CXXFLAGS=-std=c++11 -g
LDFLAGS=-lstdc++ -ldl

bot.so: bot.o
	${CXX} -shared bot.o -o bot.so

bot.o: bot.cpp ../core/core_module.h ../core/module.h bot.h

clean:
	rm bot.so bot.o
