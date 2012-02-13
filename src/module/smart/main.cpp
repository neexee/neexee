#include "module.h"
#include <fstream>
#include <iostream>

int main()
{
    smart::Module ko;
    ko.read();
/*
    std::ifstream dict;
    dict.open("dict");
    if(!dict)
    {
        return -1;
    }
    std::string line;
    while(!dict.eof())
    {
       std::getline(dict, line);
       ko.parse_and_put(line);
    }
*/
    std::cout <<ko.generate(std::string("ko"), 8);
    return 0;
}
