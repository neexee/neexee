CXX = g++
OBJ = src/bot/bot.o\
	  src/tools/tools.o\
	  src/main.o\
	  src/settings/settings.o\
	  src/moduleexecutor/moduleexecutor.o\
	  src/module/defaultmodule.o\
	  src/module/ping/ping.o\
	  src/module/smart/smartmodule.o\
	  src/module/koko/kokomodule.o\
	  src/module/pluginexecutor/pluginexecutor.o\
	  src/debug/debug.o\
	  src/console/console.o\
	  src/tools/tokenizer.o

LDFLAGS=-lgloox -lpthread 
CXXFLAGS =-DDEBUG=3 -Wall -Wextra -std=gnu++0x
BIN = bot
all: $(OBJ)
		$(CXX) $(LDFLAGS) $+ -o $(BIN)
.cpp.o:
		$(CXX) $(CXXFLAGS) -c $< -o $@
clean:
	rm -f -- ${OBJ} bot
