/* 
 * File:     hand.cpp
 * Author:   Sharad C. Sundararajan
 * Function: Contains implementations for the methods in the Hand class.
 * 
 * EDIT HISTORY:
 * 
 * DATE                 NAME                            DESCRIPTION
 * ----                 ----                            -----------
 * July 20, 2014        Sharad Sundararajan             Created
 */

#include <iostream>
#include <sstream>
#include <iomanip>

#include "hand.h"

/*
 * 1. Accumulate the values of all the cards in the hand.
 * 2. The Ace can take on either a 1 or 11 depending on which is more beneficial
 *    to the total score (<= 21).
 */
int Hand::compute_sum() {
#ifdef DEBUG_MODE
  printMessage ("Hand::compute_sum()", DEBUG);
#endif

  int total = 0;
  int num_aces = 0;
  int value;
  
  CardVectorIterC_t citer;
  for (citer = cards.begin(); citer != cards.end(); citer++) {
    value = (*citer)->get_rank();

    total += (value > 10) ? 10 : value; // jack, queen and king all have value = 10           
    if ((*citer)->get_rank() == ACE)
      num_aces++;
  }

  /* 
   * Handle Ace value which can be 1 or 11. The ace_value is store in case
   * there is a need to display the choice (should be self-evident)
   */
  if (num_aces) {
    if (num_aces > 1) {
      set_ace_value(1); /* No point setting to 11 if more than one A */
    }
    else if (total <= 11) {
      total += 10; /* Already 1 added earlier */
      set_ace_value (11);
    }
  }

  return total;
}

void Hand::clear_hand() {
#ifdef DEBUG_MODE
    printMessage("Hand::clear_hand()", DEBUG)
#endif
            
  CardVectorIter_t iter;
  for (iter = cards.begin(); iter != cards.end(); iter++)
    delete *iter;

  cards.clear();

  set_ace_value (1); // Default
}

/*
 * Display all the cards in a hand. Skip the hole-card for the dealer
 * when cards are first dealt. This is captured by the 'seed' run. The function
 * displays cards in a box with the value at the center.
 * 
 * TODO: Investigate a better display method and formatting.
 */
// 
// Skip the hole-card (ASSUMPTION: hole-card is the top one)
void Hand::show_hand(bool seed) {    
#ifdef DEBUG_MODE
    printMessage("Hand::show_hand()", DEBUG)
#endif
            
  std::stringstream ss;
  int length = cards.size();
  
  ss << "\n";

  for (int i = 0; i < length; i++)
    ss << "\t--------    "; 
  ss << "\n";

  for (int j = 0; j < length; j++)
    ss << "\t|      |    ";
  ss << "\n";

  std::string cardvalue;
  for (int i = 0; i < length; i++) {
    if (seed && (i == 0))
      cardvalue = "HOLE"; /* First card dealt is assumed to be the hole-card */
    else {
      cardvalue = RankStr[cards[i]->get_rank()-1];
      cardvalue += "-";
      cardvalue += SuitStr[cards[i]->get_suit()];
    }
    ss << "\t| " << std::setw(4) << cardvalue << " |    ";
  }
  
  ss << "\n";
  for (int j = 0; j < length; j++)
    ss << "\t|      |    ";
  ss << "\n";

  for (int i = 0; i < length; i++)
    ss << "\t--------    ";

  if (!seed)
    ss << "\t\tTOTAL: " << compute_sum();
  
  std::cout << ss.str() << std::endl << std::setfill('~') << std::setw(50) << "\n\n";
}
