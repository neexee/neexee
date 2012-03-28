#include "../core/core_module.h"
#include "../core/module_handler.h"

#include "bot.h"

#include <iostream>
#include <vector>

struct T : public neexee::bot::message::Message,
           public neexee::bot::message::Text
{
	const std::string &text;
	T(const std::string &text) : text(text)
	{
	}
	std::string neexee_bot_message_Text_getText()
	{
		return text;
	}
};

struct B : public ::neexee::CoreModule,
           public ::neexee::bot::Bot,
           public ::neexee::bot::EventNotify
{
	std::vector<neexee::ModuleHandler<neexee::bot::Proto>> protocols;
	B()
	{
		protocols.push_back(neexee::ModuleHandler<neexee::bot::Proto>("./stdio_proto.so"));
		for(auto i: protocols)
			i->start(this);
	}
	~B()
	{
		for(auto i: protocols)
			i->stop();
	}
	void neexee_CoreModule_start()
	{
	}
	void neexee_CoreModule_stop()
	{
	}
	void neexee_bot_EventNotify_notify(::neexee::bot::event::Event *e)
	{
		auto t = dynamic_cast<neexee::bot::message::Text*>(e);
		auto r = dynamic_cast<neexee::bot::event::Reply*>(e);
		if(t && r)
		{
			r->reply(new T(t->getText()));
		}
		delete e;
	}
};

NEEXEE_MODULE_EXTERNS(B, neexee::CoreModule)
