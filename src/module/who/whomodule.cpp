#include "whomodule.h"
namespace module
{
        void who_module::generate_answer(const std::string& sender, const std::string& args,
                    const std::string& text, bot::bot_i* bot)
        {
            bot->get_room_names();
        }
        who_module::~who_module()
        {
        }
}

