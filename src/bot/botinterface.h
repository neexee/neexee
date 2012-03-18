#include <string>
#include "../settings/settings.h"
#ifndef BOT_INTERFACE_H
#define BOT_INTERFACE_H
namespace bot
{
    class bot_i
    {
        public:
        virtual void send(const std::string& message) = 0;
        virtual std::string get_room_nick() = 0;
        virtual void get_room_names() = 0;
        virtual settings::settings_t* get_settings() = 0;
        virtual void get_help() = 0;
    };
}
#endif /*BOT_INREFACE_H*/
