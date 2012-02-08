#ifndef __TOOLS
#define __TOOLS
#include <stdlib.h>
#include <iostream>
#include "../debug/debug.h"
#include "../settings/convert.h"
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
        
        int status;
        wait(&status);
        INFO(std::string ("Child process terminated by signal " + settings::Convert::T_to_string(sig) ).c_str());
    }
#endif
