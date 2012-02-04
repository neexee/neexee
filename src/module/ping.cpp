#include "../debug/debug.h"
#include "../named_socket/socket.h"
#include "ping.h"
void Ping::generate_answer(const std::string& sender,
        const std::vector<std::string>& text, char* sockname)
{
    using socket_local::socket_t;
    socket_t sock;
    WARNING("Trying to connect");
    sock.connect(sockname);
    INFO("Connect ok");
    std::string message("PING PING PONG!");
    sock.send(message.c_str(),message.length());
    sock.close();
}
