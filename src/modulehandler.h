#ifndef __CLIENT_HANDLER_H
#define __CLIENT_HANDLER_H

#include <pthread.h>
#include "named_socket/socket.h"
#include "bot.h"
namespace bot
{
    class module_handler 
    {
    public:
        module_handler ();
        virtual ~module_handler ();
        static void start(socket_local::socket_t& module_socket,
                          pthread_t* thread,
                          bot_t* bot);
    private:
        static void * thread(void* data);
    };
}
#endif
