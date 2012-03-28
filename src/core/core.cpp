#include <vector>
#include <iostream>
#include <signal.h>
#include <unistd.h>

#include "core_module.h"
#include "module_handler.h"

static void nothing(int i)
{

}

int main(int argc, char **argv)
{
	::std::vector< ::std::string> module_names;
	for(int i = 1; i < argc; i++)
		module_names.push_back(argv[i]);

	::std::vector< ::neexee::ModuleHandler< ::neexee::CoreModule>> modules;
	for(auto i : module_names)
			modules.push_back(::neexee::ModuleHandler< ::neexee::CoreModule>(i));

	for(auto i : modules)
		i->start();

	::signal(SIGINT, nothing);
	::pause();

	for(auto i : modules)
		i->stop();
}
