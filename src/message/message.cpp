#include "message.h"
namespace message
  {

  message_t::message_t ( const std::string& _sender, const std::string& _body )
  {
    sender_ = _sender;
    body_ = _body;

  }
  std::string message_t::sender() const
    {
      return sender_;
    }
  std::string message_t::body() const
    {
      return body_;
    }
  message_t::~message_t()
  {

  }
}