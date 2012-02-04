#include "defaultmodule.h"
#include "../debug/debug.h"
#include "../named_socket/socket.h"
void  DefaultModule::generate_answer(const std::string& sender,
        const std::vector<std::string>& text, const std::string& sockname)
{
    using socket_local::socket_t;
    socket_t sock;
    sock.connect(sockname.c_str());
    std::string message("OH, U!");
    sock.send(message.c_str(),message.length());
    sock.close();
}
