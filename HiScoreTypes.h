/*******************************************************************
* Program : CS388a Assignment #2 - Asteroids
* Author  : William Spaetzel
* Student#: 250115373
* File    : HiScoreTypes.h
* Modified: Oct 24, 3003
********************************************************************/

#ifndef HISCORE_TYPES
#define HISCORE_TYPES

#include "GlobalDefines.h"

typedef struct
{
	int score; 
	char initials [NUM_INITIALS];
}ScoreRecord;

typedef struct
{
	int numScores;
	ScoreRecord record [ MAX_SCORES];
	int maxHi; /* The highest score */
	int minHi; /* The lowest score in the top MAX_SCORES */
	char* file; /* The file the scores are to be saved in */
}HighScores;

#include "HiScoreInterface.h"

#endif
