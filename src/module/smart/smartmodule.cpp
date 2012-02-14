#include <iostream>
#include <fstream>
#include <vector>
#include "../../tools/tokenizer.h"
#include "../../debug/debug.h"
#include "../../settings/settings.h"
#include "smartmodule.h"
#include <stdlib.h>
#include <time.h>
namespace
{
    const std::string delimiters = " \t\n";
}
namespace module
{
    using std::string;
    using std::pair;
    using std::multimap;
    typedef pair<int, string> pair_second;
    typedef multimap<string, pair_second > dictmap;
    typedef pair<string, pair_second > map_element;

    void smart_module::read()
    {

        std::ifstream backup;
        INFO(dictionary_file.c_str());
        backup.open(dictionary_file.c_str());
        if (!backup)
        {
            ERROR("FILE, WTF?");
        }
         //   return; 

        string key;
        string word;
        int count;
        int i = 0;
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
            i++;
        }
        INFO(std::string("Dictionary ready. " + settings::convert::T_to_string(i) + " pairs written").c_str());
        backup.close();
    }
    void smart_module::dump()
    {
        std::ofstream backup;
        backup.open(dictionary_file.c_str(), std::ofstream::trunc);
        for(auto it: dict)
        {
            backup<<it.first<<" ";
            backup<<it.second.first<<" "<<it.second.second<< std::endl;
        }
        backup.close();
    }
    void smart_module::put(string& key, string& word)
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
   string smart_module::get_next(const string& key)
    { 
        INFO("Entering get");
        string next = "";
        if(!dict.empty())
        {
            pair<dictmap::iterator, dictmap::iterator >  range = dict.equal_range(key);
            int count=0;
           // string next;
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
                INFO("NOT FOUND IN MAP");
                dictmap::iterator item = dict.begin();
                std::advance(item, random_n_to_m(0, dict.size()) );
                //if(item != dict.end())
                //{
                next = item->first;
                INFO(next.c_str());
            }
        }
        else
        {
            next = "My base empty!";
        }
            return next;
     }
    void smart_module::parse_and_put( const string& message)
    {
        
        using tools::tokenizer;
        INFO("Now i will put message into map");
        tokenizer tokens = tokenizer(message, delimiters);
        std::string prev;
        std::string  next;
        if(tokens.next_token())
        {
            prev = tokens.get_token();
        }
        else
        {
            return;
        }

        while(tokens.next_token())
        {
            next = tokens.get_token();
            put(prev, next);
            prev = next; 
        }

    }
    void smart_module::generate_answer(const std::string& sender, const std::string& args,
                    const std::string& text, bot::bot_i* bot)
    {
        
        using tools::tokenizer;
        parse_and_put(text);
        INFO("In smart_module generate answer");
        tokenizer tok = tokenizer(text, delimiters);
        INFO(text.c_str());
        INFO("tokenizer ok");
        std::vector<std::string> tokens = tok.tokenize();
        INFO("tokenize ok");
        std::string begin = tokens.at(1);

        INFO(begin.c_str());

        std::string answer = generate(begin, 4);
        bot->send(sender +", " +answer);

    }

   string smart_module::generate(const string& begin, int length)
    {
        string answer;
        string token = begin;
        INFO(std::string("length " + settings::convert::T_to_string(length)).c_str());
            ;
        for(int i= 0; i< length; i++)
        {

            token = get_next(token);
            INFO(token.c_str());
            answer+=token + " ";
        }
        INFO(answer.c_str());
        return answer;
    }

    int smart_module::random_n_to_m(int n, int m)
    {
        srand ( time(NULL) );
        return ((rand())%(m -n)) + n ;
    }
    
    smart_module::smart_module(const std::string& _dictionary_file)
    {
       dictionary_file = _dictionary_file;
       read();

    }
    smart_module::~smart_module()
    {
        dump();
        INFO("OK, DUMPED!");
    }
}
