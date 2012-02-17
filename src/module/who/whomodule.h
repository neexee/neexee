#include "../module.h"
namespace module
{
    class who_module: public module_i
    {
        public:
            virtual void generate_answer(const std::string& sender, const std::string& args,
                    const std::string& text, bot::bot_i* bot);
            virtual ~who_module();
    };
}

