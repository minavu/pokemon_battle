a.out: main.o minalib.o attacks.o addonsdb.o pokemon.o gym.o
	g++ -g *.o

main.o: main.cpp
	g++ -g -c main.cpp

gym.o: gym.h gym.cpp
	g++ -g -c gym.cpp

pokemon.o: pokemon.h pokemon.cpp
	g++ -g -c pokemon.cpp

addonsdb.o: addonsdb.h addonsdb.cpp
	g++ -g -c addonsdb.cpp

attacks.o: attacks.h attacks.cpp
	g++ -g -c attacks.cpp

minalib.o: minalib.h minalib.cpp
	g++ -g -c minalib.cpp

clean:
	rm -rvf *.o a.out
