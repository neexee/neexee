CXXFLAGS=-std=c++11 -g

test_module.so: test_module.o
	${CXX} -shared test_module.o -o test_module.so

test_module.o: test_module.cpp ../../core/core_module.h ../../core/module.h ../bot.h

clean:
	rm -f test_module.o test_module.so
