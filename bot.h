#include <gloox/client.h>
#include <gloox/messagehandler.h>
#include <gloox/message.h>
#include <gloox/mucroom.h>
#include <gloox/connectionlistener.h>
#include <gloox/disco.h>
#include <gloox/mucroomhandler.h>

#include <string>
#include <iostream>
#include "settings.h"

using namespace gloox;
class Bot : public MessageHandler, gloox::ConnectionListener, gloox::MUCRoomHandler  
{
    public:
    Bot( Settings& sets);
    
    ~Bot();
    
    void connect();
    
    protected:

    virtual void handleMessage( const Message& stanza, MessageSession* session = 0 );
    
    virtual void onConnect();
    
    virtual void onDisconnect( gloox::ConnectionError e );
    
    virtual bool onTLSConnect( const gloox::CertInfo& );
    
    virtual void handleMUCMessage (MUCRoom *room, const Message &msg, bool priv); 

    virtual void handleMUCParticipantPresence(gloox::MUCRoom*, 
                                              gloox::MUCRoomParticipant, 
                                              const gloox::Presence&){}
    
    virtual bool handleMUCRoomCreation(gloox::MUCRoom*){}

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
    Client* j;
    MUCRoom *room;
    Settings settings;
};
