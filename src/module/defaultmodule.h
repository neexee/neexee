#ifndef MODULE_DEFAULT_H
#define MODULE_DEFAULT_H
#include "module.h"
//#include <string>
class DefaultModule: public Module 
    {
        public:
            virtual std::string generate_answer(const std::string& sender,
                                                const std::vector<std::string>& text);
    };
#endif
