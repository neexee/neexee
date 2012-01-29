CXX = g++
OBJ = src/bot.o\
	  src/tools.o\
	  src/main.o\
	  src/settings.o
LDFLAGS=-lgloox -lpthread

BIN = bot
all: $(OBJ)
		$(CXX) $(LDFLAGS) $+ -o $(BIN)
clean:
	rm -f -- ${OBJ} bot
