#ifndef MODULE_ASYNC_H
#define MODULE_ASYNC_H
#define MAX_ARG_NUM 1
#include "module.h"
#include <vector>
namespace module
{
    class AsyncModule : public Module
    {
        public:
            virtual void generate_answer(const std::string& sender, const std::string& args,
                    const std::string& text, const std::string& sockname);
    
            const std::vector<std::string> parse_args(std::string& text );
            static void sigchildHandler(int sig);
    };
}
#endif
