#include "../module.h"
namespace module
{
    class who_module: public module_i
    {
        public:
            virtual void generate_answer(const message::message_t& msg, 
					 const std::string& args,  bot::bot_i* bot);
            virtual ~who_module();
    };
}

