#ifndef MODULE_DEFAULT_H
#define MODULE_DEFAULT_H
#include "module.h"
namespace module
{
    class default_module: public module_i
    {
        public:
	    virtual void generate_answer(const message::message_t& msg, 
					 const std::string& args,  bot::bot_i* bot);
            virtual ~default_module(){};
    };
}
#endif
