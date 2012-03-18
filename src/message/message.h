#ifndef MESSAGE_MESSAGE_T_H
#define MESSAGE_MESSAGE_T_H
#include <string>
namespace message
  {
  class message_t
    {
    public:
      message_t ( const std::string& _sender, const std::string& _body,
                  const std::string& _keyword = std::string(""));
      std::string sender() const;
      std::string body() const;
      std::string keyword() const;
      void set_keyword(const std::string& _keyword);
      ~message_t();
    private:
      std::string sender_;
      std::string body_;
      std::string keyword_;
    };
}

#endif