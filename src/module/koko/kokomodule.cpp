#include "kokomodule.h"
#include "../debug/debug.h"
namespace module
{
    void  koko_module::generate_answer(const std::string& sender, const std::string& args,
            const std::string& text, bot::bot_i* bot)
    {
        if(text.find("лисп") != text.npos)
        {
            bot->send(sender+", KOKOKOKO");
        }
    }
}
