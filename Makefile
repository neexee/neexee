bot: bot.o main.o settings.o
	g++ main.o bot.o settings.o -o bot -lgloox -lpthread
main.o: main.cpp
	g++ -c main.cpp 
bot.o: bot.cpp
	g++ -c bot.cpp
settings.o: settings.cpp
	g++ -c settings.cpp
tools.o: tools.cpp
	g++ -c tools.cpp
clean:
	rm *.o bot
