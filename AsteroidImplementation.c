/*******************************************************************
* Program : CS388a Assignment #2 - Asteroids
* Author  : William Spaetzel
* Student#: 250115373
* File    : AsteroidImplementation.c
* Modified: Oct 24, 3003
* Description: Controls the behavior of the asteroids and draws them 
*				to the screen
********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#include <GLUT/glut.h>

#include "GlobalDefines.h"
#include "AsteroidTypes.h"
#include "AsteroidInterface.h"
#include "ShipTypes.h"
#include "BulletTypes.h"
#include "PolygonTypes.h"
#include "GameTypes.h"
#include "CollisionTypes.h"

/* createAsteroid
 Input: AsteroidGroup* asteroids All the asteroids currently onscreen
		GLint size	The size of asteroid to be created
		GLpoint translation The translation where to create the asteroid
 Output: Asteroid* a pointer to the asteroid that was created
 Creates a new asteroid and adds it to the passed AsteroidGroup
*/

Asteroid* createAsteroid(AsteroidGroup* asteroids, GLint size, GLpoint translation)
{
	int i; /* Counter variable */
	/* Find the first free asteroid location*/
	for (i = 0; i< MAX_ROCKS && asteroids->rocks[i].alive == TRUE; i++);
	if (i < MAX_ROCKS)
	{
		/* There is room for the asteroid, add one to the group */
		Asteroid* curRock = &asteroids->rocks[i]; /* The asteroid bein added */
		
		curRock->alive = TRUE;
		curRock->size = size;
		curRock->direction.x =  ((rand() % 200) / 100.0 ) - 1;
		curRock->direction.y = ((rand() % 200) / 100.0 ) - 1 ;

		/* Randomly pick a speed */
		do{
			curRock->speed = rand() % (curRock->size * AS_SPEED_RATIO);
		}while (curRock->speed < 1);
		
		/* Make sure the numAsteroids is correct */
		if (i >= asteroids->numAsteroids)
		{
			asteroids->numAsteroids = i+1;
		}
				curRock->translation = translation;
	
		
		return curRock;
	}
	return NULL;
}

/* createAsteroidGroup
 Input: AsteroidGroup* asteroids All the asteroids currently onscreen
		GLint numAsteroids How many asteroids to put in the group
		Polygon shapes[] The shapes of the asteroids
		GLint numShapes How many shapes there are
		Ship* theShip The player controlled ship
 Output: None
 Creates a group of asteroids, making sure not to place them close to the ship
 Also randomizes the shapes for all possible asteroids so that other functions
 don't have to worry about the shape
*/
void createAsteroidGroup( AsteroidGroup* asteroids, GLint numAsteroids, 
	Polygon shapes[], GLint numShapes, Ship* theShip)
{

	int i;

	asteroids->timeLeftToSpawn = 0;
	for (i = 0; i < MAX_ROCKS; i++)
	{
		asteroids->rocks[i].alive = FALSE;
		asteroids->rocks[i].shape = &shapes[rand() % numShapes]; 
	}
	
	/* Pick a location for each asteroid, make sure this location isn't near the ship*/
	for (i = 0; i < numAsteroids; i++)
	{
		GLpoint translation;	
		do
		{
			translation.x = (rand() % (int)MAX_X*2) - MAX_X;
			translation.y = (rand() % (int)MAX_Y*2) - MAX_Y;
			
		}while (pointInShipRange ( translation, theShip) );
		createAsteroid (asteroids, LARGE, translation);
	}
	
	
}

/* updateAsteroids
 Input: AsteroidGroup* asteroids All the asteroids currently onscreen
 Output: int The number of asteroids still alive
 Updates the location of all the asteroids based on their direction and speed
*/
int updateAsteroids(AsteroidGroup* asteroids, double_t timePassed)

{ 
	int i, asteroidsLeft;
	GLfloat x, y ;
	asteroidsLeft = 0;
	if ( asteroids->timeLeftToSpawn <= 0)
	{
		for (i = 0 ; i <  asteroids->numAsteroids ; i++)
		{
			if (asteroids->rocks[i].alive)
			{
				asteroidsLeft++;
			
				asteroids->rocks[i].translation.x += asteroids->rocks[i].direction.x*asteroids->rocks[i].speed*timePassed;
				asteroids->rocks[i].translation.y += asteroids->rocks[i].direction.y*asteroids->rocks[i].speed*timePassed;

				/* Wrap the asteroids around the screen */
				x = asteroids->rocks[i].translation.x ; 
				y = asteroids->rocks[i].translation.y ;
				if (x > MAX_X) {
					asteroids->rocks[i].translation.x = MIN_X + 1.0 ;
				}
				if (x < MIN_X) {
					asteroids->rocks[i].translation.x = MAX_X - 1.0 ;
				}
				if (y > MAX_Y) {
					asteroids->rocks[i].translation.y = MIN_Y + 1.0 ;
				}
				if (y < MIN_Y) {
					asteroids->rocks[i].translation.y = MAX_Y - 1.0 ; 
				}
			}
		}
	}
	else
	{
		asteroids->timeLeftToSpawn--;
		asteroidsLeft = 1;
	}
	return asteroidsLeft;
}

