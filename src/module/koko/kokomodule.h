#ifndef MODULE_KOKO_H
#define MODULE_KOKO_H
#include "../module.h"
namespace module
{
    class koko_module: public module_i
    {
        public:
            virtual void  generate_answer(const std::string& sender, const std::string& args,
                    const std::string& text, bot::bot_i* bot);
            virtual ~koko_module(){};
    };
}
#endif
