#ifndef __SETTINGS
#define __SETTINGS
#include <iostream>
#include <string>
#include <map>
#include <typeinfo>
class Settings
    {
       public:
         Settings();
         
         void get(const std::string &fName);
         
         bool keyExists(const std::string &key) const;
        
         template <typename ValueType> ValueType getValueOfKey(const std::string &key,
                            ValueType const &defaultValue = ValueType()) const;
         
         ~Settings();
      
       private:
          void removeComment(std::string &line) const;
          bool onlyWhitespace(const std::string &line) const;
          bool validLine(const std::string &line) const;
          void extractKey(std::string &key, size_t const &sepPos, const std::string &line) const;
          void extractValue(std::string &value, size_t const &sepPos, const std::string &line) const;
          void extractContents(const std::string &line);
          void parseLine(const std::string &line, size_t const lineNo);
          void ExtractKeys();
             
          std::map<std::string, std::string> contents;
          std::string fName;

    };
#endif
