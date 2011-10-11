/*******************************************************************
* Program : CS388a Assignment #2 - Asteroids
* Author  : William Spaetzel
* Student#: 250115373
* File    : .c
* Modified: Oct 24, 3003
********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#include <time.h>
#include <GLUT/glut.h>


#include "GameTypes.h" 
#include "CollisionInterface.h"
#include "GlobalDefines.h"
#include "AsteroidTypes.h"
#include "PlayerTypes.h"
#include "HiScoreTypes.h"

#include "PolygonTypes.h"
#include "ShipTypes.h"
#include "BulletTypes.h"
#include "TextTypes.h"



int currentInitial;
int paused;
int hiScore;
int numAsteroidShapes;
CoinMessages coinMessage;
Polygon asteroidShapes[MAX_ROCKS];
Polygon shipShape[1], flameShape[1];
Polygon font[MAX_LETTERS];
Ship theShip;
AsteroidGroup asteroids ;                                     // Asteroids 
BulletGroup bullets;
BulletGroup explosionParts; 		// The flying pixels for all the current explosions
Player thePlayer;
HighScores hiScores;

int modeDelay;	/* How long to stay in the current mode - used for HELP and GAME_OVER */

GameMode currentMode;
GameMode previousMode;
int hiScore;


void myInit()
{  
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glLineWidth(1.0) ;
	glPointSize (2);
}

int min ( GLfloat one, GLfloat two)
{
	if ( one < two )
	{
		return one;
	}
	else
	{ 	
		return two;
	}
}

int max ( GLfloat one, GLfloat two)
{
	if ( one > two )
	{
		return one;
	}
	else
	{ 	
		return two;
	}
}

void resetGame ()
{
	resetLevel(thePlayer.level);
	resetShip ( &theShip);
	resetPlayer ( &thePlayer, theShip.shape );
	theShip.timeLeftToSpawn = GAME_START_TIME;
	asteroids.timeLeftToSpawn = GAME_START_TIME;
	theShip.status = DEAD;
	switchGameMode ( PLAYING );
	
}
void switchGameMode (GameMode newMode)
{
	previousMode = currentMode;
	 currentMode = newMode;
	if (newMode == INSERT_COIN || newMode == SCORE_TABLE)
	{
		
		resetShip ( &theShip);
		resetPlayer ( &thePlayer, theShip.shape );
			
		glutKeyboardFunc(coinKeyboard);
		glutSpecialFunc (coinSpecialKeyboard);
		
		if ( newMode == SCORE_TABLE)
		{
			modeDelay = SCORE_TABLE_DELAY;
		}
		else
		{
			modeDelay = COIN_MODE_DELAY;
			setupCoinMessages();
		}
	}else if (newMode == HELP)
	{
		glutKeyboardFunc ( helpKeyboard );
		modeDelay = HELP_DELAY;
	}else if (newMode == PLAYING)
	{
		glutKeyboardFunc (playingKeyboard );
		glutSpecialUpFunc (playingSpecialKeyboardUp);
		glutSpecialFunc (playingSpecialKeyboard );
	}else if ( newMode == GAME_OVER)
	{
		modeDelay = GAME_OVER_DELAY;
	}
	else if ( newMode == INITIALS)
	{
		glutKeyboardFunc (initialsKeyboard );
		glutSpecialFunc (initialsSpecialKeyboard );
		currentInitial = 0;
		thePlayer.initials[currentInitial] = 'a';
	}

}

void myDisplay()

{
	
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.7, 0.7, 0.7);
	
		
	if ( currentMode == PLAYING || currentMode == INSERT_COIN || currentMode== GAME_OVER)
	{
		displayAsteroids (&asteroids);

		
	}

	if ( currentMode == PLAYING)
	{
		/* Display the BULLETS */
		displayBullets (&bullets);
		/* Display the ship */
		displayShip (&theShip);
	
		/* Display the asteroid explosion parts */
		displayBullets (&explosionParts);
		
		displayLivesLeft( &thePlayer);
	}
	else if ( currentMode == INSERT_COIN)
	{
		
		displayCoinText ( coinMessage, font);
		
	}
	else if (  currentMode == HELP)
	{
		displayHelp( font );
	}
	else if ( currentMode == GAME_OVER)
	{
		displayGameOver( font );
	}
	else if ( currentMode == INITIALS )
	{
		displayInitials (thePlayer.initials, font );
	}
	else if ( currentMode == SCORE_TABLE )
	{
		displayCoinText ( coinMessage, font);
		displayHiScores ( &hiScores, font );
	}
	/* Display the score, lives left, etc */
	displayPlayerData (&thePlayer, hiScores.maxHi, font);
	displayCopy (font);	
		

	glutSwapBuffers();
}


 

