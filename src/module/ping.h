#ifndef MODULE_PING_H
#define MODULE_PING_H
#include "module.h"
class Ping : public Module 
{
    public:
    virtual void generate_answer(const std::string& sender,
            const std::vector<std::string>& text, const std::string& sockname);
};
#endif
