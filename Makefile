bot: bot.o tools.o main.o settings.o
	g++ main.o bot.o settings.o tools.o -o bot -lgloox -lpthread
main.o: main.cpp
	g++ -std=c++0x -c main.cpp 
bot.o: bot.cpp
	g++ -c -std=c++0x bot.cpp
settings.o: settings.cpp
	g++ -c -std=c++0x settings.cpp
tools.o: tools.cpp
	g++ -c -std=c++0x tools.cpp
clean:
	rm *.o bot