void myReshape(int w, int h)

{ glViewport(0,0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(MIN_X, MAX_X, MIN_Y, MAX_Y, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}


void resetLevel(int level)
{
	int numAsteroids;
	if (level == 1)
		numAsteroids = ASTEROIDS_ONE;
	else if (level == 2)
		numAsteroids = ASTEROIDS_TWO;
	else
		numAsteroids = ASTEROIDS_OTHER;
	

	createAsteroidGroup( &asteroids, numAsteroids, asteroidShapes, numAsteroidShapes, &theShip );
	
	if (currentMode == PLAYING)
	asteroids.timeLeftToSpawn = LEVEL_DELAY_TIME;
printf ("reset");
	createBullets ( &bullets );
	createBullets ( &explosionParts);
}

int checkCollisions()
{
	

	int shipCollideVal, bulletCollideVal;
		
	if ( theShip.status == ALIVE )
	{
		shipCollideVal = checkShipCollision(&asteroids, &theShip, &explosionParts);
	}
	else
	{
		shipCollideVal = 0;
	}
	bulletCollideVal = checkBulletCollision(&asteroids, &bullets, &explosionParts);
	
	
	if (shipCollideVal != 0)
	{
		loseLife (&thePlayer );
		explodeShip ( &theShip);
	}
	return shipCollideVal + bulletCollideVal;
}

int lastDisplayed = 0;

void updateDisplay()
{
    if( lastDisplayed == 0 || clock() > lastDisplayed + 0.02 * CLOCKS_PER_SEC )
    {
       
	int asteroidsLeft;
	if (currentMode == PLAYING || currentMode == INSERT_COIN || currentMode == GAME_OVER)
	{
		asteroidsLeft = updateAsteroids(&asteroids);
		
		updateBullets (&explosionParts);
	}
	
	if (  currentMode == PLAYING)
	{

	
		increasePlayerScore (&thePlayer, checkCollisions());

		if (thePlayer.score > hiScores.maxHi)
		{
			hiScores.maxHi = thePlayer.score;
		}
		updateShip(&theShip, &asteroids);
		updateBullets (&bullets);
		
		
		if (asteroidsLeft == 0)
		{
			thePlayer.level++;
			resetLevel (thePlayer.level);
		}
		
		if ( thePlayer.livesLeft < 0)
		{
			switchGameMode (GAME_OVER);
		}
	} else if ( currentMode == INSERT_COIN || currentMode == SCORE_TABLE)
	{
		coinMessage.timeToNextMessage--;
		if ( coinMessage.timeToNextMessage <= 0)
		{
			coinMessage.timeToNextMessage = MESSAGE_DELAY;
			coinMessage.currentMessage++;
			if (coinMessage.currentMessage >= coinMessage.numMessages)
				coinMessage.currentMessage = 0;
		}
		modeDelay--;
		
			
		if (modeDelay <= 0)
		{
			if ( currentMode == SCORE_TABLE)
			
			{
				switchGameMode ( INSERT_COIN );
			}
			else
			{
				switchGameMode ( SCORE_TABLE );
			}
		}
		
	} else if (  currentMode == HELP)
	{
		modeDelay--;
		if (modeDelay <= 0)
		{
			switchGameMode ( previousMode );
		}
	} else if (  currentMode == GAME_OVER)
	{
		modeDelay--;
		if (modeDelay <= 0)
		{
			if ( thePlayer.score > hiScores.minHi || hiScores.numScores < MAX_SCORES)
			{
				switchGameMode ( INITIALS );
			}else
			{
				switchGameMode ( SCORE_TABLE );
			}
		}
	} 
		
        lastDisplayed = clock();
	glutPostRedisplay();
    }
}

void playingSpecialKeyboard(int theKey, int mouseX, int mouseY)
{
	switch(theKey)
	{
		case GLUT_KEY_UP:
			accelerateShip ( &theShip);
			break;
		case GLUT_KEY_DOWN:
			break;
		case GLUT_KEY_LEFT:
			turnShipLeft ( &theShip );
			break;
		case GLUT_KEY_RIGHT:
			turnShipRight ( &theShip );
			break;
		default:
			break;
	}

}

void playingSpecialKeyboardUp(int theKey, int mouseX, int mouseY)
{
	switch(theKey)
	{
		case GLUT_KEY_UP:
			stopShipAccel ( &theShip );
			break;
		case GLUT_KEY_DOWN:
			break;
		case GLUT_KEY_LEFT:
			stopShipTurn ( &theShip );
			break;
		case GLUT_KEY_RIGHT:
			stopShipTurn ( &theShip );
			break;
		default:
			break;
	}

}

void playingKeyboard(unsigned char theKey, int mouseX, int mouseY)
{ 
	switch(theKey)
	{
		case 'f':
			fireBullet ( &bullets , &theShip);
			break;
		case 'p':
			if (!paused)
			{
				glutIdleFunc (NULL);
				paused = TRUE;
			}
			else
			{
				glutIdleFunc (updateDisplay);
				paused = FALSE;
			}
			break;
		case 'h':
			switchGameMode ( HELP );
			break;
		case 'q':
			exit (0);
			break;
		case ' ':
			hyperspaceShip( &theShip );
			break;
		default:
			break;
	}
}


				 
void initialsKeyboard(unsigned char theKey, int mouseX, int mouseY)
{ 
	switch(theKey)
	{
		case 'q':
			exit (0);
			break;
		case ' ':
			currentInitial++;
			if (currentInitial >= NUM_INITIALS)
			{
				insertHiScore ( thePlayer, &hiScores );
				switchGameMode (SCORE_TABLE);
			}
			else
			{
				thePlayer.initials[currentInitial]= 'a';
			}
			break;
		default:
			break;
	}
}


	
void initialsSpecialKeyboard(int theKey, int mouseX, int mouseY)
{
	switch(theKey)
	{
		case GLUT_KEY_LEFT:
			changeCurrentInitial ( &thePlayer, currentInitial, -1 );
			break;
		case GLUT_KEY_RIGHT:
			changeCurrentInitial ( &thePlayer, currentInitial, 1 );
			break;
		default:
			break;
	}

}

void helpKeyboard (unsigned char theKey, int mouseX, int mouseY)
{
	switchGameMode ( previousMode );
}

void coinKeyboard (unsigned char theKey, int mouseX, int mouseY)
{
	switch (theKey)
	{
		case 's':
			resetLevel(thePlayer.level);
			resetGame();
			break;
		case 'h':
			switchGameMode (HELP);
			break;
		case 'q':
			exit (0);
			break;
	}
}
void coinSpecialKeyboard (int theKey, int mouseX, int mouseY)
{
	switch (theKey)
	{
		case GLUT_KEY_F1:
			resetGame();
			break;
		case GLUT_KEY_F3:
			switchGameMode ( HELP );
			break;
	}
}

void setupCoinMessages()
{
	coinMessage.numMessages =	5;
	coinMessage.timeToNextMessage = MESSAGE_DELAY;
	coinMessage.messages[0] = "";
	coinMessage.messages[1] = "push start";
	coinMessage.messages[2] = "s for 1 player game";
	coinMessage.messages[3]	=  "h for help";
	coinMessage.messages[4] = "q to quit";
}



void startGame(char* asteroidFile, char* shipFile, char* flameFile, char* fontFile, char* hiFile)
{
	int numShipShapes, numFontShapes, numFlameShapes, numScores;
	numAsteroidShapes = loadPolygons(asteroidFile, asteroidShapes) ;
	numShipShapes = loadPolygons(shipFile, shipShape);
	numFlameShapes = loadPolygons (flameFile, flameShape);
	numFontShapes = loadPolygons (fontFile, font) ;
	numScores = loadScores ( hiFile, &hiScores);
	
	if ( numAsteroidShapes != -1 && numShipShapes != -1 && numFlameShapes != -1 && numFontShapes != -1
		&& numScores != -1)
	{
	
		theShip.shape= &shipShape[0];
		theShip.flameShape = &flameShape[0];
			
		
		glutDisplayFunc(myDisplay);
		glutReshapeFunc(myReshape);
		glutIgnoreKeyRepeat (TRUE);
		glutIdleFunc (updateDisplay);
	
		
	
		resetLevel(thePlayer.level);
		switchGameMode ( INSERT_COIN );
		glutMainLoop(); 
	}
	else
	{
		 printf("Error loading a file!\n");
	}
}
	
