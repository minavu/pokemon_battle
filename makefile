main: main.cpp mstr.o attacks.o pokemon.o gym.o
	g++ -g -o main main.cpp mstr.o attacks.o pokemon.o gym.o

gym.o: gym.h gym.cpp
	g++ -g -c gym.cpp

pokemon.o: pokemon.h pokemon.cpp
	g++ -g -c pokemon.cpp

attacks.o: attacks.h attacks.cpp
	g++ -g -c attacks.cpp

mstr.o: mstr.h mstr.cpp
	g++ -g -c mstr.cpp

clean:
	rm -rvf *.o main
