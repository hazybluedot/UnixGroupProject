all: clt

clt: clt.o
     g++ clt.o -o clt

clt.o: clt.cpp
     g++ -c clt.cpp

clean:
      rm -rf *o clt
