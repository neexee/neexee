#ifndef MODULE_PING_H
#define MODULE_PING_H
#include "../module.h"
namespace module
{
    class ping : public module_i 
    {
        public:
            virtual void generate_answer(const message::message_t& msg,const std::string& args,
                    bot::bot_i* bot);
    };
}
#endif
