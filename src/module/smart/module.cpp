#include "module.h"
#include <iostream>
#include <fstream>
#include "../../tools/tokenizer.h"
#include <stdlib.h>
#include <time.h>
namespace
{
    const std::string delimiters = " \t\n,.:?!";
}
namespace smart
{
    using std::string;
    using std::pair;
    using std::multimap;
    typedef pair<int, string> pair_second;
    typedef multimap<string, pair_second > dictmap;
    typedef pair<string, pair_second > map_element;

    void Module::read()
    {

        std::ifstream backup;
        backup.open("pairs");
        if (!backup)
            return; 

        string key;
        string word;
        int count;
        while(backup.good())
        {
            backup>>key;
            if (!backup.good())
            {
                break;
            }
            backup>>count;
            backup>>word;
            dict.insert(map_element(key, pair_second(count, word)));
        }
        backup.close();
    }
    void Module::dump()
    {
        std::ofstream backup;
        backup.open("pairs", std::ofstream::trunc);
        for(auto it: dict)
        {
            backup<<it.first<<" ";
            backup<<it.second.first<<" "<<it.second.second<< std::endl;
        }
        backup.close();
    }
    void Module::put(string& key, string& word)
    {
        pair<dictmap::iterator, dictmap::iterator > range = dict.equal_range(key);
        bool found = 0;
        for(dictmap::iterator it = range.first; it!= range.second; ++it)
        {
            if(it->second.second == word )
            {
                it->second.first++;
                found =1;
            }

        }
        if(found == 0)
        {
            dict.insert(map_element (key, pair_second(1, word)));
        }
    }
    string Module::get_next(string& key)
    {
        pair<dictmap::iterator, dictmap::iterator >  range = dict.equal_range(key);
        int count=0;
        string next;
        bool found = 0;
        for(auto it = range.first; it!= range.second; ++it)
        {
            if(it->second.first > count )
            {
                next = it->second.second;
            }

        }

        if(next == std::string(""))
        {
            dictmap::iterator item = dict.begin();
            std::advance(item, random_0_to_n(dict.size()) );
            next = item->first;
        }
        return next;
    }
    void Module::parse_and_put( const string& message)
    {
        using tokenizer::Tokenizer;
        Tokenizer tokens = Tokenizer(message, delimiters);
        std::string prev;
        std::string  next;
        if(tokens.NextToken())
        {
            prev = tokens.GetToken();
        }
        else
        {
            return;
        }

        while(tokens.NextToken())
        {
            next = tokens.GetToken();
            put(prev, next);
            prev = next; 
        }

    }
    string Module::generate(const string& begin, int length)
    {
        string answer;
        string token = begin;
        for(int i= 0; i< length; i++)
        {
            token = get_next(token);
            answer+=token + " ";
        }
        return answer;
    }
    int Module::random_0_to_n(int n)
    {
        srand ( time(NULL) );
        return rand()%n;
    }
    Module::Module()
    {}
    Module::~Module()
    {
        dump();
    }
}
