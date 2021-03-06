#ifndef MODULEEXECUTOR_HPP
#define  MODULEEXECUTOR_HPP
#include "../module/module.h"
#include "../settings/settings.h"
#include "../message/message.h"
#include <string>
#include <map>
#include <vector>
#include <pthread.h>
#include <semaphore.h>
namespace module
{
    class module_executor
    {
        public:
            module_executor(bot::bot_i* _bot); 
            void reg(const  std::string& keyword,
                    module_i* module, 
                    const std::string& command
                    = std::string());

            void register_modules();

            void exec( const message::message_t& msg);
            static  void* module_handler(void* _data);


            void* generate_data( const message::message_t& msg,
                                 const std::string& args,
                                 module_i* module);
            std::string get_help_for_registered_modules();

            ~module_executor();

        private:
            void clear_threads();
            void thread_ready(pthread_t* thread);

            typedef std::map<std::string, module_i*> modules_container;
            typedef std::map<std::string, std::string> command_container; /*keyword/command */

            modules_container modules;
            command_container commands;
            std::vector<pthread_t*> ready_threads;
            sem_t thread_counter;
            pthread_mutex_t ready_thread_mutex;
            pthread_t* handler_thread;

            bot::bot_i* bot;
            settings::settings_t* settings;
            std::vector<module_i*> default_modules;
    };
}
#endif
