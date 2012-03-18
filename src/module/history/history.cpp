#include <iostream>
#include <fstream>
#include <vector>
#include "../../debug/debug.h"
#include "history.h"
#include <stdlib.h>
#include <time.h>
#include <utility>
namespace module
{
    using std::string;
    using std::vector;
    void history::dump()
    {
        std::ofstream backup;
        backup.open(history_file_name.c_str(), std::ofstream::app);
        for( auto it: hist )
        {
          backup<< it.first;
        }
        backup.close();
    }
    void history::put(message::message_t& entry)
    {
       int date = 1;
       hist.push_back(hist_entry(1, entry));
    }
    void history::generate_answer(const message::message_t& msg, const std::string& args,
            bot::bot_i* bot)
    {
    }
    history::~history()
    {
        dump();
    }
}
