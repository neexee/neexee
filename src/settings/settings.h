#ifndef __SETTINGS
#define __SETTINGS
#include <iostream>
#include <string>
#include <map>
#include <stdexcept>
#include "convert.h"
#define JID_KEYWORD "jid"
#define PASSWORD_KEYWORD "pass"
#define ROOM_KEYWORD "room"
#define EXTERNAL_MODULES_KEYWORD "external_modules"
namespace settings
{
    class settings_t
    {
        public:
            settings_t();

            void get(const std::string& filename);

            bool key_exists( const std::string &key) const;

            template <typename value_type> value_type get_value_of_key(const std::string& key) 
            {
                if (!key_exists(key))
                {
                    throw std::runtime_error(key);
                }
                else
                {
                    return convert::string_to_T<value_type>(contents.find(key)->second);
                }
            };

            ~settings_t();

        private:
            void remove_comment(std::string& line) const;
            bool only_whitespace(std::string& line) const;
            bool valid_line(std::string& line) const;
            void extract_key(std::string& key, size_t& sep_pos, std::string& line) const;
            void extract_value(std::string &value, size_t &sep_pos, std::string &line) const;
            void extract_contents(std::string &line);
            void parse_line(std::string &line, const size_t line_number);
            void extract_keys();

            std::map<std::string, std::string> contents;
            std::string filename;

    };
}
#endif
