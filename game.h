/* 
 * File:     game.h
 * Author:   Sharad C. Sundararajan
 * Function: Contains Class declaration for Game
 * 
 * EDIT HISTORY:
 * 
 * DATE                 NAME                            DESCRIPTION
 * ----                 ----                            -----------
 * July 20, 2014        Sharad Sundararajan             Created
 */


#ifndef GAME_H
#define	GAME_H

#include <vector>
#include <string>

#include "player.h"
#include "deck.h"

class Game {

  Dealer               dealer_;
  std::vector<Player*> players_; /* List of all the players */
  Deck                 deck_;    /* Deck of 52 cards */
  
public:
  Game(std::vector<std::string> &player_names);
  ~Game(); 
  
  int  play();  
  void deal();
  void show_all_hands(bool seed);
  void reset();
};

#endif	/* GAME_H */

