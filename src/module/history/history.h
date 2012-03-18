#include "../module.h"
#include <vector>
#include <map>
namespace module
{
  typedef std::pair<int, message::message_t&> hist_entry;
  class history : public module_i
  {
     public:
          virtual void generate_answer(const message::message_t& msg, const std::string& args,
                    bot::bot_i* bot);
          void save(const std::string& filename);
    virtual ~history();
  private:     
	  void put(message::message_t& entry);
      void dump();
	  std::vector<hist_entry> hist;
      std::string history_file_name;
	  
  };
}