#ifndef BOT_HPP
#define BOT_HPP
#include <gloox/client.h>
#include <gloox/messagehandler.h>
#include <gloox/message.h>
#include <gloox/mucroom.h>
#include <gloox/connectionlistener.h>
#include <gloox/disco.h>
#include <gloox/mucroomhandler.h>
#include <vector>
#include <string>
#include <iostream>
#include <pthread.h>
#include <semaphore.h>

//#include "modulehandler.h"
#include "settings.h"
#include "module/moduleexecutor.h"
#include "named_socket/socket.h"
#define SEPARATORS " ,:"
#define FIRST_MESSAGE "Всем привет в этом чатике"
#define SOCKNAME "/tmp/bot.sock"
#define BOTNAME "neexee"
#define VERSION "0.0.3"
#define TYPE "bot"
namespace bot
{
    using namespace gloox;
    class bot_t : public MessageHandler, gloox::ConnectionListener, gloox::MUCRoomHandler  
    {
        public:
            bot_t(Settings& sets);
            ~bot_t();
            void thread_ready(pthread_t* thread);
            void clear_threads();
            void connect();
            void send(const std::string& message);            
            static void*  modules_handler(void * _socketname);


        protected:

            virtual void handleMessage( const Message& stanza, MessageSession* session = 0 );

            virtual void onConnect();

            virtual void onDisconnect( gloox::ConnectionError e );

            virtual bool onTLSConnect( const gloox::CertInfo& );

            virtual void handleMUCMessage (MUCRoom *room, const Message &msg, bool priv); 

            virtual void handleMUCParticipantPresence(gloox::MUCRoom*, 
                    gloox::MUCRoomParticipant, 
                    const gloox::Presence&){}

            virtual bool handleMUCRoomCreation(gloox::MUCRoom*){ return true;}

            virtual void handleMUCSubject(gloox::MUCRoom*,
                    const std::string&,
                    const std::string&){}

            virtual void handleMUCInviteDecline(gloox::MUCRoom*,
                    const gloox::JID&,
                    const std::string&){}

            virtual void handleMUCError(gloox::MUCRoom*,
                    gloox::StanzaError){}

            virtual void handleMUCInfo(gloox::MUCRoom*,
                    int, const std::string&,
                    const gloox::DataForm*){}
            virtual void handleMUCItems(gloox::MUCRoom*,
                    const std::list<gloox::Disco::Item*,
                    std::allocator<gloox::Disco::Item*> >&){}

        private:
            void register_modules();
            std::vector<std::string> tokenize(const std::string& message);

            Client* client;
            MUCRoom *room;
            Settings settings;
            ModuleExecutor* executor;
            std::vector<pthread_t*> ready_threads;
            socket_local::socket_t* server_socket;
            sem_t thread_counter;
            pthread_mutex_t ready_thread_mutex;
            pthread_t* handler_thread;
    };
}
#endif
