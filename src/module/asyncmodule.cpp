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
using namespace std;
std::string AsyncModule::generate_answer(const string& sender,
        const vector<string>& text)
    {
        char buf[80];
        int check;
        int pair[2];
        int status;
        string binaryFile = text.front();
        INFO(string("Binary file: "+ binaryFile).c_str() );
        signal( SIGCHLD, sigchildHandler); 
        
        pid_t childpid;
        check = socketpair(AF_LOCAL, SOCK_STREAM,0, pair);
        if(check == -1)
            {

                strerror_r(errno, buf, sizeof buf);
                ERROR(buf);
                return std::string("МОИ СОКЕТЫ ПОЛОМАЛИСЬ");
            }
        else
            {
        
                childpid = fork();
                if(childpid  == 0)
                   { 
                       dup2(pair[1], 1);
                       //INFO("Executing text");
                       //vector<string>::iterator it;
                       //it = text.begin();
                       
                       //d
                      //INFO(std::string("Parameters: "+text[1]).c_str()); 
                      check =  execl(binaryFile.c_str(), binaryFile.c_str(), text[1].c_str(), (char *) 0);
                      if(check == -1)
                      {
                           strerror_r(errno, buf, sizeof buf);
                           ERROR(buf);
                           return std::string("exec поломался");

                      }
                       
                   }
                if( childpid > 0)
                   {   //sleep(2);
                       wait(&status);
                       std::string answer;
                       do
                       {
                            check = read(pair[0], buf, sizeof buf);
                            answer += string(buf);


                       }while (check  == (sizeof buf) );

//                       while ((check = read(pair[0], buf, sizeof buf)) == (sizeof buf) )
//                           answer += string(buf);

                           // if(check = -1)
                        //   {
                          //     strerror_r(errno, buf, sizeof buf);
                            //   ERROR(buf);
                            //   return std::string("read поломался");
                           //}
                       //else
                         //  {
                               return answer;
                         //  }
                       //wait(&status);
                   }
           }
    
    }