#include "moduleexecutor.h"
#include "defaultmodule.h"
#include "../debug/debug.h"

ModuleExecutor::ModuleExecutor()
     {
         m_default = new  DefaultModule();
     }


void ModuleExecutor::reg(const std::string& keyword,
                         Module* module,
                         const std::string& command )
    {   
        std::string* command_ = new std::string(command);
        std::string key = keyword;
        INFO("Registering");
        INFO(keyword.c_str());
        if(std::string(SYNC_MODULE).compare(command) != 0)
           {
                commands[key]  = command_;
               //commands.insert(std::pair<std::string,std::string>(key,command_));

           }
        
        
        if(std::string(DEFAULT_MODULE_NAME).compare(keyword) == 0)
           {
               m_default = module;
           }
        else
           {
               modules[keyword] = module;
           }
        
    }
ModuleExecutor::~ModuleExecutor()
    {
    }
std::string ModuleExecutor::exec( const std::string& sender,
                                 std::vector<std::string>& message )
    {  
 //       std::string keyword = message.front();
        INFO("Executing command");
        std::string keyword = message.front();

        INFO(std::string("Keyword = " + keyword).c_str());
        INFO(std::string("Sender = " + sender ).c_str());
        //INFO(std::string("Message = " + message).c_str());
        command_container::iterator ko = commands.find(keyword); 
        if( ko != commands.end() )
            {
                  message.front() = *(ko->second);
            }
         modules_container::iterator it = modules.find(keyword) ;
        if( it != modules.end())
            {
                INFO(std::string ("Picked up keyword"+ keyword).c_str());
                return (it->second)->generate_answer(sender, message);
            }
        
             
                  INFO("Calling default module");
                  return m_default->generate_answer(sender, message);
             
    }
