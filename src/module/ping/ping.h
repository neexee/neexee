#ifndef MODULE_PING_H
#define MODULE_PING_H
#include "../module.h"
namespace module
{
    class ping : public module_i 
    {
        public:
            virtual void generate_answer(const std::string& sender, const std::string& args,
                    const std::string& text, bot::bot_i* bot);
    };
}
#endif
