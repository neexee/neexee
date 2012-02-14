#ifndef PLuGIN_EXECUTOR_H
#define PLUGIN_EXECUTOR_H
#include "../module.h"
#include <vector>
namespace module
{
    class plugin_executor : public module_i
    {
        public:
            virtual void generate_answer(const std::string& sender, const std::string& args,
                    const std::string& text, bot::bot_i* bot);
            static void sigchild_handler(int sig);
            virtual ~plugin_executor(){};
       private:
            const std::vector<std::string> parse_args(std::string& text );

    };
}
#endif /* MODULE_ASYNC_H */
