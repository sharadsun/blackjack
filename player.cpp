/* 
 * File:     player.cpp
 * Author:   Sharad C. Sundararajan
 * Function: Contains implementations for the methods in the following classes
 *           BasePlayer, Dealer, Player.
 * 
 * EDIT HISTORY:
 * 
 * DATE                 NAME                            DESCRIPTION
 * ----                 ----                            -----------
 * July 20, 2014        Sharad Sundararajan             Created
 */

#include <iostream>
#include <sstream>

#include "player.h"
#include "utils.h"


void BasePlayer::add_card(Card* c) {
  Hand::add_card(c);  

  if (compute_sum() > BLACKJACK)
    set_state (BUST);
}

void Player::show_hand (bool seed) {
    std::cout << "[" << name_ << "'s Cards]: ";
    BasePlayer::show_hand(seed); 
}

/* 
 * Player can be dealt one more card when doubling-down (but no more), hence
 * can hit even when option = (D)ouble-down.
 */
bool Player::should_hit(std::string str) { 
    return ((str == "H") || (str == "D")) ; 
}

/*
 * Ask players for number of bets (chips).
 */
bool Player::get_and_check_bets() {

  /* Cannot bet more than what is available */
  if (chip_bank_ == 0) {
      printMessage("You have no chips to bet. Cannot play.", ERROR, 4);
      return false;
  }
  
  bet_ = getUserBetResponse(name_, chip_bank_);
  return true;
}

bool Player::can_split(RankValue rank) {
  return (cards.size() && (cards[0]->get_rank() == rank) && getSplitResponse(name_, RankStr[rank]));
}

/* 
 * 1. Checks for BUST/WIN/LOSS
 * 2. Updates the players' bank of chips. If the players' score is EXACTLY 21
 *    (a natural), then chips increase by 1.5 (3 to 2). This explains why the
 *    chips_bank is a 'double' type. 
 * 3. Display the game summary
 * 
 * TODO: The checks in this function can be re-arranged to be shorter. Re-visit.
 */
void Player::check_and_declare_winner(int dtotal) {

  int ptotal = compute_sum();

  // Check Player bust first
  if (is_bust()) {

    chip_bank_ -= bet_;

    std::cout << "[BlackJack] PLAYER SUMMARY for " << name_ << " : " << std::endl;
    std::cout << "\t\tSTATE    : BUST" << std::endl;
    std::cout << "\t\tTOTAL    : " << ptotal << std::endl;
    std::cout << "\t\tLOST     : " << bet_ << " chips" << std::endl;
    std::cout << "\t\tCHIPS BALANCE : " << chip_bank_ << std::endl << std::endl;    

    return;
  }

  std::stringstream player_summary;

  player_summary << "[BlackJack] PLAYER SUMMARY for " << name_ << " : " << std::endl;


  if (dtotal > BLACKJACK) {
    
    if (ptotal < BLACKJACK) {

      set_state (WIN);
      chip_bank_ += bet_;

      player_summary << "\t\tSTATE          : WON" << std::endl;
      player_summary << "\t\tTOTAL          : " << ptotal << std::endl;
      player_summary << "\t\tCHIPS BALANCE  : " << chip_bank_ << std::endl;
      player_summary << "\t\tWINNINGS       : " << bet_ << " chips" << std::endl << std::endl;
      player_summary << "\t\tDEALER-STATE   : BUST\n";
      player_summary << "\t\tDEALER-TOTAL   : " << dtotal << std::endl;
    }
    else {
      set_state (NATURAL_WIN); // = BlackJack
      chip_bank_ += 1.5 * bet_;

      player_summary << "\t\tSTATE          : NATURAL WIN (21)" << std::endl;
      player_summary << "\t\tTOTAL          : " << ptotal << std::endl;
      player_summary << "\t\tCHIPS BALANCE  : " << chip_bank_ << std::endl;
      player_summary << "\t\tWINNINGS       : " << 1.5 * bet_ << " chips" << std::endl << std::endl;
      player_summary << "\t\tDEALER-STATE   : BUST\n";
      player_summary << "\t\tDEALER-TOTAL   : " << dtotal << std::endl;
    }
  }
  else {
    if (dtotal > ptotal) {	       
      set_state (LOSE);
      chip_bank_ -= bet_;

      player_summary << "\t\tSTATE          : LOST" << std::endl;
      player_summary << "\t\tTOTAL          : " << ptotal << std::endl;
      player_summary << "\t\tCHIPS BALANCE  : " << chip_bank_ << std::endl;
      player_summary << "\t\tLOST           : " << bet_ << " chips" << std::endl << std::endl;
      player_summary << "\t\tDEALER-STATE   : WON" << std::endl;
      player_summary << "\t\tDEALER-TOTAL   : " << dtotal << std::endl;
    }
    else if (ptotal == dtotal) {
      set_state (TIE);

      player_summary << "\t\tSTATE          : PUSH (DRAW)" << std::endl;
      player_summary << "\t\tTOTAL          : " << ptotal << std::endl;
      player_summary << "\t\tCHIPS BALANCE  : " << chip_bank_ << std::endl;
      player_summary << "\t\tWINNINGS       : NIL " << std::endl << std::endl;
      player_summary << "\t\tDEALER-STATE   : PUSH (DRAW) \n";
      player_summary << "\t\tDEALER-TOTAL   : " << dtotal << std::endl;
    }
    else {

      if (ptotal < BLACKJACK) {
	set_state (WIN);
	chip_bank_ += bet_;

	player_summary << "\t\tSTATE          : WIN" << std::endl;
	player_summary << "\t\tTOTAL          : " << ptotal << std::endl;
        player_summary << "\t\tCHIPS BALANCE  : " << chip_bank_ << std::endl;
	player_summary << "\t\tWINNINGS       : " << bet_ << " chips" << std::endl << std::endl;
      }
      else {
	set_state (NATURAL_WIN);
	chip_bank_ += 1.5 * bet_;	

	player_summary << "\t\tSTATE          : NATURAL WIN (21)" << std::endl;
	player_summary << "\t\tTOTAL          : " << ptotal << std::endl;
        player_summary << "\t\tCHIPS BALANCE  : " << chip_bank_ << std::endl;
	player_summary << "\t\tWINNINGS       : " << 1.5 * bet_ << " chips" << std::endl << std::endl;
      }

      player_summary << "\t\tDEALER-STATE     : LOST \n";
      player_summary << "\t\tDEALER-TOTAL     : " << dtotal << std::endl;      
    }
  }
  
  std::cout << player_summary.str() << std::endl; // May also save to a file
}

void Dealer::show_hand (bool seed) {
    std::cout << "[Dealer's Cards]: "; 
    BasePlayer::show_hand(seed); 
}

bool Dealer::should_hit (int max_players_sum) { 
      int total = compute_sum();
      
      /*
       * The reason for the extra check against max_players is so to stop 
       * betting if the dealer has 17 and is already higher than ALL other
       * players.
       */
      return ((total < DEALER_MIN_BET) && (total < max_players_sum));
  }
