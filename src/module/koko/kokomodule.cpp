#include "kokomodule.h"
#include "../debug/debug.h"
namespace module
{
    void  koko_module::generate_answer(const message::message_t& msg, const std::string& args,
         bot::bot_i* bot)
    {
        if(msg.body().find("lisp") != msg.body().npos)
        {
            bot->send(msg.sender() +", KOKOKOKO");
        }
    }
}
