#ifndef HELP_MODULE_H
#define HELP_MODULE_H
#include "../module.h"
namespace module
{
    class help_module: public module_i
    {
        public:
            virtual void  generate_answer(const std::string& sender, const std::string& args,
                    const std::string& text, bot::bot_i* bot);
            virtual ~help_module();
    };
}
#endif
