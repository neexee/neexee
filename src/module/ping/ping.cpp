#include "../debug/debug.h"
#include "ping.h"
namespace module
{
    void ping::generate_answer(const message::message_t& msg, const std::string& args,
            bot::bot_i* bot)
    {
        bot->send("Pong");
    }
}
