#pragma once

#include <memory>
#include <string>

#define SP(x) std::shared_ptr<x>

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
		class Chatmodule;
	}
}

struct neexee::bot::Bot
{
	
};

struct neexee::bot::EventNotify
{
	void notify(SP(::neexee::bot::event::Event) e)
		{this->neexee_bot_EventNotify_notify(e);}
		virtual void neexee_bot_EventNotify_notify(SP(::neexee::bot::event::Event) e) {};
};

struct neexee::bot::event::Event
{
	virtual void k(){};
};

struct neexee::bot::event::Reply
{
	void reply(SP(::neexee::bot::message::Message) e)
		{this->neexee_bot_event_Reply_reply(e);}
		virtual void neexee_bot_event_Reply_reply(SP(::neexee::bot::message::Message) e) {};
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
		virtual void neexee_bot_Proto_start(::neexee::bot::EventNotify *e) {};

	void stop()
		{this->neexee_bot_Proto_stop();}
		virtual void neexee_bot_Proto_stop() {};
};

struct neexee::bot::Chatmodule
{
	void start()
		{this->neexee_bot_Chatmodule_start();}
		virtual void neexee_bot_Chatmodule_start() {};

	void stop()
		{this->neexee_bot_Chatmodule_stop();}
		virtual void neexee_bot_Chatmodule_stop() {};

	void notify(SP(::neexee::bot::event::Event) e)
		{this->neexee_bot_Chatmodule_notify(e);}
		virtual void neexee_bot_Chatmodule_notify(SP(::neexee::bot::event::Event) e) {};
};

#undef SP
