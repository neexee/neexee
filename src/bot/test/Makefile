CXXFLAGS=-std=c++11 -fpermissive -g
LDFLAGS=-lstdc++ -ldl -lthread

test.so: test_protocol.o
	${CXX} -shared test_protocol.o -o test.so

test_protocol.o: test_protocol.cpp ../../core/core_module.h ../../core/module.h ../bot.h

clean:
	rm -f test_protocol.o test.so
