#include "bot.h"
using namespace gloox;
Bot::Bot(Settings& sets)
    {   
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

void Bot::connect()
    {
        j->connect();
    }
Bot::~Bot()
    {
         delete j;
         delete room;
    } 

void Bot::handleMessage( const Message& stanza,
            MessageSession* session)
    {
        Message msg (Message::Chat, stanza.from(), "KOKOKOKOKO" );
        j->send( msg );
    }

void Bot::onDisconnect( gloox::ConnectionError e )
    {
         std::cout << " EГГОГ : " << e << '\n';
    }

bool Bot::onTLSConnect( const gloox::CertInfo& )
    {

    }

void Bot::handleMUCMessage (MUCRoom *room, const Message &msg, bool priv)
    {
       if (!msg.when() && msg.from().resource().compare(room->nick()))
        {
           if (msg.body() == "!ping")
           {
             std::string pong = "pong to ";
              room->send(pong.append(msg.from().resource()));
           }
           if (!msg.body().compare(0, 4, "!say ", 0, 4))
              room->send(msg.body().substr(5));       


           if (!msg.body().compare(0, 2, "!ko", 0, 2))
               room->send("/me прокукарекал что-то в сторону " + msg.body().substr(3));

         }


    }
void Bot::onConnect()
    {
        std::cout << "Connected" << std::endl;
        room = new MUCRoom( j, settings.getValueOfKey<std::string>("room"), 0, 0 );
        room->join();

        room->send("KOKOKOKOKO!");
        room->registerMUCRoomHandler(this);
    }
