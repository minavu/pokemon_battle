a.out: main.o minalib.o addons.o addonsdb.o pokemon.o redblack.o kanto.o
	g++ -g *.o

main.o: main.cpp
	g++ -g -c main.cpp

kanto.o: kanto.h kanto.cpp
	g++ -g -c kanto.cpp

redblack.o: redblack.h redblack.cpp
	g++ -g -c redblack.cpp

pokemon.o: pokemon.h pokemon.cpp
	g++ -g -c pokemon.cpp

addonsdb.o: addonsdb.h addonsdb.cpp
	g++ -g -c addonsdb.cpp

addons.o: addons.h addons.cpp
	g++ -g -c addons.cpp

minalib.o: minalib.h minalib.cpp
	g++ -g -c minalib.cpp

clean:
	rm -rvf *.o a.out
