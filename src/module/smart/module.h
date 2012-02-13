#include <map>
#include <string>
namespace smart
{
    class Module
    {
        public:
            Module();
            ~Module();
            void read();
            std::string get_next(std::string& key);
            void put(std::string& key, std::string& word);
            void dump();
            void parse_and_put(const std::string& message);
            std::string generate(const std::string& begin, int length);
            int random_0_to_n(int n);


        private:
            std::multimap<std::string, std::pair<int, std::string> > dict;

    };
}
