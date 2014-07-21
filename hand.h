/* 
 * File:     hand.h
 * Author:   Sharad C. Sundararajan
 * Function: Contains Class declaration for Hand
 * 
 * EDIT HISTORY:
 * 
 * DATE                 NAME                            DESCRIPTION
 * ----                 ----                            -----------
 * July 20, 2014        Sharad Sundararajan             Created
 */

#ifndef HAND_H
#define	HAND_H

#include "card.h"

class Hand {
 
  int   ace_value_; /* To keep track of which value (1 or 11) was used */
  
protected:
      CardVector_t cards;
      
public:
  Hand() : ace_value_ (1) {}

  void add_card       (Card* c)   { cards.push_back (c); }
  void clear_hand     ();
  void show_hand      (bool seed);
  int  compute_sum    ();
  
  void set_ace_value (int val)   { ace_value_ = val;  }
  int  get_ace_value ()          { return ace_value_; }  
};


#endif	/* HAND_H */

