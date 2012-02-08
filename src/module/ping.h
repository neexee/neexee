#ifndef MODULE_PING_H
#define MODULE_PING_H
#include "module.h"
namespace module
{
    class Ping : public Module 
    {
        public:
            virtual void generate_answer(const std::string& sender, const std::string& args,
                    const std::string& text, const std::string& sockname);
    };
}
#endif
