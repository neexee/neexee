#include "settings.h"
#include "convert.h"
void Settings::removeComment(std::string &line) const
    {
        if (line.find('#') != line.npos)
            line.erase(line.find('#'));
    }

bool Settings::onlyWhitespace(const std::string &line) const
    {
        return (line.find_first_not_of(' ') == line.npos);
    }
bool Settings::validLine(const std::string &line) const
    {
        std::string temp = line;
        temp.erase(0, temp.find_first_not_of("\t "));
        if (temp[0] == '=')
            return false;

        for (size_t i = temp.find('=') + 1; i < temp.length(); i++)
            if (temp[i] != ' ')
                return true;

        return false;
    }

void Settings::extractKey(std::string &key, size_t const &sepPos, const std::string &line) const
    {
        key = line.substr(0, sepPos);
        if (key.find('\t') != line.npos || key.find(' ') != line.npos)
            key.erase(key.find_first_of("\t "));
    }
void Settings::extractValue(std::string &value, size_t const &sepPos, const std::string &line) const
    {
        value = line.substr(sepPos + 1);
        value.erase(0, value.find_first_not_of("\t "));
        value.erase(value.find_last_not_of("\t ") + 1);
    }

void Settings::extractContents(const std::string &line) 
    {
        std::string temp = line;
        temp.erase(0, temp.find_first_not_of("\t "));
        size_t sepPos = temp.find('=');

        std::string key, value;
        extractKey(key, sepPos, temp);
        extractValue(value, sepPos, temp);

        if (!keyExists(key))
            contents.insert(std::pair<std::string, std::string>(key, value));
        else
            exitWithError("CFG: Can only have unique key names!\n");
    }

void Settings::parseLine(const std::string &line, size_t const lineNo)
    {
        if (line.find('=') == line.npos)
            exitWithError("CFG: Couldn't find separator on line: " + Convert::T_to_string(lineNo) + "\n");

        if (!validLine(line))
            exitWithError("CFG: Bad format for line: " + Convert::T_to_string(lineNo) + "\n");

        extractContents(line);
    }

void Settings::ExtractKeys()
    {
        std::ifstream file;
        file.open(fName.c_str());
        if (!file)
            exitWithError("CFG: File " + fName + " couldn't be found!\n");

        std::string line;
        size_t lineNo = 0;
        while (std::getline(file, line))
        {
            lineNo++;
            std::string temp = line;

            if (temp.empty())
                continue;

            removeComment(temp);
            if (onlyWhitespace(temp))
                continue;

            parseLine(temp, lineNo);
        }

        file.close();
    }
Settings::Settings()
    {
       // this->fName = fName;
        //ExtractKeys();
    }
void Settings::get(const std::string &fName)
    {
        this->fName = fName;
        ExtractKeys();
    }
bool Settings::keyExists(const std::string &key) const
    {
        return contents.find(key) != contents.end();
    }
Settings::~Settings()
    {

    }
template <typename ValueType> ValueType Settings::getValueOfKey(const std::string &key,
        ValueType const &defaultValue) const
{
    if (!keyExists(key))
        return defaultValue;

    return Convert::string_to_T<ValueType>(contents.find(key)->second);
}
/*
int main()
{
    ConfigFile cfg("config.cfg");

    bool exists = cfg.keyExists("car");
    std::cout << "car key: " << std::boolalpha << exists << "\n";
    exists = cfg.keyExists("fruits");
    std::cout << "fruits key: " << exists << "\n";

    std::string someValue = cfg.getValueOfKey<std::string>("mykey", "Unknown");
    std::cout << "value of key mykey: " << someValue << "\n";
    std::string carValue = cfg.getValueOfKey<std::string>("car");
    std::cout << "value of key car: " << carValue << "\n";
    double doubleVal = cfg.getValueOfKey<double>("double");
    std::cout << "value of key double: " << doubleVal << "\n\n";

    std::cin.get();
    return 0;
}
*/

