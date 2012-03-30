#ifndef BOT_HPP
#define BOT_HPP
#include <gloox/client.h>
#include <gloox/messagehandler.h>
#include <gloox/message.h>
#include <gloox/mucroom.h>
#include <gloox/connectionlistener.h>
#include <gloox/disco.h>
#include <gloox/mucroomhandler.h>
#include <gloox/mucroomconfighandler.h>
#include <vector>
#include <string>
#include <iostream>
#include <ctime>
#include <pthread.h>
#include <semaphore.h>
#include <gloox/eventhandler.h>
#include "botinterface.h"
#include "../settings/settings.h"
#include "../moduleexecutor/moduleexecutor.h"
#include "query.h"
namespace bot
{
    class bot_t : public gloox::MessageHandler, gloox::ConnectionListener,
                  gloox::MUCRoomHandler, gloox::MUCRoomConfigHandler, gloox::EventHandler, bot_i  
    {
        public:
            bot_t(settings::settings_t& sets);
            ~bot_t();
            void connect();
            virtual void send(const message::message_t& message);
            virtual std::string get_room_nick();
            virtual void  get_room_names();
            virtual settings::settings_t* get_settings();
            virtual void get_help();
            virtual void ping(const std::string jid);
              


        protected:
            /*MessageHandler*/
            virtual void handleMessage( const gloox::Message& stanza, gloox::MessageSession* session = 0 );

            /*ConnectionListener*/
            virtual void onConnect();
            virtual void onDisconnect( gloox::ConnectionError e );
            virtual bool onTLSConnect( const gloox::CertInfo& );
            /*gloox::MUCRoomHandler*/
            virtual void handleMUCMessage (gloox::MUCRoom *room, const gloox::Message &msg, bool priv); 
            virtual void handleMUCParticipantPresence(gloox::MUCRoom*,
                    gloox::MUCRoomParticipant,
                    const gloox::Presence&);

            virtual bool handleMUCRoomCreation(gloox::MUCRoom*);

            virtual void handleMUCSubject(gloox::MUCRoom*,
                    const std::string&,
                    const std::string&);

            virtual void handleMUCInviteDecline(gloox::MUCRoom*,
                    const gloox::JID&,
                    const std::string&);

            virtual void handleMUCError(gloox::MUCRoom*,
                    gloox::StanzaError);

            virtual void handleMUCInfo(gloox::MUCRoom*,
                    int, const std::string&,
                    const gloox::DataForm*);
            virtual void handleMUCItems(gloox::MUCRoom*,
                    const std::list<gloox::Disco::Item*>& items);

            /*MUCRoomConfigHandler*/
            virtual void handleMUCConfigForm (gloox::MUCRoom *   room, 
                            const gloox::DataForm & form);

            virtual void handleMUCConfigResult ( gloox::MUCRoom * room, 
                    bool success, gloox::MUCOperation operation);

            virtual void handleMUCRequest ( gloox::MUCRoom * room,
                    const gloox::DataForm & form);
            virtual void handleMUCConfigList( gloox::MUCRoom* room, const gloox::MUCListItemList& items,
                                         gloox::MUCOperation operation );
            /*For ping*/
            virtual void handleEvent(const gloox::Event&   event);
        private:

            gloox::Client* client;
            gloox::MUCRoom *room;
            std::string roomname;
            std::string nick;
            query::query_t quer;
            settings::settings_t settings;
            module::module_executor* executor;
            time_t start;
    };
}
#endif
