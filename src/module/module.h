#ifndef MODULE_ANSWER_GENERATE_H
#define MODULE_ANSWER_GENERATE_H
#include <string>
#include <vector>
class Module
{
    public:
    virtual void generate_answer(const std::string& sender,
            const std::vector<std::string>& text, char* sockname) = 0;
};
#endif
