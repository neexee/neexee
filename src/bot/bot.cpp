#include "../core/core_module.h"
#include "../core/module_handler.h"

#include "bot.h"

#include <iostream>
#include <vector>

struct B : public ::neexee::CoreModule,
           public ::neexee::bot::Bot,
           public ::neexee::bot::EventNotify
{
	::std::vector< ::neexee::ModuleHandler< ::neexee::bot::Proto>> protocols;
	B()
	{
		this->protocols.push_back(::neexee::ModuleHandler< ::neexee::bot::Proto>("./test.so"));
		for(auto i: this->protocols)
			i->start(*this);
		::std::cout << "Bot created." << ::std::endl;
	}
	~B()
	{
	}
	void neexee_CoreModule_start()
	{
	}
	void neexee_CoreModule_stop()
	{
	}
	void neexee_bot_EventNotify_notify(const ::neexee::bot::event::Event &e)
	{
		::std::cout << "Qooqureqooe!" << ::std::endl;
	}
};

NEEXEE_MODULE_EXTERNS(::B, ::neexee::CoreModule)
