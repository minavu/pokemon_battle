a.out: main.o minalib.o addons.o addonsdb.o pokemon.o redblacktree.o kanto.o
	g++ -g *.o

main.o: main.cpp
	g++ -g -c main.cpp

kanto.o: kanto.h kanto.cpp
	g++ -g -c kanto.cpp

redblacktree.o: redblacktree.h redblacktree.cpp
	g++ -g -c redblacktree.cpp

pokemon.o: pokemonabc.h pokemonsub.h pokemonabc.cpp pokemonsub.cpp
	g++ -g -c pokemonabc.cpp pokemonsub.cpp

addonsdb.o: addonsdb.h addonsdb.cpp
	g++ -g -c addonsdb.cpp

addons.o: addons.h addons.cpp
	g++ -g -c addons.cpp

minalib.o: minalib.h minalib.cpp
	g++ -g -c minalib.cpp

clean:
	rm -rvf *.o a.out
