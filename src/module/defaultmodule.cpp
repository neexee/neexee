#include "defaultmodule.h"
#include "../debug/debug.h"
namespace module
{
    void default_module::generate_answer(const message::message_t& msg, 
                                         const std::string& args,
                                         bot::bot_i* bot) 
    {
       bot->send("OH U!");
    }
}
