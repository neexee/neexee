#include <string>
#include <vector>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/wait.h>
#include <errno.h>
#include "asyncmodule.h"
#include "../tools.h"
#include "../debug/debug.h"
#include "../named_socket/socket.h"
using namespace std;
void AsyncModule::generate_answer(const string& sender,
        const vector<string>& text, const std::string& sockname)
{
    using socket_local::socket_t;
    char buf[80];
    int check;
    int status;
    int pair[2];

    string binaryFile = text.front();
    INFO(string("Binary file: "+ binaryFile).c_str() );

    signal( SIGCHLD, sigchildHandler); 

    socket_t sock;
    sock.connect(sockname.c_str());
    INFO("socket connected");
    check = socketpair(AF_LOCAL, SOCK_STREAM,0, pair);
    pid_t childpid;
    if(check == -1)
    {

        strerror_r(errno, buf, sizeof buf);
        ERROR(buf);
    }
    else
    {

        childpid = fork();
        if(childpid  == 0)
        { 
            //INFO("dup2 stdout socket");
            dup2(pair[1], 1);

            check =  execl(binaryFile.c_str(), binaryFile.c_str(), text[1].c_str(), (char *) 0);
            if(check == -1)
            {
                strerror_r(errno, buf, sizeof buf);
                ERROR(buf);
            }

        }
        if( childpid > 0)
        {
            do
            {
                check = read(pair[0], buf, sizeof buf);
                if(check>0)
                {
                    sock.send(buf, check);
                }
            }while (check  == (sizeof buf) );
            sock.close();
            wait(&status);
        }

    }
}


