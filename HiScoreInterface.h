/*******************************************************************
* Program : CS388a Assignment #2 - Asteroids
* Author  : William Spaetzel
* Student#: 250115373
* File    : HiScoreInterface.h
* Modified: Oct 24, 3003
* Keeps track of the game's high scores
********************************************************************/

#ifndef HISCORE_INTERFACE
#define HISCORE_INTERFACE

#include "PlayerTypes.h"

int loadScores(char* f1, HighScores *hiScores);
void sortScores ( HighScores* hiScores );
int saveScores(HighScores* hiScores);
void displayInitials(char initials[NUM_INITIALS], Polygon* theFont);
void displayHiScores ( HighScores* hiScores, Polygon* theFont);
#endif
