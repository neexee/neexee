#include "../debug/debug.h"
#include "../named_socket/socket.h"
#include "ping.h"
namespace module
{
    void Ping::generate_answer(const std::string& sender, const std::string& args,
            const std::string& text, const std::string& sockname)
    {
        using socket_local::socket_t;
        socket_t sock;
        //WARNING("Trying to connect");
        sock.connect(sockname.c_str());
        INFO("Connect ok");
        std::string message("PING PING PONG!");
        sock.send(message.c_str(),message.length());
        sock.close();
    }
}
