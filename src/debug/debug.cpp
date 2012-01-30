#include <string>
#include <iostream>
#include <sstream>
#include <ctime>

#include "debug.h"


    using std::string;
    using std::stringstream;
    using std::cout;
    using std::endl;


    void debug::print(const char* type, const char* message, const char* func, const int line)
    {
        string result;
        time_t time = ::time(0);
        struct tm* struct_time = localtime(&time);
        char result_time[21];

        strftime(result_time, sizeof(result_time), "[%d/%m/%y][%H:%M:%S]", struct_time);

        result += result_time;

        result += type;

        if(0 != line)
        {
            stringstream sstream;
            sstream << line;
            result += sstream.str();
            result += " line: ";
        }

        result += message;

        if(0 != func)
        {
            result += " (function: ";
            result += func;
            result += ')';
        }

        cout << result << endl;
    }

    debug::debug() {}
    debug::~debug() {}
