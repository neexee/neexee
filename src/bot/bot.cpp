#include "../core/core_module.h"
#include "../core/module_handler.h"

#include "bot.h"

#include <iostream>
#include <vector>

struct B : public ::neexee::CoreModule,
           public ::neexee::bot::Bot,
           public ::neexee::bot::EventNotify
{
	std::vector<neexee::ModuleHandler<neexee::bot::Proto>> protocols;
	std::vector<neexee::ModuleHandler<neexee::bot::Chatmodule>> chatmodules;

	B()
	{
		for(auto i: {"./stdio_proto.so"})
			protocols.push_back(neexee::ModuleHandler<neexee::bot::Proto>(i));

		for(auto i: {"./test_module.so"})
			chatmodules.push_back(neexee::ModuleHandler<neexee::bot::Chatmodule>(i));
	}
	~B()
	{
	}
	void neexee_CoreModule_start()
	{
		for(auto i: protocols)
			i->start(this);

		for(auto i: chatmodules)
			i->start();
	}
	void neexee_CoreModule_stop()
	{
		for(auto i: protocols)
			i->stop();

		for(auto i: chatmodules)
			i->stop();
	}
	void neexee_bot_EventNotify_notify(std::shared_ptr< ::neexee::bot::event::Event> e)
	{
		for(auto i: chatmodules)
			i->notify(e);
	}
};

NEEXEE_MODULE_EXTERNS(B, neexee::CoreModule)
