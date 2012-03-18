#ifndef MODULE_KOKO_H
#define MODULE_KOKO_H
#include "../module.h"
namespace module
{
    class koko_module: public module_i
    {
        public:
            virtual void  generate_answer(const message::message_t& msg, const std::string& args,
                    bot::bot_i* bot);
            virtual ~koko_module(){};
    };
}
#endif
