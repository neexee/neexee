#include "convert.h"

export template <typename T> std::string Convert::T_to_string(T const &val) 
    {
        std::ostringstream ostr;
        ostr << val;
        return ostr.str();
    }
