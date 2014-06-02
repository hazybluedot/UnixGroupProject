CXX ?= g++
CXXFLAGS = -g -Wall -Wextra -pedantic -D_XOPEN_SOURCE=700 -std=c++11

all: clt stats cint

clt: clt.o sample.o
	$(CXX) -o $@ $^

stats: stats.o sample.o
	$(CXX) -o $@ $^

cint: cint.o sample.o ztable.o
	$(CXX) -o $@ $^

.PHONY: clean
clean:
	rm -f clt *.o
