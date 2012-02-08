CXX = g++
OBJ = src/bot/bot.o\
	  src/tools/tools.o\
	  src/main.o\
	  src/settings/settings.o\
	  src/module/moduleexecutor.o\
	  src/module/defaultmodule.o\
	  src/module/ping.o\
	  src/module/asyncmodule.o\
	  src/debug/debug.o\
	  src/bot/modulehandler.o\
	  src/named_socket/socket.o\
	  src/console/console.o\
	  src/tools/tokenizer.o

LDFLAGS=-lgloox -lpthread 
CXXFLAGS =-Wall -Wextra -std=gnu++0x
BIN = bot
all: $(OBJ)
		$(CXX) $(LDFLAGS) $+ -o $(BIN)
.cpp.o:
		$(CXX) $(CXXFLAGS) -c $< -o $@
clean:
	rm -f -- ${OBJ} bot
