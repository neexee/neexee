#ifndef MODULE_ANSWER_GENERATE_H
#define MODULE_ANSWER_GENERATE_H
#include <string>
#include <vector>
#include "../bot/botinterface.h"
namespace module
{
    class module_i
    {
        public:
            virtual void generate_answer(const std::string& sender, const std::string& args,
                    const std::string& text, bot::bot_i* bot) = 0;
            virtual ~module_i(){};
    };
}
#endif
