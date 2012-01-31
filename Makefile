CXX = g++
OBJ = src/bot.o\
	  src/tools.o\
	  src/main.o\
	  src/settings.o\
	  src/module/moduleexecutor.o\
	  src/module/defaultmodule.o\
	  src/module/ping.o\
	  src/module/asyncmodule.o\
	  src/debug/debug.o

LDFLAGS=-lgloox -lpthread
CXXFLAGS = -DDEBUG=2  -Wall -Wextra
BIN = bot
all: $(OBJ)
		$(CXX) $(LDFLAGS) $+ -o $(BIN)
.cpp.o:
		$(CXX) $(CXXFLAGS) -c $< -o $@
clean:
	rm -f -- ${OBJ} bot
