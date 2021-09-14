main: card player deck game main.cpp
	g++ -std=c++14 -Wall -o main game.o deck.o card.o player.o main.cpp

game: game.cpp game.h
	g++ -c -std=c++14 -Wall -o game.o game.cpp

deck: deck.cpp deck.h
	g++ -c -std=c++14 -Wall -o deck.o deck.cpp

player: player.cpp player.h
	g++ -c -std=c++14 -Wall -o player.o player.cpp

card: card.cpp card.h
	g++ -c -std=c++14 -Wall -o card.o card.cpp

clean:
	rm *.o
	rm main	
