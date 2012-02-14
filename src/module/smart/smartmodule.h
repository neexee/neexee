#include <map>
#include <string>
#include "../module.h"
namespace module
{
    class smart_module: public module_i 
    {
        public:
            smart_module(const std::string& dictionary_file);
            virtual ~smart_module();  
            virtual void generate_answer(const std::string& sender, const std::string& args,
                    const std::string& text, bot::bot_i* bot);

            void read();
            std::string get_next(const std::string& key);
            void put(std::string& key, std::string& word);
            void dump();
            void parse_and_put(const std::string& message);
            std::string generate(const std::string& begin, int length) ;
            int random_n_to_m(int n, int m);


        private:
            std::multimap<std::string, std::pair<int, std::string> > dict;
            std::string dictionary_file;

    };
}
