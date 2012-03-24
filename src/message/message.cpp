#include "message.h"
namespace message
  {

  message_t::message_t (  const std::string& _body, bool __priv,const std::string& _sender, const std::string& _jid,
                         const std::string& _keyword)
  {
    sender_ = _sender;
    body_ = _body;
    keyword_ = _keyword;
    _priv = __priv;
    jid = _jid;

  }
  /*
  message_t::message_t (  const std::string& _body, const std::string& _sender,
                         std::string& _keyword)
  {
    sender_ = _sender;
    body_ = _body;
    keyword_ = _keyword;
   
  }

*/
  std::string message_t::sender() const
    {
      return sender_;
    }
  std::string message_t::body() const
    {
      return body_;
    }
  std::string message_t::full() const
    {
      return jid;
    }
  bool message_t::priv() const
  {
    return _priv;
  }
  std::string message_t::keyword() const
    {
      return keyword_;
    }
void message_t::set_keyword(const std::string& _keyword)
{
   keyword_ = _keyword;
}


  message_t::~message_t()
  {

  }
}
