#include <iostream>
#include <fstream>
#include <vector>
#include "../../tools/tokenizer.h"
#include "../../debug/debug.h"
#include "../../settings/settings.h"
#include "../../message/message.h"
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
            ERROR("File with dictionary not found. Creating empty dictionary.");
        }
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
        string next = "";
        if(!dict.empty())
        {
            pair<dictmap::iterator, dictmap::iterator >  range = dict.equal_range(key);
            int count=0;
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
                std::advance(item, random_n_to_m(0, dict.size()) );
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
    void smart_module::put(const std::vector<std::string>& message)
    {
        std::string prev;
        std::string  next;
        bool begin = 1;
        prev = *(message.begin());
        for(auto it: message )
        {
            next = it;
            if(begin)
            {
                 begin = 0;
                 continue;
            }
            put(prev, next); 
            prev = next;

        }

    }

 void smart_module::generate_answer (const message::message_t& msg, 
			const std::string& args,  bot::bot_i* bot) 
    {

        using tools::tokenizer;
	const std::string text = msg.body();
	const std::string sender = msg.sender();
        //INFO(text.c_str());
        //string text = _text;
        tokenizer tok = tokenizer(text, delimiters);
        std::vector<std::string> tokens = tok.tokenize();
        if(tokens.size() != 0)
        {
            std::string nick = bot->get_room_nick();

            size_t pos = text.find_first_not_of(" \t\n");

            if(pos == text.find(nick))
            {
                tokens.erase(tokens.begin());
                std::string begin = tokens.at(random_n_to_m(0, tokens.size()));

                INFO(begin.c_str());

                std::string answer = generate(begin, random_n_to_m(2, 8));
                bot->send(message::message_t(sender +", " +answer, msg.priv()));

            }

            put(tokens);
        }
    }

   string smart_module::generate(const string& begin, int length)
    {
        string answer;
        string token = begin;
        bool end = 0;
        for(int i= 0; i< length; i++)
        {

            token = get_next(token);
            answer+=token + " ";
            switch(token[token.size()-1])
            {
                case ',':
                    token[token.size()-1] ='.';
                    end =1;
                    break;
                case '.':
                    end =1;
                    break;
                case '!':
                    end =1;
                    break;
                case '?':
                    end =1;
                    break;
                default:
                    break;
            }
            if(end)
            {
                break;
            }
        }
        return answer;
    }

    int smart_module::random_n_to_m(int n, int m)
    {
       // srand ( time(NULL) );
        return ((rand())%(m -n)) + n ;
    }
    
    smart_module::smart_module(const std::string& _dictionary_file)
    { 
       srand ( time(NULL) );
       dictionary_file = _dictionary_file;
       read();

    }
    smart_module::~smart_module()
    {
        dump();
    }
}
