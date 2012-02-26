#ifndef MESSAGE_MESSAGE_T_H
#define MESSAGE_MESSAGE_T_H
#include <string>
namespace message
  {
  class message_t
    {
    public:
      message_t ( const std::string& _sender, const std::string& _body );
      std::string sender() const;
      std::string body() const;
      ~message_t();
    private:
      std::string sender_;
      std::string body_;
    };
}

#endif