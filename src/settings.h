#ifndef __SETTINGS
#define __SETTINGS
#include <iostream>
#include <string>
#include <map>
#include <typeinfo>
#include "convert.h"
class Settings
    {
       public:
         Settings();
         
         void get(const std::string& fName);
         
         bool keyExists( const std::string &key) const;
        
         // template <typename ValueType> ValueType getValueOfKey(std::string &key) const;
         template <typename ValueType> ValueType getValueOfKey(const std::string& key, 
                                                               const ValueType& defaultValue = ValueType())
             {
                 if (!keyExists(key))
                      return defaultValue;

                  return Convert::string_to_T<ValueType>(contents.find(key)->second);
             };
         
         ~Settings();
      
       private:
          void removeComment(std::string& line) const;
          bool onlyWhitespace(std::string& line) const;
          bool validLine(std::string& line) const;
          void extractKey(std::string& key, size_t& sepPos, std::string& line) const;
          void extractValue(std::string &value, size_t &sepPos, std::string &line) const;
          void extractContents(std::string &line);
          void parseLine(std::string &line, const size_t lineNo);
          void ExtractKeys();
             
          std::map<std::string, std::string> contents;
          std::string fName;

    };
#endif
