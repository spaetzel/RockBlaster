/*******************************************************************
* Program : CS388a Assignment #2 - Asteroids
* Author  : William Spaetzel
* Student#: 250115373
* File    : GameTypes.h
* Modified: Oct 24, 3003
* Holds the data types for the game module
********************************************************************/

#ifndef GAME_TYPES
#define GAME_TYPES

#include "GlobalDefines.h"

/* The possible game modes */
typedef enum {INSERT_COIN = 0, PLAYING, SCORE_TABLE, HELP, GAME_OVER, INITIALS}GameMode;

/* The messages to show when the game first starts up */
typedef struct
{
	int numMessages; /* How many messages */
	int timeToNextMessage; /* How many frames until the next message */
	int currentMessage; /* The index of the message currently being shown */
	char* messages[MAX_MESSAGES]; /* The messages */
}CoinMessages;


#endif
