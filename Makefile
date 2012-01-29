OBJ=bot.o tools.o main.o settings.o
LDFLAGS=-lgloox -lpthread

bot: ${OBJ}

clean:
	rm -f -- ${OBJ} bot
