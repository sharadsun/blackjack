blackjack
=========
NOTE: A reademe.pdf exists in the current repository that may be downloaded as well.

Implementation Language: C++

Features Implemented (with some assumptions)

- Multiple players - currently restricted to 5 (randomly chosen)
- Dealer (H)its until his hand >= 17. If 17 is reached additional check if dealer has already surpassed all the other players or they all busted, no more hits.
- Player starts with 100 chips betting atleast 1 chip per hand. If player gets a Natural (i.e. 21), the return is 3 to 2 (i.e. 1.5) times the original bet.
- Ace takes whichever value is beneficial.
- Players can double-down (i.e. double the bet if they're fairly sure of winning). Only one more hand will be dealt if that option is chosen. Can double-down at any point, not only with a two-card hand (Assumption made). 
- Splitting : One time split is allowed when the two cards dealt have the same value. No special handling of Ace during splitting. Also, when hands are split, the code treats the new hand as another player and so the number of chips available to play will also be split (Eg. 100 starter chips will now become 50 each).
- Only one deck is assumed to be used.

Files (For class-structure refer to readme.pdf)

1.	cards.h
2.	hand.h
3.	hand.cpp
4.	deck.h
5.	deck.cpp
6.	player.h
7.	player.cpp
8.	game.h
9.	game.cpp
10.	utils.h	
11.	utils.cpp
12.	main.cpp (entry point)
13.	Makefile

Build : Type "make" with all the files in the same directory. Alternatively load into an IDE and hit compile.


