#include <iostream>
#include <thread>
#include <unistd.h>
#include <stdlib.h>


#include "../../core/core_module.h"
#include "../bot.h"

struct P;

void f(P&);

struct E : public neexee::bot::event::Event,
           public neexee::bot::event::Reply,
           public neexee::bot::message::Message,
           public neexee::bot::message::Text
{
	const std::string &text;
	E(std::string text) : text(text)
	{
	}
	void neexee_bot_event_Reply_reply(::neexee::bot::message::Message *e)
	{
		auto t = dynamic_cast<neexee::bot::message::Text*>(e);
		if(t)
			std::cout << "> " << t->getText() << std::endl;
		else
			std::cout << "***" << std::endl;
		delete e;
	}
	std::string neexee_bot_message_Text_getText()
	{
		return text;
	}
};

struct P : public neexee::bot::Proto
{
	neexee::bot::EventNotify *e = NULL;
	P()
	{
	}
	~P()
	{
	}
	void neexee_bot_Proto_start(neexee::bot::EventNotify *e)
	{
		this->e = e;
		std::thread t(f, std::ref(*this));
		t.detach();
	}
	void neexee_bot_Proto_stop()
	{
	}
};

void f(P& p)
{
	std::string s;
	while(1)
	{
		std::getline(std::cin, s);
		//std::shared_ptr< neexee::bot::event::Event> e(new E(s));
		p.e->notify(new E(s));
	}
}

NEEXEE_MODULE_EXTERNS(::P, ::neexee::bot::Proto)
