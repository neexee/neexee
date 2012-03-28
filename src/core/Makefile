CXXFLAGS=-std=c++11 -pthread -g
LDFLAGS=-lstdc++ -ldl -pthread

core: core.o

core.o: core.cpp core_module.h module.h module_handler.h

clean:
	rm -f core core.o
