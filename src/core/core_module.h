#include "module.h"

namespace neexee
{
	class CoreModule;
}

struct neexee::CoreModule
{
	void start()
		{this->neexee_CoreModule_start();}
		virtual void neexee_CoreModule_start() = 0;
	void stop()
		{this->neexee_CoreModule_stop();}
		virtual void neexee_CoreModule_stop() = 0;
};
