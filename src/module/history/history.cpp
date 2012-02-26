#include <iostream>
#include <fstream>
#include <vector>
#include "../../debug/debug.h"
#include "history.h"

#include <stdlib.h>
#include <time.h>
namespace module
{
    using std::string;
    using std::vector;
    void history::dump()
    {
        std::ofstream backup;
        backup.open(dictionary_file.c_str(), std::ofstream::app);
        for(auto it: hist)
        {
        }
        backup.close();
    }
    void history::put(const string& entry)
    {
       string date = "";
       hist.push_back( new hist_entry(date, entry));
    }
    void smart_module::generate_answer(const std::string& sender, const std::string& args,
            const std::string& _text, bot::bot_i* bot)
    {
    }



    history::~history()
    {
        dump();
    }
}
