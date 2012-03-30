#include <gloox/event.h>
#include "bot.h"
#include "../debug/debug.h"
#include "../console/console.h"
#include "../tools/tokenizer.h"
#include <stdexcept>
#include "../message/message.h"
#include <time.h>
#include "../settings/convert.h"
namespace
{
    const std::string BOTNAME =  "neexee";
    const std::string VERSION =  "0.0.4";
    const std::string TYPE =  "bot";

}
namespace bot
{
//    using  namespace gloox;
    using  gloox::Client;
    using  gloox::Message;
    using  gloox::MessageSession;
    using  gloox::MUCRoom;
    using  gloox::DataForm;
    using  gloox::MUCOperation;
    using  gloox::JID;
    using  gloox::MUCListItemList;

    using  settings::settings_t;
    using  tools::tokenizer;
    using  message::message_t;


    bot_t::bot_t(settings_t& sets)
    {
        std::string _jid;
        std::string _pass;

        settings = sets;
        try
        {
            _jid = settings.get_value_of_key<std::string>(JID_KEYWORD);
            _pass = settings.get_value_of_key<std::string>(PASSWORD_KEYWORD);
        }
        catch(const std::runtime_error& e)
        {
            ERROR(std::string(e.what() + std::string(" not found in config")).c_str());
            throw e;
        }

        JID jid(_jid);
        client  = new Client( jid, _pass);

        client->disableRoster();
        client->setCompression(false);
        client->setPresence( gloox::Presence::Available, -1 );
        client->disco()->setVersion(BOTNAME, VERSION);
        client->disco()->setIdentity(BOTNAME, TYPE);
        client->registerMessageHandler( this );
        client->registerConnectionListener( this );
    }

    bot_t::~bot_t()
    {
        delete room;
        delete client;
        delete executor;

    }

    void bot_t::connect()
    {
        client->connect();
    }

    void bot_t::onConnect()
    {
        INFO("Connection successful");
        std::string room_and_nick;
        try
        {
             room_and_nick = settings.get_value_of_key<std::string>(ROOM_KEYWORD);
        }
        catch(const std::runtime_error& e)
        {
            INFO("Room disabled :<");
        }
        room = new MUCRoom( client, room_and_nick, 0, 0 );
        room->join();
        roomname =room->name();
        room->registerMUCRoomHandler(this);
        executor = new module::module_executor(this);
        executor->register_modules();

        tools::tokenizer _tokenizer = tools::tokenizer(room_and_nick, "/");
        nick = _tokenizer.tokenize().at(1);
        INFO(nick.c_str());
        console::console_t* cons = new console::console_t(this);
        cons->start();

    }
    void bot_t::onDisconnect( gloox::ConnectionError e )
    {
        std::ostringstream ostr;
        ostr<< e;
        std::string error = ostr.str();
        ERROR(error.c_str());
        throw std::runtime_error(error);
    }

    bool bot_t::onTLSConnect( const gloox::CertInfo& )
    {
        return true;
    }
    void bot_t::handleMessage( const Message& stanza,
            MessageSession* session)
    {
        Message msg (Message::Chat, stanza.from(), stanza.body());
        client->send( msg );
    }

    void bot_t::handleMUCMessage (MUCRoom *room,
            const Message &msg, bool priv)
    {
        if (!msg.when() && msg.from().resource().compare(room->nick()))
        {

         //   INFO("Handling room message");
           // INFO(msg.from().full().c_str());
            executor->exec( message_t(msg.body(), priv, msg.from().resource(), msg.from().full())); 
        }

    }

    void bot_t::handleMUCRequest ( MUCRoom * room,
            const DataForm & form)
    {
    }

    void bot_t::handleMUCConfigResult ( MUCRoom * room, 
            bool success, 
            MUCOperation operation)
    {
    }
    void bot_t::handleMUCConfigList( MUCRoom* room, const MUCListItemList& items,
                                        MUCOperation operation )
    {
    }

    void bot_t::handleMUCConfigForm (gloox::MUCRoom *   room, 
            const gloox::DataForm & form)
    {
    }

    void bot_t::handleMUCItems(gloox::MUCRoom*,
            const std::list<gloox::Disco::Item*>& items)
    {
        std::string result = "Now in room:\n";
        for(auto item : items)
        {
            result+=item->name()+"\n";
        }
        send(message_t(result, 0));

    }

    void bot_t::handleMUCInfo(gloox::MUCRoom*,
            int, const std::string&,
            const gloox::DataForm*){}

    void bot_t::handleMUCError(gloox::MUCRoom*,
            gloox::StanzaError)
    {
    }

    void bot_t::handleMUCInviteDecline(gloox::MUCRoom*,
            const gloox::JID&,
            const std::string&)
    {
    }

    void bot_t::handleMUCSubject(gloox::MUCRoom*,
            const std::string&,
            const std::string&)
    {
    }

    bool bot_t::handleMUCRoomCreation(gloox::MUCRoom*)
    {
        return true;
    }

    void bot_t::handleMUCParticipantPresence(gloox::MUCRoom*,
            gloox::MUCRoomParticipant,
            const gloox::Presence&)
    {
    }
   
    settings::settings_t* bot_t::get_settings()
    {
        return &settings;
    }
    void bot_t::send(const message_t& message)
    {
      using gloox::Message;
      
        if(!message.priv())
        {
           room->send(message.body());
        }
        else
        {
          INFO("SEND MESSAGE");
          client->send(Message(Message::MessageType::Chat, message.full(), message.body()));
        }
    }

    std::string bot_t::get_room_nick()
    {
       return nick;
    }
    void bot_t::get_room_names()
    {
        room->getRoomItems ();
    }
   
    void bot_t::get_help()
    {
        using std::string;
        INFO("HELP");
        string answer = "This is a " +string(" ")+ string(BOTNAME) + string(TYPE) +". Now you can use following commands:\n";
        answer += executor->get_help_for_registered_modules();
        send(message::message_t(answer, 0));
    }
    void bot_t::ping(const std::string sender)
    {
        time(&start);
        client->xmppPing(sender,this);
    }
    void bot_t::handleEvent ( const gloox::Event& event )
    {
        time_t stop;
        std::string sender = event.stanza()->from().resource();
        time(&stop);
        double dif  = difftime(stop,start);
        send(message::message_t(sender +", ping to you " + settings::convert::T_to_string<double>(dif*1000) +" ms", 1, sender, event.stanza()->from().full()));

    }

}
