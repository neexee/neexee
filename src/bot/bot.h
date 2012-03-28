#pragma once

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
	void notify(const ::neexee::bot::event::Event &e)
		{this->neexee_bot_EventNotify_notify(e);}
		virtual void neexee_bot_EventNotify_notify(const ::neexee::bot::event::Event &e) = 0;
};

struct neexee::bot::event::Event
{
};

struct neexee::bot::event::Reply
{
	void reply(const ::neexee::bot::message::Message &e)
		{this->neexee_bot_event_Reply_reply(e);}
		virtual void neexee_bot_event_Reply_reply(const ::neexee::bot::message::Message &e) = 0;
		// Динамикоговно: а вдруг чатмодуль ответит не тем типом сообщения?
};

struct neexee::bot::message::Message
{
	
};

struct neexee::bot::message::Text
{
	
};

struct neexee::bot::Proto
{
	void start(const ::neexee::bot::EventNotify &e)
		{this->neexee_bot_Proto_start(e);}
		virtual void neexee_bot_Proto_start(const ::neexee::bot::EventNotify &e) = 0;
};

struct neexee::bot::ChatModule
{
	//void no	
};