/* displayAsteroids
 Input: AsteroidGroup* asteroids All the asteroids currently onscreen
 Output: none
 Displays all the asteroids to the screen
*/
void displayAsteroids(AsteroidGroup* asteroids)
{
	int i; /* counter */
	/* Display the Asteroids */
	if (asteroids->timeLeftToSpawn <= 0)
	{
		for (i = 0 ; i < asteroids->numAsteroids ; i++) {
		
			Asteroid curRock = asteroids->rocks[i];
			if (curRock.alive == TRUE)
			{
				displayPolygon (curRock.shape, curRock.translation, 0, curRock.size);	
			}	
		}
	}
}


/* splitAsteroid
 Input: AsteroidGroup* asteroids All the asteroids currently onscreen
		BulletGroup* explosionParts The structure which will hold the particles of the explosion
		Asteroid* theRock The asteroid to be split
 Output: The score the player recieves for hitting this asteroid
 Splits the passed asteroid in two and creates the animation of the asteroid breaking
*/
int splitAsteroid (AsteroidGroup* asteroids, BulletGroup* explosionParts, Asteroid* theRock)
{
	int returnVal; /* The score the player recieves for hitting this asteroid */
	GLpoint translation; /* The translation of the asteroid being split*/
	translation = theRock->translation;

	if (theRock->size== LARGE)
	{
		createAsteroid ( asteroids, MEDIUM, translation);
		createAsteroid ( asteroids, MEDIUM, translation);
		returnVal = LARGESCORE;
	}else if (theRock->size== MEDIUM)
	{
		createAsteroid ( asteroids, SMALL, translation);
		createAsteroid ( asteroids, SMALL, translation);
		returnVal = MEDIUMSCORE;
	}
	else
	{
		returnVal = SMALLSCORE;
	}
	
	theRock->alive = FALSE;	

	/* Create the explosion animation */
	explodeAsteroid ( theRock, explosionParts);
	return returnVal;
}
	
/* explodeAsteroid
 Input: Asteroid* theRock The asteroid to explode
		BulletGroup* explosionParts The structure which will hold the particles of the explosion
 Output: None
 Adds bullets located at the vertices of the asteroid to create an animation of the asteroid exploding
*/
void explodeAsteroid (Asteroid* theRock, BulletGroup* explosionParts)
{
	int i; /* Counter */
	GLpoint direction; /* The direction of the current bullet */
	GLpoint translation; /* The translation of the current bullet */
	for (i =0; i < (theRock->shape->numVertices - 1); i++)
	{ 
		translation.x = (theRock->shape->vertex[i].x / ( 2 * theRock->size ) ) + theRock->translation.x;
		translation.y = (theRock->shape->vertex[i].y / ( 2 *theRock->size ) ) + theRock->translation.y;
		direction.x = rand() % MAX_EXPLODE_SPEED;
		direction.y = rand() % MAX_EXPLODE_SPEED;
		createBullet ( explosionParts, translation, direction, rand() % EXPLOSION_LIFE );
	}
}

/* asteroidInShipRange
 Input: Asteroid* theAst The asteroid to check
		Ship* theShip	The ship to be checked against
 Output: TRUE if a point of the asteroid is in the range of the ship 
		FALSE otherwise
 Checks to see if the asteroid is within RANGE_SIZE pixels of the ship
*/
int asteroidInShipRange ( Asteroid* theAst, Ship* theShip)
{
	if (theAst->alive)
		return pointInShipRange ( theAst->translation, theShip);
	else
		return FALSE;
}

/* asteroidGroupInShipRange
 Input: AsteroidGroup* asteroids All the asteroids currently onscreen
		Ship* theShip	The ship to be checked against
 Output: TRUE if a point of an asteroid is in the range of the ship 
		FALSE otherwise
 Checks to see any asteroids asteroid are within RANGE_SIZE pixels of the ship
*/
int asteroidGroupInShipRange ( AsteroidGroup* asteroids, Ship* theShip)
{
	Asteroid* theAst; /* The asteroid currently being checked*/
	int i; /* counter*/
	for (i =0; i < asteroids->numAsteroids; i++)
	{
		theAst = &asteroids->rocks[i];
		if ( asteroidInShipRange ( theAst, theShip) == TRUE)
		{
			
			return TRUE;
		}
	}
	return FALSE;
}



