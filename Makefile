OBJS = deck.o game.o hand.o main.o player.o utils.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

blackjack : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o blackjack

utils.o : utils.h utils.cpp
	$(CC) $(CFLAGS) utils.cpp

deck.o : deck.h deck.cpp
	$(CC) $(CFLAGS) deck.cpp

game.o : game.h game.cpp utils.h
	$(CC) $(CFLAGS) game.cpp

hand.o : hand.h hand.cpp
	$(CC) $(CFLAGS) hand.cpp

player.o : player.h player.cpp utils.h
	$(CC) $(CFLAGS) player.cpp

main.o : main.cpp game.h utils.h
	$(CC) $(CFLAGS) main.cpp

clean:
	\rm *.o blackjack
