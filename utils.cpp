/* 
 * File:     utils.cpp
 * Author:   Sharad C. Sundararajan
 * Function: Contains helper functions.
 * 
 * EDIT HISTORY:
 * 
 * DATE                 NAME                            DESCRIPTION
 * ----                 ----                            -----------
 * July 20, 2014        Sharad Sundararajan             Created
 */

#include <algorithm>
#include <iostream>
#include <sstream>
#include <time.h>
#include <assert.h>

#include "utils.h"

#define MAX_TICK_TIME 0.1 /* To control the pause time */

ReportStruct gErrorReport;

static void tick() {

  time_t initial_time, current_time;  
  time(&initial_time);

  do {
    time (&current_time);
  } while ((current_time - initial_time) < MAX_TICK_TIME);
}

void wait(int n) {
  
  int i = 0;
  while (i < n) {
    std::cout << ".";
    std::cout.flush();
    tick();
    i++;
  }
}

std::string uppercase(const std::string &inputstr) {

  std::string newstr;
  std::transform(inputstr.begin(), inputstr.end(), std::back_inserter(newstr), ::toupper);
  
  return newstr;
}

/*
 * Determine if user wants to Hit/Stand/Double-down
 */
bool getActionResponse (std::string name, std::string &response) {   

  while (1) {

    std::cout << name << ", would you like to (H)it or (S)tand or (D)ouble-down? : ";

    std::string str;
    std::cin >> str;
    std::cin.clear();

    response = uppercase (str);
    
#ifdef DEBUG_MODE
    std::stringstream ss;
    ss << "SELECTED option (" << str << ") and uppercase (" << response << ")";
    printMessage(ss.str(), DEBUG);
    ss.str(""); ss.clear();
#endif
    if ((response == "H") || (response == "D") || (response == "S"))
      break;
    else
      std::cout << "\nPlease enter a valid option : H or S or D\n";
  };

  return true;
}

/*
 * Determine how many chips the user wants to bet
 */
int getUserBetResponse (std::string name, double allowed_max) {
    
    std::stringstream ss;
    int bet;
    
    while (true) {
      ss << name << ", how many chips would you like to bet per hand (Minimum = 1) ? : ";
      printMessage(ss.str(), PROMPT);
      ss.str(""); ss.clear();
      
      std::cin >> bet;
      while (std::cin.fail()) {
          std::cin.clear();
          std::cin.ignore(256, '\n');
          printMessage("Input must be an integer. Please re-enter:", PROMPT);
          std::cin >> bet;
      }
      
      if (bet <= allowed_max)
          break;
      else {
       ss << "Cannot bet over available chips (" << allowed_max << "). Please re-enter.";
       printMessage(ss.str(), WARN, 5);
       ss.str(""); ss.clear();
      }
    }
    
    return bet;
}

/*
 * Once the players have two similar valued cards, ask if they would like to 
 * split.
 */
bool getSplitResponse (std::string name, std::string rank) {
    
  std::string str, response;

  while (true) {
    std::cout << "[" << name << "] Two cards with the same value " << rank << " found. Would you like to split ? (Y/N) : ";
    
    std::cin >> str;
    std::cin.clear();
    response = uppercase (str);

    if ((response == "Y") || (response == "N"))
      break;
    else
      std::cout << "Please enter a valid option : Y/N " << std::endl;
  };

  return (response == "Y");
}

/*
 * Determine number of players and their names
 */
bool  getPlayerInfoResponse (std::vector<std::string> &names) {

  int numplayers = 1; // Minimum = 1 player.

  do {

    std::cout << "How many players will be playing ? Please enter between [1-5] : ";
    std::cin >> numplayers;

  } while (numplayers < 1 || numplayers > 5);
  
  names.reserve(numplayers);

  std::string name;
  for (int i=1; i <= numplayers; i++) {

    std::cout << "Enter name for player-" << i << " : ";
    std::cin >> name;

    names.push_back(name);
    name.clear();
  }

  return (names.size() != 0);  
}

/*
 * Determine if players want to continue playing
 */
std::string getUserGoalResponse() {
    std::string str, upstr;
    
    while (true) {
        
        printMessage("Would you like to play a hand of BlackJack ? (Y/N) : ", PROMPT);
        std::cin >> str;
        std::cout << std::endl;    
        
        upstr = uppercase(str);
    
    if ((upstr == "Y") || (upstr == "N"))
        break;
    else
        printMessage ("Please enter a valid option (Y/N) : ", WARN);    
  };
  
  return upstr;
}

/*
 * A display routine with appropriate message for different error codes.
 * 
 * TODO: Enhance this routine to take in formatting with variable arguments
 */
void printMessage (std::string msg, MsgMode mode, int id) {
  
  assert (id >= 0);

  std::stringstream ss;

  switch (mode) {
  case INFO:
    ss << "[BlackJack-INFO-" << id << "]\t" << msg << std::endl;
    break;

  case WARN:
    ss << "[BlackJack-WARNING-" << id << "]\t" << msg << std::endl;
    gErrorReport.num_warnings++;
    break;

  case ERROR:
    ss << "[BlackJack-ERROR-" << id << "]\t" << msg << std::endl;
    gErrorReport.num_errors++;
    break;

  case SEVERE:
    ss << "[BlackJack-" << id << "]\t" << msg << std::endl;
    gErrorReport.num_severe++;
    break;

  case PROMPT:
      ss << "[BlackJack-User-Input]\t" << msg;
      break;
      
  case DEBUG:
      ss << "[BlackJack-DEBUG]\t" << msg << std::endl;
      break;
      
  case EMPTY:
      ss << "--------" << msg << "--------\n\n";
      break;
      
  default:
    break;
  }

  // NOTE: Reason to keep in stringstream is to allow for writing into a file 
  // if needed.
  std::cout << ss.str();
}

void printErrorReport() {    
    std::cout << "[BlackJack] Run completed: SEVERE(" << gErrorReport.num_severe << ") : ERRORS(" << gErrorReport.num_errors << ") : WARNINGS(" << gErrorReport.num_warnings << ")\n\n";
}
