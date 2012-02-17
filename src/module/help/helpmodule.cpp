#include "helpmodule.h"
namespace module
{
    void  help_module::generate_answer(const std::string& sender, const std::string& args,
            const std::string& text, bot::bot_i* bot)
    {
        bot->get_help();
    }
   help_module::~help_module()
    {
    }
}

