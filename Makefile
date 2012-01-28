bot: bot.o main.o
	g++ main.o bot.o -o bot -lgloox -lpthread
main.o: main.cpp
	g++ -c main.cpp 
bot.o: bot.cpp
	g++ -c bot.cpp
clean:
	rm *.o bot
