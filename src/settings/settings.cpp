#include "settings.h"
#include "convert.h"
#include "../tools/tools.h"
#include "../debug/debug.h"
namespace
{
    const std::string DELIMITERS =  "\t ";
}
namespace settings
{

    void settings_t::remove_comment(std::string& line) const
    {
        if (line.find('#') != line.npos)
            line.erase(line.find('#'));
    }

    bool settings_t::only_whitespace(std::string &line) const
    {
        return (line.find_first_not_of(' ') == line.npos);
    }
    bool settings_t::valid_line(std::string &line) const
    {
        std::string temp = line;
        temp.erase(0, temp.find_first_not_of(DELIMITERS));
        if (temp[0] == '=')
            return false;

        for (size_t i = temp.find('=') + 1; i < temp.length(); i++)
            if (temp[i] != ' ')
                return true;

        return false;
    }

    void settings_t::extract_key(std::string &key, size_t& sep_pos, std::string& line) const
    {
        key = line.substr(0, sep_pos);
        if (key.find('\t') != line.npos || key.find(' ') != line.npos)
            key.erase(key.find_first_of(DELIMITERS));
    }
    void settings_t::extract_value(std::string &value, size_t& sep_pos, std::string &line) const
    {
        value = line.substr(sep_pos + 1);
        value.erase(0, value.find_first_not_of(DELIMITERS));
        value.erase(value.find_last_not_of(DELIMITERS) + 1);
    }

    void settings_t::extract_contents(std::string &line) 
    {
        std::string temp = line;
        temp.erase(0, temp.find_first_not_of(DELIMITERS));
        size_t sep_pos = temp.find('=');

        std::string key, value;
        extract_key(key, sep_pos, temp);
        extract_value(value, sep_pos, temp);

        if (!key_exists(key))
            contents.insert(std::pair<std::string, std::string>(key, value));
        else
            exit_with_error("CFG: Can only have unique key names!\n");
    }

    void settings_t::parse_line(std::string& line, size_t line_number)
    {
        if (line.find('=') == line.npos)
            exit_with_error("CFG: Couldn't find separator on line: " + convert::T_to_string(line_number) + "\n");

        if (!valid_line(line))
            exit_with_error("CFG: Bad format for line: " + convert::T_to_string(line_number) + "\n");

        extract_contents(line);
    }

    void settings_t::extract_keys()
    {
        std::ifstream file;
        file.open(filename.c_str());
        if (!file)
            exit_with_error("CFG: File " + filename + " couldn't be found!\n");

        std::string line;
        size_t line_number = 0;
        while (std::getline(file, line))
        {
            line_number++;
            std::string temp = line;

            if (temp.empty())
                continue;

            remove_comment(temp);
            if (only_whitespace(temp))
                continue;

            parse_line(temp, line_number);
        }

        file.close();
    }

    settings_t::settings_t()
    {
        // this->filename = filename;
        //extract_keys();
    }

    void settings_t::get( const std::string& filename)
    {
        this->filename = filename;
        extract_keys();
    }

    bool settings_t::key_exists(const std::string& key) const
    {
        return contents.find(key) != contents.end();
    }

    settings_t::~settings_t()
    {

    }
}
