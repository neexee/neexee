#include "tokenizer.h"
namespace
{
    const std::string DELIMITERS(" \t\n\r");
}
namespace tools
{
    using std::string;
    tokenizer::tokenizer( const std::string& s)
    {
        m_string = s;
        m_offset = 0;
        m_delimiters =  DELIMITERS;
    }
    tokenizer::tokenizer(const string& s, const std::string& delimiters)
    { 
        m_string  = s;
        m_offset = 0; 
        m_delimiters  = delimiters;
    }
    bool tokenizer::next_token() 
    {
        return next_token(m_delimiters);
    }

    bool tokenizer::next_token(const std::string& delimiters) 
    {
        size_t i = m_string.find_first_not_of(delimiters, m_offset);
        if (string::npos == i) 
        {
            m_offset = m_string.length();
            return false;
        }

        size_t j = m_string.find_first_of(delimiters, i);
        if (string::npos == j) 
        {
            m_token = m_string.substr(i);
            m_offset = m_string.length();
            return true;
        }

        m_token = m_string.substr(i, j - i);
        m_offset = j;
        return true;
    }
    const std::string tokenizer::get_token() const
    {
        return m_token;
    }
    const std::vector<std::string> tokenizer::tokenize()
    {
        std::vector<std::string> tokens;
        while(next_token())
        {
            tokens.push_back(get_token());
        }
        return tokens;
    }
}
