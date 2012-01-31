#define DEFAULT_MODULE_NAME "!ping"
#define SYNC_MODULE "sync" 
#include "module.h"
#include <string>
#include <map>
#include <vector>
class ModuleExecutor
    {
        public:
            ModuleExecutor(); 
            void reg(const  std::string& keyword,
                     Module* module, 
                     const std::string& command = std::string(SYNC_MODULE));
            std::string exec( const std::string& sender,
                                             std::vector<std::string>& message );

            ~ModuleExecutor();
        
        private:

            typedef std::map<std::string, Module*> modules_container;
            typedef std::map<std::string, std::string*> command_container; /*keyword/command */
            modules_container modules;
            command_container commands;

            Module* m_default;
     };
