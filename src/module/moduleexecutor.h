#ifndef MODULEEXECUTOR_HPP
#define  MODULEEXECUTOR_HPP
#define SYNC_MODULE "sync"
#include "module.h"
#include <string>
#include <map>
#include <vector>
namespace module
{
    class ModuleExecutor
    {
        public:
            ModuleExecutor(const std::string&  _sockname); 
            void reg(const  std::string& keyword,
                    Module* module, 
                    const std::vector<std::string>& command\
                    = std::vector<std::string>(1, std::string(SYNC_MODULE)));
            void exec( const std::string& sender,
                    const   std::vector<std::string>& message );

            ~ModuleExecutor();

        private:

            typedef std::map<std::string, Module*> modules_container;
            typedef std::map<std::string, std::vector<std::string> > command_container; /*keyword/command */


            modules_container modules;
            command_container commands;

            std::string sockname;
            Module* m_default;
    };
}
#endif
