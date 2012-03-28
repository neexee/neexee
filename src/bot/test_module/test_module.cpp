#include "../../core/core_module.h"
#include "../bot.h"

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

struct M : neexee::bot::Chatmodule
{
	M()
	{
	}
	~M()
	{
	}
	void neexee_bot_Chatmodule_notify(std::shared_ptr<neexee::bot::event::Event> e)
	{
		auto t = dynamic_cast<neexee::bot::message::Text*>(e.get());
		auto r = dynamic_cast<neexee::bot::event::Reply*>(e.get());
		if(t && r)
		{
			if(t->getText().find("lisp") != std::string::npos)
			{
				std::string ans = "'(qooqureqooe)";
				r->reply( std::shared_ptr<neexee::bot::message::Message>(new T(ans)) );
			}
		}
	}
};

NEEXEE_MODULE_EXTERNS(M, neexee::bot::Chatmodule)
