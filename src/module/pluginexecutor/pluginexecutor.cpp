#include <string>
#include <vector>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/wait.h>
#include <errno.h>
#include "pluginexecutor.h"
#include  "../../settings/convert.h"
#include "../../debug/debug.h"
#include "../../tools/tokenizer.h"
#include <iostream>
#include "../../message/message.h"
namespace 
{
        const char START_SYMBOL = '*';
        const std::string END_STRING = "//";
}
namespace module
{
    void plugin_executor::generate_answer(const message::message_t& msg, 
				 const std::string& args,  bot::bot_i* bot) 
    {
       // using socket_local::socket_t;
        using std::string;
        using std::vector;
        using tools::tokenizer;
        
        char buf[1024];
        int check;
        int sockets[2];

        //prepare argv for execv 
        std::string text = msg.body();
        tokenizer _tokenizer = tokenizer(args);
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

        check = socketpair(AF_LOCAL, SOCK_STREAM,0, sockets);
        if(check == -1)
        {
            //strerror_r(errno, buf, sizeof buf);
            ERROR(strerror(errno));
        }
        else
        { 
            pid_t childpid;
            //prepare signal handler
            signal(SIGCHLD, plugin_executor::sigchild_handler); 

            //fork, dup, execv
            childpid = fork();
            if(childpid  == 0)
            { 
                dup2(sockets[1], 1);

                check =  execv(argv[0], (char **)argv);
                if(check == -1)
                {
                   // strerror_r(errno, buf, sizeof buf);
                    ERROR(strerror(errno));
                }

            }
            if( childpid > 0)
            {
                int size;
              INFO(std::string("CLOSING SOCKET "+ settings::convert::T_to_string(sockets[1]) ).c_str());
                close(sockets[1]);
                    while((size = recv(sockets[0], buf, sizeof buf, 0)) > 0)
                    {
                        if(buf[size-1] =='\n')
                        {
                            buf[size-1] = 0;
                        }
                        bot->send(message::message_t(std::string(buf) , msg.priv()));
                    }
                    close(sockets[0]);
                    INFO(std::string("CLOSING SOCKET "+ settings::convert::T_to_string(sockets[1]) ).c_str());
                    close(sockets[1]);

                    INFO("RECIEVED OK");

            }
        }
    }

    void plugin_executor::sigchild_handler(int sig)
    {

        int status;
        wait(&status);
       // close(socket);
        INFO(std::string ("Child process terminated by signal " + settings::convert::T_to_string(sig) ).c_str());
    }

    const std::vector<std::string> plugin_executor::parse_args(std::string& text )
    {
        using std::string;
        using tools::tokenizer;
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
                tokenizer _tokenizer = tokenizer(args);
                args_vec = _tokenizer.tokenize();
            }
        }
        return args_vec;
    }
}
