#include "moduleexecutor.h"
#include "../debug/debug.h"
std::string ModuleExecutor::exec(const std::string& keyword,
                                 const std::string& sender,
                                 const std::string& message )
    {  
        INFO("Executing command");
        INFO(std::string("Keyword = " + keyword).c_str());
        INFO(std::string("Sender = " + sender ).c_str());
        INFO(std::string("Message = " + message).c_str());


        modules_container::iterator it;
        if(( it = modules.find(keyword) ) != modules.end())
            {
                INFO(std::string ("Picked up keyword"+ keyword).c_str());
                return (it->second)->generate_answer(sender, message);
            }
        else
             {
                 INFO("Calling default module");
                  return m_default->generate_answer(sender, message);
             }
    }

ModuleExecutor::ModuleExecutor()
     {
         m_default = new  DefaultModule();
     }


void ModuleExecutor::reg(std::string const& name, Module* module)
    {
        if(std::string(DEFAULT_MODULE_NAME).compare(name) == 0)
           {
               m_default = module;
           }
        else
           {
               modules[name] = module;
           }
    }
ModuleExecutor::~ModuleExecutor()
    {
    }

