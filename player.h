/* 
 * File:     player.h
 * Author:   Sharad C. Sundararajan
 * Function: Contains Class declarations for BasePlayer, Player and Dealer
 * 
 * EDIT HISTORY:
 * 
 * DATE                 NAME                            DESCRIPTION
 * ----                 ----                            -----------
 * July 20, 2014        Sharad Sundararajan             Created
 */

#ifndef PLAYER_H
#define	PLAYER_H

#include "hand.h"

#define DEALER_MIN_BET 17 /* Dealer MUST HIT until this total is reached */

/* Possible states for player to be at the end of the game */
enum StateValue {BUST, WIN, NATURAL_WIN, LOSE, TIE, NONE};

class BasePlayer : public Hand {
    
  StateValue state_;
  
public:
  BasePlayer() : state_(NONE) {}
  
  bool should_hit ();
  void add_card   (Card* c);
  bool is_bust    ()          { return (state_ == BUST); } /* >21 */
  
  void  set_state (StateValue s)   { state_ = s;       }
  StateValue get_state ()          { return state_;    }
};

class Player: public BasePlayer {
    
  std::string  name_;
  int          bet_; /* Number of chips player bets */
  double       chip_bank_; /* Number of chips available to bet with  */
  
public:
  Player(std::string &n, int chips=100) {
    chip_bank_ = chips;
    bet_ = 0;
    name_ = n;
  }

  void show_hand                (bool seed=false);
  bool should_hit               (std::string str);
  
  void update_bank              (int chips)       { chip_bank_ = chips; }
  bool get_and_check_bets       ();
  const std::string get_name    ()                { return name_; }
  void check_and_declare_winner (int dealer_total);
  
  /* Methods related to optional strategies such as splitting and doubling-down */
  void double_down              ()                { bet_ *= 2; } /* Double the bet */
  bool can_split                (RankValue r);
};

class Dealer: public BasePlayer {

public:
  void show_hand  (bool seed=false);
  bool should_hit (int max_players_sum);
};

#endif	/* PLAYER_H */
