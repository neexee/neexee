.PHONY: all

all:
	$(MAKE) -C core
	$(MAKE) -C bot
	$(MAKE) -C bot/stdio_proto
	mkdir -p build
	cp core/core bot/bot.so bot/stdio_proto/stdio_proto.so build

clean:
	rm -rf build
	$(MAKE) -C core clean
	$(MAKE) -C bot clean
	$(MAKE) -C bot/stdio_proto clean	
