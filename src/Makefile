.PHONY: all

all:
	$(MAKE) -C core
	$(MAKE) -C bot
	$(MAKE) -C bot/test
	mkdir -p build
	cp core/core bot/bot.so bot/test/test.so build

clean:
	rm -rf build
	$(MAKE) -C core clean
	$(MAKE) -C bot clean
	$(MAKE) -C bot/test clean	
