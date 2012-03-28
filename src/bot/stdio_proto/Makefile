CXXFLAGS=-std=c++11 -g
LDFLAGS=-lstdc++ -ldl -lthread

stdio_proto.so: stdio_proto.o
	${CXX} -shared stdio_proto.o -o stdio_proto.so

stdio_proto.o: stdio_proto.cpp ../../core/core_module.h ../../core/module.h ../bot.h

clean:
	rm -f stdio_proto.o stdio_proto.so
