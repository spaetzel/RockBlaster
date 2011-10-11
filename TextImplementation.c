
#include <string.h>

#include "TextTypes.h"
#include "TextInterface.h"
#include "GlobalDefines.h"
#include "PolygonTypes.h"
#include "GameTypes.h"
#include "HiScoreTypes.h"

void displayInsertCoin ( Polygon* theFont )
{
	displayText (COIN_X, COIN_Y, "1 coin 1 play", INFO_SIZE, theFont);
}

void displayCopy (Polygon* theFont)
{
	displayText (COPY_X, COPY_Y, "2003 redune.cc", COPY_SIZE, theFont);
}



void displayCoinText ( CoinMessages coinMessage, Polygon* font)
{
	displayInsertCoin ( font);
		displayText ( MESSAGE_X, MESSAGE_Y, coinMessage.messages[coinMessage.currentMessage], 
			 INFO_SIZE, font);
}

void displayHelp(Polygon* theFont)
{
	GLfloat currentY = HELP_MAX_Y;

	displayText ( HELP_X, currentY, "left arrow rotate counterclockwise", INFO_SIZE, theFont);
	currentY -= INFO_SPACING_Y;
	displayText ( HELP_X, currentY, "right arrow rotate clockwise", INFO_SIZE, theFont);
	currentY -= INFO_SPACING_Y;
	displayText ( HELP_X, currentY, "up arrow accelerate", INFO_SIZE, theFont);
	currentY -= INFO_SPACING_Y;
	displayText ( HELP_X, currentY, "f fire",INFO_SIZE,  theFont);
	currentY -= INFO_SPACING_Y;
	displayText ( HELP_X, currentY, "space hyperspace",INFO_SIZE,  theFont);
	currentY -= INFO_SPACING_Y;
	displayText ( HELP_X, currentY, "p pause", INFO_SIZE, theFont);
	currentY -= INFO_SPACING_Y;
	displayText ( HELP_X, currentY, "q quit",INFO_SIZE,  theFont);
	currentY -= INFO_SPACING_Y;
	currentY -= INFO_SPACING_Y;
	displayText ( HELP_X, currentY, "press any key or wait to go back to game",INFO_SIZE,  theFont);
}



void displayGameOver ( Polygon* theFont)
{
	displayText ( GAME_OVER_X, GAME_OVER_Y, "game over", INFO_SIZE, theFont);
}

int displayText (int posX, int posY, char string[], GLfloat size, Polygon* theFont)
{
	/* font has characters in this order 
	0-9: 	Digits 0-9
	10-35:	Characters A-Z
 	36:	Underscore
	37:	Dot
	*/
	
  int x, curChar;
  GLfloat fontWidth;
  GLpoint point;
  point.x = posX;
  point.y = posY;

   fontWidth = ( theFont[ 0 ].maxx / size - theFont[0].minx / size) ;
 
  for (x=0; x< strlen( string); x++)
    {
	    curChar = string[x];
	    if (curChar == '.')
	    {
		    curChar = FONT_DOT;
	    }
	    else if ( curChar == '_')
	    {
		    curChar = FONT_UNDERSCORE;
	    }
	    else if (curChar <= '0' + 10)
	    {
		    curChar -= '0';
	    }
	    else if (curChar < 'a' + 26)
	    {
		    curChar = curChar - 'a' + 10;
	    }
	   
	    
	    if (curChar >= 0)
		    displayPolygon ( &theFont[ curChar ], point, 0, size );

	    
	    point.x += fontWidth + FONT_SPACING; 
	
    }
    return point.x;
 
}
