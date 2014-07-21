/* 
 * File:     card.h
 * Author:   Sharad C. Sundararajan
 * Function: Contains Class declaration for Card
 * 
 * EDIT HISTORY:
 * 
 * DATE                 NAME                            DESCRIPTION
 * ----                 ----                            -----------
 * July 20, 2014        Sharad Sundararajan             Created
 */

#ifndef CARD_H
#define	CARD_H

#include <vector>
#include <iostream>

enum SuitValue {SPADE=0, HEART, DIAMOND, CLUB, TOTALSUITS};
static const char* SuitStr[] = {"S", "H", "D", "C"}; /* "SPADE", "HEART", "DIAMOND", "CLUB" */

enum RankValue {ACE=1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, TOTALRANKS=13};
static const char* RankStr[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

class Card {
    
    RankValue        rank_;
    SuitValue        suit_;
    
public:
    Card (RankValue r, SuitValue s) : rank_(r), suit_(s) {}

    RankValue get_rank() { return rank_; }
    SuitValue get_suit() { return suit_; }
};

typedef std::vector<Card*>                 CardVector_t;
typedef std::vector<Card*>::iterator       CardVectorIter_t;
typedef std::vector<Card*>::const_iterator CardVectorIterC_t;

/*
 * A simpler display of card rank and suit for quick DEBUG
 */
inline void printCards(CardVector_t cards) {

  CardVectorIterC_t citer;
  for (citer = cards.begin(); citer != cards.end(); citer++)
    std::cout << "(" << RankStr[(*citer)->get_rank() - 1] << "-" << SuitStr[(*citer)->get_suit()] << ") ";
  
  std::cout << std::endl;
}

/*
 * Used as a function object to populate the deck of 52 cards. It automatically 
 * generates the next card with the appropriate rank and suit.
 */
class CreateNewCard {
public:
  CreateNewCard(int r, int s) : rank_(r), suit_(s) {}
  Card* operator() () {

    /* Cycle through RANK::TOTALRANKS (=12) cards, hence mod */
    Card* newCard = new Card(static_cast<RankValue>(rank_%TOTALRANKS + 1), static_cast<SuitValue>(suit_));

    rank_++;
    if ((rank_ % TOTALRANKS) == 0) /* Will happen every 13th card */
      suit_++;
    
    return newCard;    
  }

private:
  int rank_;
  int suit_;
};

#endif	/* CARD_H */

