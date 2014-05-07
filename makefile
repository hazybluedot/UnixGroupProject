clt: clt.o
	g++ clt.o -o clt

clt.o: clt.cpp
	g++ -c clt.cpp

clean:
	rm -f clt *.o
