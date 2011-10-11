/*******************************************************************
* Program : CS388a Assignment #2 - Asteroids
* Author  : William Spaetzel
* Student#: 250115373
* File    : HiScoreImplementation.c
* Modified: Oct 24, 3003
* Keeps track of the game's high scores
********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "GlobalDefines.h"
#include "HiScoreTypes.h"
#include "HiScoreInterface.h"
#include "PlayerTypes.h"
#include "PolygonTypes.h"
#include "TextTypes.h"

/* insertHiScore
 Input: Player thePlayer The player to be inserted
		HighScores* hiScores The group of high scores
 Output: none
 Adds the player's score and intials to the high score table
*/
void insertHiScore ( Player thePlayer, HighScores* hiScores)
{
	int setScore; /* index of where the plaer will be inserted */

	if ( hiScores->numScores == MAX_SCORES )
	{
		setScore = hiScores->numScores-1;
		
	}
	else
	{
		hiScores->numScores++;
		setScore = hiScores->numScores -1;
	}
	
	hiScores->record[setScore].score= thePlayer.score;
	strcpy ( hiScores->record[ setScore ].initials, thePlayer.initials);
	sortScores( hiScores );
	
	saveScores ( hiScores);
}

/* sortScores
 Input: HighScores* hiScores The group of high scores to be sorted
 Output: none
 Bubble sorts the high score table to have the highest scores at the lowest index
*/
void sortScores ( HighScores* hiScores )
{
	int i, j; /* Counters */
	ScoreRecord tempRecord; /* Used for flipping records */

	for (i = 0; i < hiScores->numScores; i++)
	{
		for (j = i; j < hiScores->numScores; j++)
		{
			if (hiScores->record[i].score < hiScores->record[j].score )
			{
				tempRecord = hiScores->record[i];
				hiScores->record[i]= hiScores->record[j];
				hiScores->record[j] = tempRecord;
			}
		}	
	}
	
	/* Make sure the maxHi and minHi still have the appropriate values*/
	hiScores->maxHi = hiScores->record[0].score;
	hiScores->minHi = hiScores->record[hiScores->numScores-1].score;

}

/* loadScores
 Input: char* f1 The filename where the scores are saved
		HighScores* hiScores The structure to store the scores in
 Output: int the number of scores successfuly loaded, -1 if the file failed to open
 Loads the high score table from a file
*/
int loadScores(char* f1, HighScores* hiScores)
{ 
	FILE *fd1; /* File pointer */
	int i; /*Counters */
	int numScores; /* the number of scores in the file*/
	if ((fd1 = fopen(f1,"r")) == NULL) {
		return -1 ;
	} 
	else
	{
		hiScores->file =f1;
		fscanf(fd1,"%d",&numScores) ;
		for (i = 0 ; i < numScores && !feof ( fd1) ; i++) 
		{
			fscanf(fd1,"%d %s", & hiScores->record[i].score,   &hiScores->record[i].initials) ;
		}
		
		fclose(fd1) ;
		
		hiScores->numScores= numScores;
		sortScores ( hiScores ); 
	
		return numScores;
	}
}

/* saveScores
 Input: HighScores* hiScores The score table to be saved
 Output: 1 if the scores were successfully saved, -1 if the file failed to open
 Saves the high score table to a file
*/
int saveScores(HighScores* hiScores)
{
	FILE *fdl; /* File pointer */
	int i; /* Counter */
	
	if ( (fdl = fopen(hiScores->file, "w")) == NULL)
	{
		return -1;
	}
	else
	{
		fprintf (fdl, "%d\n", hiScores->numScores);
		for (i = 0; i < hiScores->numScores; i++)
		{
			fprintf (fdl, "%d %s\n", hiScores->record[i].score,  hiScores->record[i].initials);
		}
		
		fclose (fdl);
		return 1;
	}
}

/* displayInitials
 Input: char initials[NUM_INITIALS] The current initials entered
		Polygon* theFont The game font
 Output: none
 Displays the screen asking the user to enter his initials for the high score table
*/
void displayInitials(char initials[NUM_INITIALS], Polygon* theFont)
{
	int i; /* Counter */
	GLfloat currentY = INITIAL_INFO_MAX_Y; /* coordinate for the text */
	GLfloat	currentX = INITIALS_X; /* coordinate for the text */

	displayText ( INITIAL_INFO_X, currentY, "your score is one of the ten best", INFO_SIZE, theFont);
	currentY -= INFO_SPACING_Y;
	displayText ( INITIAL_INFO_X, currentY, "please enter your initials", INFO_SIZE, theFont);
	currentY -= INFO_SPACING_Y;
	displayText (INITIAL_INFO_X, currentY, "push rotate to select letter", INFO_SIZE, theFont);
	currentY -= INFO_SPACING_Y;
	displayText ( INITIAL_INFO_X, currentY, "push hyperspace when letter is correct",INFO_SIZE,  theFont);
	currentY -= INFO_SPACING_Y;

	for ( i = 0; i < NUM_INITIALS; i++)
	{
		char* display = (char*) malloc ( 2 *sizeof(char) );
		display[0] = initials[i];
		display[1] = '\0';
		currentX = displayText ( currentX, INITIALS_Y, display, INITIALS_SIZE, theFont );
	}
}

/* displayHiScores
 Input: HighScores* hiScores 
		Polygon* theFont The game font
 Output: none
 Displays the high score table
*/
void displayHiScores ( HighScores* hiScores, Polygon* theFont)
{
	int i; /* Counter */
	char* hiText= (char*) malloc ( 255 * sizeof (char) ); /* the text to be displayed*/
	GLfloat currentY = HISCORE_MAX_Y; /* Text location */
	
	displayText ( HISCORE_X, HISCORE_Y, "high scores", INFO_SIZE, theFont);
	
	for ( i = 0; i < hiScores->numScores; i++)
	{
		sprintf (hiText, "%2d. %6d %s", i+1, hiScores->record[i].score, hiScores->record[i].initials);
	
		displayText ( HISCORE_X, currentY, hiText, INFO_SIZE, theFont );
		currentY -= INFO_SPACING_Y;
	}
}

