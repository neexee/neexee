#include <string>
#include <vector>
namespace tools
{
    class tokenizer 
    {
        public:
            tokenizer(const std::string& str);
            tokenizer(const std::string& str, const  std::string& delimiters);
            bool next_token();
            bool next_token(const std::string& delimiters);
            const std::string get_token() const;
            const std::vector<std::string> tokenize();
            //void Reset();
        protected:
            size_t m_offset;
            std::string m_string;
            std::string m_token;
            std::string m_delimiters;
    };
}
