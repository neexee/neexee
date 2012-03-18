#include "whomodule.h"
namespace module
{
       void who_module::generate_answer(const message::message_t& msg,
const std::string& args, bot::bot_i* bot)
        {
            bot->get_room_names();
        }
        who_module::~who_module()
        {

        }
}