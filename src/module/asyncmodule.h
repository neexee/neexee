#ifndef MODULE_ASYNC_H
#define MODULE_ASYNC_H
#define MAX_ARG_NUM 1
#include "module.h"
namespace module
{
    class AsyncModule : public Module
    {
        public:
            virtual void generate_answer(const std::string& sender,
                    const std::vector<std::string>& text, const std::string& sockname);
    };
}
#endif
