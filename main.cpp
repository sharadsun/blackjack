/* 
 * File:     main.cpp
 * Author:   Sharad C. Sundararajan
 * Function: Contains the main driver routine for the BlackJack game.
 * 
 * EDIT HISTORY:
 * 
 * DATE                 NAME                            DESCRIPTION
 * ----                 ----                            -----------
 * July 20, 2014        Sharad Sundararajan             Created
 */

#include <string>
#include <vector>
#include <exception>
#include <sstream>

#include "game.h"
#include "utils.h"

/*
 * ENTRY POINT for the blackjack game.
 * 
 * TODO: Add command line options via args as follows:
 *       -verbose to give detailed messages
 *       -help to provide instructions on running blackjack with rules
 */
int main(int argc, char** argv) { // Arguments for future command line options
   
  std::vector<std::string> names;

  printMessage ("WELCOME to the text based BLACKJACK game");

  if (!getPlayerInfoResponse(names)) { // Retrieve number and names of players
    printMessage ("No players. Exiting game ...", INFO, 1);
    return 1;
  }

  try {  
      Game G (names); // Runs the game
      
      while (getUserGoalResponse() != "N") { // Check for continuing play
          G.play();
          G.reset();
      }
  }

  catch (std::exception &e) {
      
      std::stringstream ss;
      ss << "[Blackjack] EXCEPTION encountered in code" << e.what();
      printMessage (ss.str(), SEVERE, 9);
  }
  
  printErrorReport(); // Prints Errors, Warnings and Severe count
  
  printMessage ("Thank You for playing BlackJack !");
  
  return (gErrorReport.num_errors + gErrorReport.num_severe) ;
}
