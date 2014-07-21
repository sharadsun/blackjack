/* 
 * File:     deck.cpp
 * Author:   Sharad C. Sundararajan
 * Function: Contains implementations for the methods in the Deck class.
 * 
 * EDIT HISTORY:
 * 
 * DATE                 NAME                            DESCRIPTION
 * ----                 ----                            -----------
 * July 20, 2014        Sharad Sundararajan             Created
 */

#include <algorithm>
#include <assert.h>

#include "deck.h"

/*
 * Populate the deck with 52 cards from Ace through King (13) for 4 suits. No
 * Joker in the deck.
 */
void Deck::init() {
#ifdef DEBUG_MODE
  printMessage ("Deck::init()", DEBUG);
#endif

  assert (cards.size() == 0); // MUST be cleaned or new
  
  int numcards = TOTALRANKS * TOTALSUITS;
  CreateNewCard ncard(0, 0); // used as a function object

  /* 
   * This routine creates a new card with the new value and adds it to the
   * list. "ncard" is a function object that under the covers appropriately
   * picks the next rank and suit.
   */
  std::generate_n(std::back_inserter(cards), numcards, ncard);
  
#ifdef DEBUG_MODE
  printCards(cards);
#endif
}

void Deck::clear() {
#ifdef DEBUG_MODE
  printMessage("Deck::clear()", DEBUG);
#endif
  
  CardVectorIter_t iter;
  for (iter = cards.begin(); iter != cards.end(); iter++)
    delete *iter;
  
  cards.clear();
}

void Deck::shuffle() {
#ifdef DEBUG_MODE
  printMessage ("Before Shuffling", DEBUG);
  printCards(cards);
#endif

  std::random_shuffle(cards.begin(), cards.end()); // NOTE: Can customize random function with third argument if needed

#ifdef DEBUG_MODE
  printMessage ("After Shuffling", DEBUG);
  printCards(cards);
#endif
}

/*
 * Picks the next card from the deck. 
 * 
 * NOTE: This should be fine given that the deck will be shuffled. But
 *       another addition can be randomly pick from this deck as well.
 */
Card* Deck::pick_card() {
    
    Card* card = cards.back(); 
    cards.pop_back(); 
    
    return card;
}
