#ifndef __TOOLS
#define __TOOLS
#include <stdlib.h>
#include <iostream>
#include "../debug/debug.h"
#include "tools.h"
#include <sys/types.h>
#include <sys/wait.h>
void exit_with_error(const std::string &error) 
    {
         std::cout << error;
         std::cin.ignore();
         std::cin.get();
         exit(EXIT_FAILURE);
    };
#endif
