#ifndef MODULE_ANSWER_GENERATE_H
#define MODULE_ANSWER_GENERATE_H
#include <string>
#include <vector>
#include "../bot/botinterface.h"
#include "../message/message.h"
namespace module
{
    class module_i
    {
        public:
            virtual void generate_answer(const message::message_t& msg, 
					 const std::string& args,  bot::bot_i* bot) = 0;
            virtual ~module_i(){};
    };
}
#endif
