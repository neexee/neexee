#include "../module.h"
#include <vector>
#include <map>
namespace module
{
  class history : public module_i
  {
     public:
          virtual void generate_answer(const std::string& sender, const std::string& args,
                    const std::string& text, bot::bot_i* bot);
          void save(const std::string& filename);
	  typedef std::pair<std::string date, message::message_t _message> hist_entry;
	  std::vector<hist_entry> hist;
	  
  };
}