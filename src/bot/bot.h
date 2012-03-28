#pragma once

#include <memory>

namespace neexee
{
	namespace bot
	{
		class Bot;
		class EventNotify;
		namespace event
		{
			class Event;
			class Reply;
		}
		namespace message
		{
			class Message;
			class Text;
		}
		class Proto;
		class ChatModule;
	}
}

struct neexee::bot::Bot
{
	
};

struct neexee::bot::EventNotify
{
	void notify(::neexee::bot::event::Event *e)
		{this->neexee_bot_EventNotify_notify(e);}
		virtual void neexee_bot_EventNotify_notify(::neexee::bot::event::Event *e) = 0;
};

struct neexee::bot::event::Event
{
	virtual void k(){};
};

struct neexee::bot::event::Reply
{
	void reply(::neexee::bot::message::Message *e)
		{this->neexee_bot_event_Reply_reply(e);}
		virtual void neexee_bot_event_Reply_reply(::neexee::bot::message::Message *e) = 0;
};

struct neexee::bot::message::Message
{
	virtual void k(){};
};

struct neexee::bot::message::Text
{
	::std::string getText()
		{return this->neexee_bot_message_Text_getText();}
		virtual ::std::string neexee_bot_message_Text_getText() = 0;
};

struct neexee::bot::Proto
{
	void start(::neexee::bot::EventNotify *e)
		{this->neexee_bot_Proto_start(e);}
		virtual void neexee_bot_Proto_start(::neexee::bot::EventNotify *e) = 0;

	void stop()
		{this->neexee_bot_Proto_stop();}
		virtual void neexee_bot_Proto_stop() = 0;
};

struct neexee::bot::ChatModule
{
	void notify(const neexee::bot::event::Event &e)
		{this->neexee_bot_ChatModule_notify(e);}
		virtual void neexee_bot_ChatModule_notify(const neexee::bot::event::Event &e);
};
