#include "defaultmodule.h"
#include "../debug/debug.h"
#include "../named_socket/socket.h"
namespace module
{
    void  default_module::generate_answer(const std::string& sender, const std::string& args,
            const std::string& text, bot::bot_i* bot)
    {
       bot->send("OH U!");
        /* using socket_local::socket_t;
        socket_t sock;
        sock.connect(sockname.c_str());
        std::string message("OH, U!");
        sock.send(message.c_str(),message.length());
        sock.close();
        */
    }
}
