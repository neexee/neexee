#include <string.h>
#include <vector>
#include <pthread.h>
#include <map>
#include "../message/message.h"
namespace query
{
   class query_t
   {
    public:
     query_t();
     ~query_t();
     void add(const message::message_t, const std::string);
     const message::message_t find(std::string);
   private:
     pthread_mutex_t lock;
     std::multimap< std::string, message::message_t > query;
   };
}