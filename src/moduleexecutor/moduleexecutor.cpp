#include "moduleexecutor.h"
#include <cstring>
#include <typeinfo>
#include <stdexcept>
#include <sstream>
#include "../tools/tokenizer.h"
#include "../debug/debug.h"
#include "../module/pluginexecutor/pluginexecutor.h"
#include "../module/defaultmodule.h"
#include "../module/help/helpmodule.h"
#include "../module/smart/smartmodule.h"
#ifdef ENABLE_KOKO
#include "../module/koko/kokomodule.h"
#endif
#include "../module/who/whomodule.h"
#include "../module/ping/ping.h"

namespace
{
    const std::string DEFAULT_MODULE_NAME =  "";
    //const std::string SYNC_MODULE =  "sync";
}
namespace module
{  
    typedef struct data_t
    {
        module_i* module;
        const std::string* sender;
        std::string* message;
        std::string* args;
        bot::bot_i* bot;
        pthread_t* thread;
        module_executor* executor;

    }data_t;
    
    module_executor::module_executor(bot::bot_i* _bot)
    {
        bot = _bot;
//        m_default = new  default_module();
        if(0 != pthread_mutex_init(&ready_thread_mutex, NULL))
        {
            throw std::runtime_error(strerror(errno));
        }

        if(0 != sem_init(&thread_counter, 0, 200)) //200 threads available
        {
            pthread_mutex_destroy(&ready_thread_mutex);
            throw(std::runtime_error(strerror(errno)));
        }

        settings = _bot->get_settings();

    }


    void module_executor::reg( const std::string& keyword,
            module_i* module,
            const std::string& command )
    {


        if(DEFAULT_MODULE_NAME.compare(keyword) == 0)
        {
            INFO(std::string("Registered default module "+ keyword).c_str());
            default_modules.push_back(module);
        }
        else
        {

        INFO(std::string("Registering keyword "+ keyword).c_str());

            modules[keyword] = module;

            if(typeid(*module) ==typeid(plugin_executor))
            {
                commands[keyword] = command;
            }

        }

    }
    void module_executor::register_modules()
    {
        using module::smart_module;
        using tools::tokenizer;
        
        reg("!help", new module::help_module());
        INFO("Registering Ping");
        reg("!ping", new ping());

        smart_module* smart = new smart_module("dictionaries/dict");
        reg("", smart);

#ifdef KOKO_MODULE

        reg("", new module::koko_module());

#endif

        reg("!who", new module::who_module());

        INFO("Registering external modules");
        std::string external_modules;
        try
        {
            external_modules = settings->get_value_of_key<std::string>(EXTERNAL_MODULES_KEYWORD);
        }
        catch(const std::runtime_error& e)
        {
            WARNING("Plugins disabled :<");
            return;
        }
        tokenizer _tokenizer = tokenizer(external_modules);
        std::vector<std::string> keywords = _tokenizer.tokenize();
        for(auto it : keywords)
        {
            std::string command;
            try
            {
                command = settings->get_value_of_key<std::string>(it);
            }
            catch(const std::runtime_error& e)
            {
                ERROR(std::string(e.what() + std::string(" not found in config")).c_str());
                continue;
            }
            size_t comment_pos = command.find("/*");
            if(comment_pos != std::string::npos)
            {
                size_t pos_end_args = command.find("//");
                if(pos_end_args != std::string::npos)
                {
                    command.erase(comment_pos);
                }
            }
            INFO(command.c_str());
            size_t endpos = command.find_last_not_of(" \t");
            if( std::string::npos != endpos )
            {
                command = command.substr( 0, endpos+1 );
            }
            reg(it, new plugin_executor(), command);
        }
    }

    module_executor::~module_executor()
    {
        for(auto it : modules)
        {
            delete  it.second;
        }
        for(auto it: default_modules)
        {
            delete it;
        }
        pthread_mutex_destroy(&ready_thread_mutex);
        sem_destroy(&thread_counter);

    }
    void module_executor::exec( const std::string& sender,
            const  std::string& _message )
    {
        using tools::tokenizer;

        std::string keyword;
        std::string args;
        tokenizer _tokenizer = tokenizer(_message);

        if(_tokenizer.next_token())
        {
            keyword = _tokenizer.get_token();
        }

        std::string message = _message;
        message.erase(0, keyword.length());
        command_container::iterator executable = commands.find(keyword); 

        if( executable != commands.end() )
        {
            args = executable->second;
        }

        modules_container::iterator it = modules.find(keyword) ;

        if( it != modules.end())
        {
            void* data = generate_data(sender, message, args, it->second);
            if(0 != pthread_create(((data_t*)data)->thread, NULL, module_executor::module_handler, data))

            {
                throw std::runtime_error(strerror(errno));
            }

        }
        else
        {
            for(auto def : default_modules)
            {
                void* data = generate_data(sender, _message, args, def);
                if(0 != pthread_create(((data_t*)data)->thread, NULL, module_executor::module_handler, data))

                {
                    throw std::runtime_error(strerror(errno));
                }


            }
        }
    }
    void* module_executor::generate_data(const std::string& sender,
            const  std::string& message,
            const std::string& args,
            module_i* module)
    {
        data_t* data = new data_t;
        data->module = module;
        data->sender = new std::string(sender);
        data->message = new std::string(message);
        data->args = new std::string(args);
        data->bot = bot;
        data->executor = this;
        data->thread = new pthread_t;
        return data;
    }

    std::string module_executor::get_help_for_registered_modules()
    {
        std::string answer;
        for(auto it : commands)
        {
            std::string command = settings->get_value_of_key<std::string>(it.first);
            answer+= it.first +" runs a "+ command + "\n";
        }
      return answer;
    }

    void* module_executor::module_handler(void* _data)
    {
        data_t* data = static_cast<data_t*>(_data);
        module_i* module = data->module;
        std::string sender = *(data->sender);
        std::string message = *(data->message);
        std::string args = *(data->args);
        bot::bot_i* bot = data->bot;
        module_executor* executor = data->executor;
        pthread_t* thread = data->thread;

        module->generate_answer(sender,args, message, bot);
        delete data->sender;
        delete data->args;
        delete data->message;
        delete data;
        executor->clear_threads();
        executor->thread_ready(thread);
        return NULL;
    }


    void module_executor::clear_threads()
    {
        pthread_mutex_lock(&ready_thread_mutex);
        int size = ready_threads.size();
        for(int i = 0; i < size; i++)
        {
            if(0 != pthread_join(*ready_threads[i], NULL))
            {
                ERROR(strerror(errno));
            }
            delete ready_threads[i];
            sem_post(&thread_counter);
            INFO("Thread complete");
        }
        ready_threads.clear();
        pthread_mutex_unlock(&ready_thread_mutex);
    }


    void module_executor::thread_ready(pthread_t* thread)
    {
        pthread_mutex_lock(&ready_thread_mutex);
        ready_threads.push_back(thread);
        pthread_mutex_unlock(&ready_thread_mutex);
    }

}
