#define DEFAULT_MODULE_NAME "!ping"
#include "defaultmodule.h"
#include <string>
#include <map>
class ModuleExecutor
    {
        public:
            ModuleExecutor(); 
            void reg(std::string const& name, Module* module);
            std::string exec(const std::string& keyword,
                                             const std::string& sender,
                                             const std::string& message );
            ~ModuleExecutor();
        
        private:

            typedef std::map<std::string, Module*> modules_container;
            modules_container modules;
            Module* m_default;
     };
