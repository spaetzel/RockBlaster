/*******************************************************************
* Program : CS388a Assignment #2 - Asteroids
* Author  : William Spaetzel
* Student#: 250115373
* File    : PlayerImplementation.c
* Modified: Oct 24, 3003
* Keeps track of the player's score, lives left, etc
* and displays this data to the screen
********************************************************************/

#include <GLUT/glut.h>
#include <stdlib.h>
#include <stdio.h>

#include "PlayerTypes.h"
#include "PlayerInterface.h"
#include "PolygonTypes.h"
#include "ShipTypes.h"
#include "GlobalDefines.h"
#include "TextTypes.h"

/* resetPlayer
 Input: Player* thePlayer The Player to reset
		Polygon* shipShape The shape of the ship - used for displaying lives left
 Output: none
 Resets the player, setting all variables to their initial states
*/
void resetPlayer(Player* thePlayer, Polygon* shipShape)
{
	int i;
	thePlayer->score = 0;
	thePlayer->livesLeft = START_LIVES;
	thePlayer->shipShape = shipShape;
	thePlayer->lastFreeLife = 0;
	thePlayer->level = 1;

	/* Set the initials to "___" used when entering the initials for the hi score table */
	for (i = 0; i< NUM_INITIALS; i++)
	{
		thePlayer->initials[i] = '_';
	}
}

/* displayPlayerData
 Input: Player* thePlayer The Player to show the data for
		int hiScore The maximum score recorded in the hi score table
		Polygon* font The screen font 
 Output: none
 Displays the score, and hi score to the screen 
*/
void displayPlayerData(Player* thePlayer, int hiScore, Polygon* font)
{
	char* scoreText = malloc (20 * sizeof(char) ); /* The score as a string */
	char* hiScoreText = malloc (3 * sizeof(char) ); /* The hiscore as a string */

	sprintf (scoreText, "%d", thePlayer->score);
	
	if (hiScore < 10)
		sprintf (hiScoreText, "0%d", hiScore);
	else
		sprintf (hiScoreText, "%d", hiScore);
	
	displayText ( SCORE_X, SCORE_Y, scoreText, SCORE_SIZE, font);
	displayText ( HI_X, HI_Y, hiScoreText, HI_SIZE, font);

}

/* displayLivesLeft
 Input: Player* thePlayer The Player to show the lives for
 Output: none
 Displays the lives left to the screen 
*/
void displayLivesLeft(Player* thePlayer)
{
	int shipSpacing; /* How far apart in the x direction to space the ships */
	int i; /* Counter */
	GLpoint translation; /* Where the current ship is being drawn */

	shipSpacing = thePlayer->shipShape->maxx - thePlayer->shipShape->minx + 1;
	
	for (i = 0; i < thePlayer->livesLeft; i++)
	{
		translation.x = LIVES_X +i * (shipSpacing);
		translation.y = LIVES_Y;
		displayPolygon (thePlayer->shipShape, translation, 0, 1);
	}
	
}

/* loseLife
 Input: Player* thePlayer The Player to subtract a life from
 Output: int how many lives the player now has
 Subtracts one life from the player
*/
int loseLife (Player* thePlayer )
{
	thePlayer->livesLeft--;

	return thePlayer->livesLeft;
}

/* increasePlayerScore
 Input: Player* thePlayer The Player to show add score to
		int addScore How many points to add
 Output: int how many points the player now has
 Adds the passed amount to the player's score
*/
int increasePlayerScore( Player* thePlayer, int addScore )
{
	thePlayer->score+=addScore;

	if (thePlayer->score >= NEXT_LIFE + thePlayer->lastFreeLife)
	{
		thePlayer->livesLeft++;
		thePlayer->lastFreeLife = thePlayer->score - (thePlayer->score % NEXT_LIFE);
	}

	return thePlayer->score;
}

/* changeCurrentInitial
 Input: Player* thePlayer The Player to change the initials of
		int currentInitial The index of the initial to change
		int change How many ascii values to add to the initial
 Output: none
 Adds the passed amount to the passed initial, wrapping around through the characters
*/
void changeCurrentInitial (Player* thePlayer,int currentInitial, int change)
{
	thePlayer->initials[currentInitial]+= change;

	/* Wrap around */
	if (thePlayer->initials[currentInitial] < 'a')
	{
		thePlayer->initials[currentInitial] = 'z';
	}
	else if (thePlayer->initials[currentInitial] > 'z')
	{
		thePlayer->initials[currentInitial] = 'a';
	}
}