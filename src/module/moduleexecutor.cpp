#include "moduleexecutor.h"
#include "defaultmodule.h"
#include <cstring>
#include "../debug/debug.h"
namespace module
{
    ModuleExecutor::ModuleExecutor(const std::string& _sockname)
    {
        sockname = _sockname;
        m_default = new  DefaultModule();
    }


    void ModuleExecutor::reg(const std::string& keyword,
            Module* module,
            const std::vector<std::string>& command
            )
    {

        INFO(std::string("Registering keyword "+ keyword).c_str());

        if(std::string(SYNC_MODULE).compare(command.front()) != 0)
        {
            commands[keyword]  = command;
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
        for(auto it : modules)
        {
            delete  it.second;
        }
        delete m_default;
    }
    void ModuleExecutor::exec( const std::string& sender,
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

            str = executable->second;

            for( std::string it: message)
            {
                str.push_back(it);
            }
        }

        modules_container::iterator it = modules.find(keyword) ;

        if( it != modules.end())
        {
            INFO(std::string ("Picked up keyword: "+ keyword).c_str());
            (it->second)->generate_answer(sender, str, sockname);
        }
        else
        {
            INFO("Calling default module");
            m_default->generate_answer(sender, str, sockname) ;
        }
    }
}
