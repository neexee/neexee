#include "console.h"
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <cstring>
#include <stdexcept>
#include "../debug/debug.h"
#include "../bot/bot.h"
namespace
{
    const size_t BUFSIZE = 1024;
    const char welcome[] =  "\033[1;39m>>\033[0m ";
}
namespace console
{
    using bot::bot_t;
    using std::string;
    console_t::console_t(bot_t* _b)
    {
        b = _b;
    }
    console_t::~console_t()
    {
        if(0 != pthread_join(*thread, NULL))
        {
            ERROR(strerror(errno));
        }
        delete thread;
    }
    void console_t::start()
    {
       int check;
       thread = new pthread_t; 

       check = pthread_create(thread, NULL, console_t::reader,  (void*)b);
       if(check != 0)
       {
           ERROR(strerror(errno));
           throw std::runtime_error("Failed in creation thread");
       }

    }
    void* console_t::reader(void* __bot)
    {
      bot::bot_t* _bot = static_cast<bot::bot_t*>(__bot);
      char buffer[BUFSIZE];
      write(0,welcome, sizeof welcome);
      int i;
      while((i = read(0, buffer, BUFSIZE )) > 0)
        {
            _bot->send(std::string(buffer));
             write(0,welcome, sizeof welcome);
        }
      return NULL;

    }
}
