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
#include "../tools/tools.h"
#include "../debug/debug.h"
#include "../named_socket/socket.h"
#include "../tools/tokenizer.h"
#include <iostream>
namespace 
{
        const char START_SYMBOL = '*';
        const std::string END_STRING = "//";
}
namespace module
{
    void AsyncModule::generate_answer(const std::string& sender, const std::string& args,
            const std::string& _text, const std::string& sockname)
    {
        using socket_local::socket_t;
        using std::string;
        using std::vector;
        using tokenizer::Tokenizer;

        char buf[1024];
        int check;
        int pair[2];

        //prepare argv for execv 
        std::string text = _text;
        Tokenizer _tokenizer = Tokenizer(args);
        vector<string> arg_vector = _tokenizer.tokenize();
        vector<string> additional_args = parse_args(text);
        for(auto it : additional_args )
        {
            arg_vector.push_back(it);
        }
        const char **argv = new const char* [arg_vector.size()+2];
        for (size_t j = 0;  j < arg_vector.size();  ++j)
        {    argv [j] = arg_vector[j].c_str();
             INFO(arg_vector[j].c_str());
        }
        argv [arg_vector.size()] = NULL;

        //prepare sockets for IPC
        socket_t sock;
        sock.connect(sockname.c_str());
        check = socketpair(AF_LOCAL, SOCK_STREAM,0, pair);
        if(check == -1)
        {
            //strerror_r(errno, buf, sizeof buf);
            ERROR(strerror(errno));
        }
        else
        {
            pid_t childpid;
            //prepare signal handler
            signal(SIGCHLD, sigchildHandler); 

            //fork, dup, execv
            childpid = fork();
            if(childpid  == 0)
            { 
                dup2(pair[1], 1);

                check =  execv(argv[0], (char **)argv);
                if(check == -1)
                {
                   // strerror_r(errno, buf, sizeof buf);
                    ERROR(strerror(errno));
                }

            }
            if( childpid > 0)
            {
             // socket_t reader(pair[0]);
              int size;
              
              INFO("Entering get");
               size = read(pair[0], buf, sizeof buf);
                {
                  INFO("leave read");
                  sock.send(buf, size);
                }
              sock.close();
            }

        }
    }


    const std::vector<std::string> AsyncModule::parse_args(std::string& text )
    {
        using std::string;
        using tokenizer::Tokenizer;
        std::vector<string> args_vec;
        string args;

        text.erase(0, text.find_first_not_of("\t ")); 
        if(text[0] == START_SYMBOL)
        {
            size_t pos_end_args; 
            if( (pos_end_args = text.find(END_STRING)) != string::npos)
            {
                args = text.substr(1, pos_end_args-1);
                text.erase(0, pos_end_args+2);
                Tokenizer _tokenizer = Tokenizer(args);
                args_vec = _tokenizer.tokenize();
            }
        }
        return args_vec;
    }
}
