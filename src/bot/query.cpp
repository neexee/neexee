#include "query.h"
namespace query
{
query_t::query_t()
{
   pthread_mutex_init(&lock, NULL);
}
query_t::~query_t()
{
  pthread_mutex_destroy(&lock);
}
void query_t::add ( const message::message_t msg, const std::string tag)
{
  pthread_mutex_lock(&lock);
  query.insert(std::pair<std::string, message::message_t>(tag, msg));
  pthread_mutex_unlock(&lock);

}
const message::message_t query_t::find ( std::string tag)
{
  pthread_mutex_lock(&lock);
  auto it = query.find(tag);
  message::message_t msg = it->second;
  query.erase(it);
  pthread_mutex_unlock(&lock);
  return msg;
}

}