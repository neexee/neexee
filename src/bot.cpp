#include "bot.h"
#include "debug/debug.h"
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>
#include "module/ping.h"
#include "module/asyncmodule.h"
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
        registerModules();
    }

void Bot::connect()
    {
        j->connect();
    }
std::vector<std::string> Bot::tokenize(const std::string& message)
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
        if(token_vector.front().compare(room->nick()) == 0)
                {
                    token_vector.erase(token_vector.begin());
                }
        //BUG, nick can contain SEPARATORS
        return token_vector;

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
     return true;
    }

void Bot::handleMUCMessage (MUCRoom *room, const Message &msg, bool priv)
    {
       if (!msg.when() && msg.from().resource().compare(room->nick()))
        {
            /*
           if (msg.body() == "!ping")
           {
             std::string pong = "pong to ";
              room->send(pong.append(msg.from().resource()));
           }
           if (!msg.body().compare(0, 4, "!say ", 0, 4))
              room->send(msg.body().substr(5));       


           if (!msg.body().compare(0, 2, "!ko", 0, 2))
               room->send("/me прокукарекал что-то в сторону " + msg.body().substr(3));
            */
            INFO("Handling room message");
            std::vector<std::string> tokens = tokenize(msg.body());
            room->send(executor.exec( msg.from().resource(),tokens));
            

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
void Bot::registerModules()
    {
        //settings read
        //test
        INFO("Registering Ping");
        executor.reg("!ping", new Ping());
        INFO("Registering bash script");
        executor.reg("!ko", new AsyncModule(), "bash ~/ko.sh");

    }
