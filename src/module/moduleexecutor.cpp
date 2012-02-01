#include "moduleexecutor.h"
#include "defaultmodule.h"
#include "../debug/debug.h"

ModuleExecutor::ModuleExecutor()
     {
         m_default = new  DefaultModule();
     }


void ModuleExecutor::reg(const std::string& keyword,
                         Module* module,
                         const std::vector<std::string>& command
                         )
    {
        auto command_ = std::make_shared<std::vector<std::string> >(command);

        INFO(std::string("Registering"+ keyword).c_str());

        if(std::string(SYNC_MODULE).compare(command.front()) != 0)
           {
                commands[keyword]  = command_;
           }

        if(std::string(DEFAULT_MODULE_NAME).compare(keyword) == 0)
           {
               INFO(std::string("Registered default module with keyword "+ keyword).c_str());
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
                                const  std::vector<std::string>& message )
    {
        INFO("Executing command");
        std::string keyword = message.front();
        std::vector<std::string> str = message;

        INFO(std::string("Keyword = " + keyword).c_str());
        INFO(std::string("Sender = " + sender ).c_str());

        command_container::iterator executable = commands.find(keyword); 

        if( executable != commands.end() )
            {

                str = *(executable->second);
                //std::vector<std::string>::iterator it;

                for( std::string it: message)
                    {
                        str.push_back(it);
                    }
            }

        modules_container::iterator it = modules.find(keyword) ;

        if( it != modules.end())
            {
                INFO(std::string ("Picked up keyword: "+ keyword).c_str());
                return (it->second)->generate_answer(sender, str);
            }

         INFO("Calling default module");
         m_default->generate_answer(sender, str);
         return "";

    }