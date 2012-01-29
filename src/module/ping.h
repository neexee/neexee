#ifndef MODULE_PING_H
#define MODULE_PING_H
class Ping : piblic Module 
    {
        public:
            virtual std::string generate_answer(const std::string& sender,
                                                const std::string& text);
    }
#endif
