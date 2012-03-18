#include "helpmodule.h"
namespace module
{
    void  help_module::generate_answer(const message::message_t& msg, const std::string& args,
            bot::bot_i* bot)
    {
        bot->get_help();
    }
   help_module::~help_module()
    {
    }
}

