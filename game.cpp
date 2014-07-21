/* 
 * File:     game.cpp
 * Author:   Sharad C. Sundararajan
 * Function: Contains implementations for the Game class methods
 * 
 * EDIT HISTORY:
 * 
 * DATE                 NAME                            DESCRIPTION
 * ----                 ----                            -----------
 * July 20, 2014        Sharad Sundararajan             Created
 */

#include <assert.h>
#include <sstream>
#include "game.h"
#include "utils.h"

/*
 * Constructor to initialize players and deck of cards
 */
Game::Game(std::vector<std::string> &player_names) {

  /* 
   * NOTE: vector.size() is of type size_t which might result in a warning but
   *       it should be fine
   */
  for (int i=0; i <player_names.size(); i++)
    players_.push_back (new Player(player_names[i]));

  deck_.init();
  deck_.shuffle();
  
  // Initialize error report
  gErrorReport.num_errors   = 0;
  gErrorReport.num_severe   = 0;
  gErrorReport.num_warnings = 0;
}

/*
 * Destructor to clean up.
 */
Game::~Game() {
    for (int i  = 0; i < players_.size(); i++)
        delete players_[i];
    
    players_.clear();
    deck_.clear(); 
}

/*
 * Display the cards for all the player's hands as well as the dealer's.
 */
void Game::show_all_hands(bool seed) {
#ifdef DEBUG_MODE
  printMessage ("Game::show_all_hands()", DEBUG);
#endif
  dealer_.show_hand(seed);
  
  for (int i = 0; i < players_.size(); i++)
      players_[i]->show_hand();
}

/*
 * 1. Hand out 2 cards to all players. In the process, if a player finds both
 *    cards to be same, then split the hand and hand out an additional card to 
 *    both new hands. Splitting is allowed only once.
 * 
 * 2. Display all the hands at the end. The dealer will show only one card,
 *    keeping the hole-card face down.
 */
void Game::deal() {
#ifdef DEBUG_MODE
  printMessage ("Game::deal()", DEBUG);
#endif
  assert (!deck_.empty()); // NOTE: ERROR-HANDLING
  
  std::vector<Player*> splitlist (players_.begin(), players_.end());
  std::stringstream ss;
  
  /* 
   * Deal two (NUM_DEAL_CARDS) cards to all players, one card at a time
   */
  for (int i = 1; i <= NUM_DEAL_CARDS; i++) {
      
    std::cout << "Dealing Card # " << i << " to " << players_.size() << " player(s) and dealer " ;
    std::cout.flush();
    
    wait(2); /* This is to simulate the delay while dealing cards */
    std::cout << std::endl;
    
    dealer_.add_card(deck_.pick_card());

    /*
     * For each player, deal a card. If there is occasion for splitting then
     * create a new player, split the number of chips, re-use the same name
     * as the original player with the suffix "_split" and continue normal play.
     */
    for (int j = 0; j < players_.size(); j++) {
      Card* newcard = deck_.pick_card();     

      if (players_[j]->can_split(newcard->get_rank())) {
	
#ifdef DEBUG_MODE
          printMessage ("Hand being split for player ...");
#endif
	std::string splitname = players_[j]->get_name();
	splitname += "_split";

	Player* splitplayer = new Player(splitname, 50); // Half the chips for each hand
	splitplayer->add_card(newcard);
	
        /*
         * Deal Again : Only 1 split allowed.
         * NOTE: To implement further splitting - use a recursive routine
         */
	ss << "Dealing again after splitting hands for  " << players_[j]->get_name() << " and " << splitname;
        printMessage(ss.str(), INFO, 7);
        ss.str().clear();
        
	players_[j]->add_card(deck_.pick_card());
	players_[j]->update_bank (50);
	
	splitplayer->add_card(deck_.pick_card());
        
        /*
         * Insert new player next to the original player whose hand was split.
         * This will ensure that cards are dealt consecutively for both hands.
         */
	splitlist.insert(splitlist.begin() + j + 1, splitplayer);
      }
      else
	players_[j]->add_card(newcard);
    }
        
    show_all_hands(true);
  }

  /*
   * Re-insert all the new split-hands back in the original player list to 
   * resume further operations on the original list.
   */
  if (splitlist.size() > players_.size()) { // Means hands were split and new players were added
#ifdef DEBUG_MODE
      printMessage("Creating split hands ...");
#endif
      
    players_.clear();
    players_.insert(players_.begin(), splitlist.begin(), splitlist.end());
    splitlist.clear();

    show_all_hands(true); // Display hands for all players and dealer
  }
}

/*
 * Core playing routine. This will perform the following operations:
 * 
 * 1. Deal cards to everyone. Dealer leaves one card face-down
 * 2. Each player plays (Hits/Stands/Doubles-down)
 * 3. If all players bust (score > 21), else goto 4
 * 4. Compute the maximum score under 21 among all players
 * 5. Reveal dealer's hole-card.
 * 6. Dealer bets until 17 or greater than above maximum score
 * 7. Check and declare winner. NOTE: Each player is compared against the dealer
 */
int Game::play() {
#ifdef DEBUG_MODE
  printMessage ("Game::play()", DEBUG);
#endif
    
    /*
     * Deal two cards to player(s) and dealer.
     */
    this->deal();   

    std::string val;
    int num_busts = 0;
    int player_total_score, max_score = 0;
    
    /* Player's turn to play : Add a card until BUST (>21) OR user HITS */
    for (int i=0; i < players_.size(); i++) {
        if (!players_[i]->get_and_check_bets())
            return 1;
        
        while ( (players_[i]->compute_sum() <= BLACKJACK) && (getActionResponse(players_[i]->get_name(), val) && players_[i]->should_hit(val))) {
            players_[i]->add_card(deck_.pick_card());
            players_[i]->show_hand();
            
            // If doubling-down, dealer can deal only ONE more card
            if (val == "D") {
                players_[i]->double_down();
                break;
            }
        }
        
        num_busts += players_[i]->is_bust() ? 1 : 0;
        player_total_score = players_[i]->compute_sum();
        if (player_total_score > max_score)
            max_score = player_total_score;
    } 

    /* Continue only if ALL players did not BUST */
    if (num_busts != players_.size()) {

      printMessage ("Revealing Dealer's Hole Card ...", INFO, 3);
      dealer_.show_hand();
  
      /* Dealer's turn to play */
      while ((dealer_.compute_sum() <= BLACKJACK) && dealer_.should_hit(max_score)) {
        dealer_.add_card (deck_.pick_card());
	dealer_.show_hand();
      }
    }
    
#ifdef DEBUG_MODE
    if (num_busts == players_.size())
        printMessage ("ALL PLAYERS BUST !!");
#endif

    /* Check each player against the dealer's total and declare winner */
    int dtotal = dealer_.compute_sum();
    for (int i = 0; i < players_.size(); i++) {
        players_[i]->check_and_declare_winner (dtotal);
        players_[i]->clear_hand(); 
    }
    dealer_.clear_hand();

    return 0;
}

void Game::reset() {
    deck_.clear(); 
    deck_.init(); 
    deck_.shuffle();
}
