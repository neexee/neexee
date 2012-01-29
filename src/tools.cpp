#ifndef __TOOLS
#define __TOOLS
#include <stdlib.h>
#include <iostream>
void exitWithError(const std::string &error) 
    {
         std::cout << error;
         std::cin.ignore();
         std::cin.get();
         exit(EXIT_FAILURE);
    };
#endif