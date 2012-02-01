#define DEFAULT_MODULE_NAME "!what"
#define SYNC_MODULE "sync" 
#include "module.h"
#include <string>
#include <map>
#include <vector>
#include <memory>
#include <tr1/memory>
class ModuleExecutor
    {
        public:
            ModuleExecutor(); 
            void reg(const  std::string& keyword,
                     Module* module, 
                     const std::vector<std::string>& command\
                              = std::vector<std::string>(1, std::string(SYNC_MODULE)));
            std::string exec( const std::string& sender,
                                       const   std::vector<std::string>& message );

            ~ModuleExecutor();
        
        private:

            typedef std::map<std::string, Module*> modules_container;
            typedef std::map<std::string, std::shared_ptr<std::vector<std::string> > > command_container; /*keyword/command */
            modules_container modules;
            command_container commands;


            Module* m_default;
     };
