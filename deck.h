/* 
 * File:     deck.h
 * Author:   Sharad C. Sundararajan
 * Function: Contains Class declaration for Deck
 * 
 * EDIT HISTORY:
 * 
 * DATE                 NAME                            DESCRIPTION
 * ----                 ----                            -----------
 * July 20, 2014        Sharad Sundararajan             Created
 */

#ifndef DECK_H
#define	DECK_H

#include "hand.h"

class Deck : public Hand {
    
 public:
  void  init();
  void  shuffle();
  bool  empty()     { return (cards.size() == 0); }
  Card* pick_card(); 
  void  clear();
};

#endif	/* DECK_H */

