#include "../bot/bot.h"
#include <pthread.h>

namespace console
{
    class console_t
    {
       public:
       console_t(bot::bot_t* _b);
       ~console_t();
       void start();
       static void* reader(void* __bot);
       private:
       bot::bot_t * b;
       pthread_t* thread;
    };
}
