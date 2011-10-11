/*******************************************************************
* Program : CS388a Assignment #2 - Asteroids
* Author  : William Spaetzel
* Student#: 250115373
* File    : PlayerTypes.h
* Modified: Oct 24, 3003
* The types for the player module
********************************************************************/

#ifndef PLAYER_TYPES
#define PLAYER_TYPES

#include "PolygonTypes.h"
#include "GlobalDefines.h"

typedef struct
{
	int score; /* the player's score */
	int livesLeft; /* guess */
	Polygon *shipShape; /* The shape of the ship - used to show the lives left */
	int lastFreeLife; /* The score where the player last got a free life */
	int level; /* The player's level*/
	char initials[NUM_INITIALS]; /* The player's initials */
}Player;


#include "PlayerInterface.h"

#endif
