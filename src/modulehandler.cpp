#include <string>
#include <sstream>
#include <exception>
#include <stdexcept>
#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

#include "named_socket/socket.h"
#include "debug/debug.h"
#include "bot.h"
#include "modulehandler.h"

namespace bot
{
    using socket_local::socket_t;
    using std::string;
    using std::stringstream;
    using std::runtime_error;
    using std::logic_error;
    using std::invalid_argument;
    using std::bad_alloc;
    using std::exception;

    struct data_t
    {
        socket_local::socket_t module_socket;
        bot_t* bot;
        pthread_t* thread;
    };

    module_handler::module_handler()
    {}

    module_handler::~module_handler()
    {}

    void * module_handler::thread(void* _data)
    {
        INFO("Handling module");
        using std::string;
        int size = 1024;
        char* buf = new char[1024];
        data_t* data = static_cast<data_t*>(_data);
        int check;
        (data->module_socket).get(buf, size, 0);
        std::string answer(buf);
        data->bot->send(answer);
        data->bot->clear_threads();
        data->bot->thread_ready(data->thread);
        return NULL;
    }

    void module_handler::start(socket_local::socket_t& module_socket,
            pthread_t* thread,
            bot_t* bot)
    {
        data_t* data = new data_t;

        data->module_socket = module_socket;
        data->bot = bot;
        data->thread = thread;

        if(0 != pthread_create(thread, NULL, module_handler::thread, (void*) data))
        {
            throw runtime_error(strerror(errno));
        }
    }

}

