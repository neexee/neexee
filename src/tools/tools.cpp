#ifndef __TOOLS
#define __TOOLS
#include <stdlib.h>
#include <iostream>
#include "../debug/debug.h"
#include <sys/types.h>
#include <sys/wait.h>
void exitWithError(const std::string &error) 
    {
         std::cout << error;
         std::cin.ignore();
         std::cin.get();
         exit(EXIT_FAILURE);
    };
void sigchildHandler(int sig)
    {
        pid_t pid;
        int status;
        while((pid = waitpid(-1, &status, WNOHANG)) > 0)
        {
            INFO("Child process terminated");
        }
    }
#endif
