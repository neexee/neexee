#ifndef MODULE_ANSWER_GENERATE_H
#define MODULE_ANSWER_GENERATE_H
#include <string>
#include <vector>
class Module
    {
        public:
            virtual std::string generate_answer(const std::string& sender,
                                                const std::vector<std::string>& text) = 0;
    };
#endif
