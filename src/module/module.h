#ifndef MODULE_ANSWER_GENERATE_H
#define MODULE_ANSWER_GENERATE_H
#include <string>
#include <vector>
namespace module
{
    class Module
    {
        public:
            virtual void generate_answer(const std::string& sender,
                    const std::vector<std::string>& text, const std::string& sockname) = 0;
    };
}
#endif
