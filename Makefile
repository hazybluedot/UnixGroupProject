CXX ?= g++
CXXFLAGS = -Wall -Wextra 

clt: clt.o
	$(CXX) -o $@ $^

.PHONY: clean
clean:
	rm -f clt *.o
