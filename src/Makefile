.PHONY: all

all:
	$(MAKE) -C core
	$(MAKE) -C bot
	$(MAKE) -C bot/stdio_proto
	$(MAKE) -C bot/test_module
	mkdir -p build
	cp core/core bot/bot.so bot/stdio_proto/stdio_proto.so bot/test_module/test_module.so build

clean:
	rm -rf build
	$(MAKE) -C core clean
	$(MAKE) -C bot clean
	$(MAKE) -C bot/stdio_proto clean
	$(MAKE) -C bot/test_module clean
