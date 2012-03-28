#pragma once

namespace neexee
{
	class Module
	{
		public:
		virtual ~Module() {};
		//virtual void onLoad() {};
		//virtual void onUnload() {};
	};
}

#define NEEXEE_MODULE_EXTERNS(name, basename) \
	extern "C" basename* load() { return new name(); } \
	extern "C" void unload(basename *i) { delete i; }

#define NEEXEE_MODULE_EXTERNS_SINGLETONE(name, basename) \
	static int MODULE_EXTERNS_COUNTER = 0; \
	static name* MODULE_EXTERNS_OBJ;\
	extern "C" basename* load() \
	{ \
		if(!MODULE_EXTERNS_COUNTER) \
			MODULE_EXTERNS_OBJ =  new name(); \
		MODULE_EXTERNS_COUNTER++; \
		return MODULE_EXTERNS_OBJ; \
	} \
	extern "C" void unload(basename *i) \
	{ \
		MODULE_EXTERNS_COUNTER--;\
		if(!MODULE_EXTERNS_COUNTER)\
			delete MODULE_EXTERNS_OBJ; \
	}
