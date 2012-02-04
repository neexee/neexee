#ifndef MODULE_DEFAULT_H
#define MODULE_DEFAULT_H
#include "module.h"
//#include <string>
class DefaultModule: public Module 
{
    public:
    virtual void  generate_answer(const std::string& sender,
            const std::vector<std::string>& text, char* sockname);
};
#endif
