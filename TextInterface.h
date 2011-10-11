/*******************************************************************
* Program : CS388a Assignment #2 - Asteroids
* Author  : William Spaetzel
* Student#: 250115373
* File    : TextInterface.h
* Modified: Oct 24, 3003
* Displays strings of text to the screen as well as various built 
* in messages
********************************************************************/

#ifndef TEXT_INTERFACE
#define TEXT_INTERFACE

#include "TextTypes.h"
#include "PolygonTypes.h"
#include "GameTypes.h"

int displayText (int posX, int posY, char string[], GLfloat size, Polygon* theFont);
void displayCopy ( Polygon* theFont);
void displayInsertCoin ( Polygon* theFont );
void displayHelp(Polygon* theFont);
void displayCoinText ( CoinMessages coinMessage, Polygon* font);
void displayGameOver ( Polygon* theFont);


#endif
