#include <string>
#include <vector>
namespace tokenizer
{
    class Tokenizer 
    {
        public:
            Tokenizer(const std::string& str);
            Tokenizer(const std::string& str, const  std::string& delimiters);
            bool NextToken();
            bool NextToken(const std::string& delimiters);
            const std::string GetToken() const;
            const std::vector<std::string> tokenize();
            //void Reset();
        protected:
            size_t m_offset;
            std::string m_string;
            std::string m_token;
            std::string m_delimiters;
    };
}
