#pragma once

#include <exception>
#include <string>
#include <iostream>
#include <dlfcn.h>
#include <string.h>

#include "module.h"

namespace neexee
{
	class LoadModuleException;
	template<class T> class ModuleHandler;
}

class neexee::LoadModuleException : public std::exception
{
	char *w;
	public:
	LoadModuleException(std::string s)
	{
		w = strdup(s.c_str());
	}
	~LoadModuleException() noexcept (true)
	{
		free(w);
	}
	const char *what()
	{
		return w;
	}
};

template<class T> class neexee::ModuleHandler
{
	typedef T* Load();
	typedef void Unload(T*);
	const ::std::string filename;
	int *counter;

	Unload *unload;
	void *library;	
	T* instance;


	void del()
	{
		if(!this->instance)
			return;
		this->instance = NULL;

		(*this->counter)--;
		if(*this->counter > 0)
			return;
		//r->onUnload();
		this->unload(this->instance);
		delete this->counter;
		::dlclose(this->library);
	}
	void copy(const ModuleHandler<T> &o)
	{
		this->counter = o.counter;
		this->unload = o.unload;
		this->instance = o.instance;
		this->library = o.library;
		(*this->counter)++;
	}

	public:
	ModuleHandler() : filename(""), instance(NULL)
	{
	}
	ModuleHandler(const ::std::string &filename) : filename(filename)
	{
		this->counter = new int;
		*this->counter = 1;
		char *error;
		this->library = ::dlopen(filename.c_str(), RTLD_LAZY | RTLD_GLOBAL);
		if(!this->library)
		{
			delete counter;
			::std::string s = ::std::string("[1]") + ::dlerror();
			throw ::neexee::LoadModuleException(s);
		}
		dlerror();

		auto load = (Load*)::dlsym(this->library, "load");
		error = ::dlerror();
		if(error)
		{
			::std::string s = std::string("[2]") + error;
			delete counter;
			::dlclose(this->library);
			throw ::neexee::LoadModuleException(s);
		}

		this->unload = (Unload*)dlsym(library, "unload");
		error = ::dlerror();
		if(error)
		{
			std::string s = std::string("[3]") + error;
			delete counter;
			::dlclose(this->library);
			throw ::neexee::LoadModuleException(s);
		}

		try
		{
			this->instance = load();
		}
		catch(...)
		{
			//dlclose(this->library);
			delete counter;
			throw;
		}
		//r->onLoad();
	}
	ModuleHandler(const ModuleHandler<T> &o) : filename(o.filename)
	{
		copy(o);
	}
	ModuleHandler<T>& operator=(const ModuleHandler<T> &o)
	{
		del();
		copy(o);
	}
	~ModuleHandler()
	{
		del();
	}
	T* operator ->()
	{
		return this->instance;
	}
};
