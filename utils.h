/* 
 * File:     utils.h
 * Author:   Sharad C. Sundararajan
 * Function: Function declarations the all generic utilities
 * 
 * EDIT HISTORY:
 * 
 * DATE                 NAME                            DESCRIPTION
 * ----                 ----                            -----------
 * July 20, 2014        Sharad Sundararajan             Created
 */


#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

#define BLACKJACK      21 /* Natural or Number of cards to win */
#define NUM_DEAL_CARDS 2  /* Number of cards dealer will initially deal */

// #define DEBUG_MODE /* May be enabled to help with debug */

enum MsgMode {INFO, WARN, ERROR, SEVERE, PROMPT, DEBUG, EMPTY};

/* Global Error Report */
typedef struct {
    
    int num_errors;
    int num_warnings;
    int num_severe;
} ReportStruct;
extern ReportStruct gErrorReport;

/* Utilities */
std::string uppercase(const std::string &inputstr);
void        wait(int n); /* To simulate delay for user experience */

/* Get input from User (command line) */
bool        getActionResponse     (std::string name, std::string& response);
bool        getSplitResponse      (std::string name, std::string rank);
bool        getPlayerInfoResponse (std::vector<std::string> &names);
int         getUserBetResponse    (std::string name, double allowed_max);
std::string getUserGoalResponse   ();

/* Customized display with warning/error/info... */
void        printMessage          (std::string msg, MsgMode mode = EMPTY, int id = 0);
void        printErrorReport      ();

#endif
