#include <iostream>
#include <thread>
#include <unistd.h>
#include <stdlib.h>


#include "../../core/core_module.h"
#include "../bot.h"

void f()
{
	::usleep(1000);
	for(int i = 0; i < 10; i++)
	{
		::std::cout << i << ::std::endl;
	}
}

struct P : public ::neexee::bot::Proto
{
	const ::neexee::bot::EventNotify *e = NULL;
	P()
	{
	}
	~P()
	{
	}
	void neexee_bot_Proto_start(const ::neexee::bot::EventNotify &e)
	{
		this->e = &e;
		std::thread t {f};
		t.detach();
		//this->e->notify(::neexee::bot::event::Event());
	}
};

NEEXEE_MODULE_EXTERNS(::P, ::neexee::bot::Proto)
