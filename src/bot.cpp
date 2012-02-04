#include "bot.h"
#include "debug/debug.h"
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>
#include "module/ping.h"
#include "module/defaultmodule.h"
#include "module/asyncmodule.h"
#include <stdexcept>
#include "modulehandler.h"
#include "named_socket/socket.h"
namespace bot
{
 typedef struct data_t{
 char * sockname;
 bot_t* bot;
 socket_local::socket_t* socket;
 sem_t  counter;
 }data_t;

    using  gloox::JID;
    using  gloox::Client;
    using  gloox::Message;



    bot_t::bot_t(Settings& sets)
    {
        if(0 != pthread_mutex_init(&ready_thread_mutex, NULL))
        {
            throw std::runtime_error(strerror(errno));
        }

        if(0 != sem_init(&thread_counter, 0, 200)) //200 threads available
        {
            pthread_mutex_destroy(&ready_thread_mutex);
            throw(std::runtime_error(strerror(errno)));
        }

        settings = sets;
        settings.getValueOfKey<std::string>("jid");
        
        JID jid(settings.getValueOfKey<std::string>("jid"));
        j = new Client( jid, settings.getValueOfKey<std::string>("pass"));
        j->disableRoster();
        j->setCompression(false);
        j->setPresence( gloox::Presence::Available, -1 );
        j->disco()->setVersion("PETUH", "0.0.1", "");
        j->disco()->setIdentity("kokoko", "bot");
        j->registerMessageHandler( this );
        j->registerConnectionListener( this );
    }

    void bot_t::connect()
    {
        j->connect();
    }
    std::vector<std::string> bot_t::tokenize(const std::string& message)
    {
        using std::vector;
        using std::string;
        using boost::char_separator;
        using boost::tokenizer;
        vector<string> token_vector;
        char_separator<char> sep(SEPARATORS);
        tokenizer< char_separator<char> > tokens(message, sep);

        INFO("Addded tokens");

        for(tokenizer<char_separator<char> >::iterator it=tokens.begin(); it!=tokens.end();++it)
        {
            token_vector.push_back(*it);
            INFO((*it).c_str());

        }
        //        if(token_vector.front().compare(room->nick()) == 0)
        //              {
        //                  token_vector.erase(token_vector.begin());
        //              }
        //BUG, nick can contain SEPARATORS
        return token_vector;

    }
    bot_t::~bot_t()
    {
        delete j;
        delete room;
    } 

    void bot_t::handleMessage( const Message& stanza,
            MessageSession* session)
    {
        Message msg (Message::Chat, stanza.from(), "KOKOKOKOKO" );
        j->send( msg );
    }

    void bot_t::onDisconnect( gloox::ConnectionError e )
    {
        std::cout << " EГГОГ : " << e << '\n';
    }

    bool bot_t::onTLSConnect( const gloox::CertInfo& )
    {
        return true;
    }

    void bot_t::handleMUCMessage (MUCRoom *room, const Message &msg, bool priv)
    {
        if (!msg.when() && msg.from().resource().compare(room->nick()))
        {

            INFO("Handling room message");
            std::vector<std::string> tokens = tokenize(msg.body());
            executor->exec( msg.from().resource(),tokens); 
        }

    }
    void bot_t::onConnect()
    {
        std::cout << "Connected" << std::endl;
        room = new MUCRoom( j, settings.getValueOfKey<std::string>("room"), 0, 0 );
        room->join();

        room->send(FIRST_MESSAGE);
        room->registerMUCRoomHandler(this);
        register_modules();
        handler_thread = new pthread_t;
        data_t* test = new data_t;
        test->sockname = SOCKNAME;
        test->bot = this;
        test->counter = thread_counter;
        test->socket= new socket_local::socket_t;
        auto koko = this;
       if(0 != pthread_create(handler_thread, NULL, bot_t::modules_handler, (void *)test))

        {
            throw std::runtime_error(strerror(errno));
        }

    }
    void bot_t::register_modules()
    {
        //settings read
        executor = new ModuleExecutor(SOCKNAME);
        INFO("Registering Ping");
        executor->reg("!ping", new Ping());
        INFO("Registering bash script");

        executor->reg("!ko", new AsyncModule(),\
                std::vector<std::string>({"/bin/bash","/home/violetta/ko.sh"}));

        executor->reg("!py", new AsyncModule(),\
                std::vector<std::string>({"/usr/bin/python3","/home/violetta/best_os.py"}));

        executor->reg(room->nick(), new DefaultModule());

        executor->reg("!blya", new AsyncModule(),\
                std::vector<std::string>({"/bin/zsh","/home/violetta/sovet.sh"}));


    }
    void bot_t::send(const std::string& message)
    {
        room->send(message);
    }

    void* bot_t::modules_handler(void* _data)
    {
        
        using socket_local::socket_t;
        using std::runtime_error;
        
        data_t* data = static_cast<data_t*>(_data);
        char * socketname = data->sockname;
        bot_t* bot  = data->bot;
        sem_t thread_counter = data->counter;
        socket_t* server_socket = data->socket;
        delete data;
        
        INFO("Binding server socket");
        server_socket->bind(socketname);
        server_socket->listen();

        while(true)

        {
            socket_t client_socket;
            try
            {
                client_socket = server_socket->accept();
            }
            catch(const runtime_error& error)
            {
                ERROR(error.what());
                continue;
            }
            INFO("New module connected");
            pthread_t* thread = new pthread_t;
            sem_wait(&thread_counter);
            try
            {
                INFO("Make new module thread");
                module_handler::start(client_socket, thread, bot);
            }
            catch(const runtime_error& error)
            {
                ERROR(error.what());
                delete thread;
                sem_post(&thread_counter);
            }
        }
    }



    void bot_t::clear_threads()
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


    void bot_t::thread_ready(pthread_t* thread)
    {
        pthread_mutex_lock(&ready_thread_mutex);
        ready_threads.push_back(thread);
        pthread_mutex_unlock(&ready_thread_mutex);
    }

}
