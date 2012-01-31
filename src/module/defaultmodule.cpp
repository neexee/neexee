#include "defaultmodule.h"
#include "../debug/debug.h"
std::string DefaultModule::generate_answer(const std::string& sender,
                                  const std::vector<std::string>& text)
    {
        return sender + std::string(", OH U!");
    }
