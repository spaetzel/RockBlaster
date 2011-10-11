/*******************************************************************
* Program : CS388a Assignment #2 - Asteroids
* Author  : William Spaetzel
* Student#: 250115373
* File    : PlayerInterface.h
* Modified: Oct 24, 3003
* Keeps track of the player's score, lives left, etc
* and displays this data to the screen
********************************************************************/

#ifndef PLAYER_INTERFACE
#define PLAYER_INTERFACE

#include "GameTypes.h"
#include "PolygonTypes.h"
#include "ShipTypes.h"
#include "PlayerTypes.h"


void resetPlayer(Player* thePlayer, Polygon* shipShape);
void displayPlayerData(Player* thePlayer , int hiScore, Polygon* font);
void displayLivesLeft(Player* thePlayer);
int loseLife (Player* thePlayer);
int increasePlayerScore( Player* thePlayer, int addScore );
void changeCurrentInitial (Player* thePlayer,int currentInitial, int change);

#endif
