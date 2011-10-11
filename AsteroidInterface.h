/*******************************************************************
* Program : CS388a Assignment #2 - Asteroids
* Author  : William Spaetzel
* Student#: 250115373
* File    : AsteroidInterface.h
* Modified: Oct 24, 3003
* Description: Controls the behavior of the asteroids and draws them 
*				to the screen
********************************************************************/

#ifndef ASTEROID_INTERFACE
#define ASTEROID_INTERFACE

#include "AsteroidTypes.h"
#include "ShipTypes.h"
#include "BulletTypes.h"


void createAsteroidGroup( AsteroidGroup* asteroids, GLint numAsteroids, 
	Polygon shapes[], GLint numShapes, Ship* theShip);
int updateAsteroids (AsteroidGroup*);
void displayAsteroids(AsteroidGroup* asteroids);

int splitAsteroid (AsteroidGroup* asteroids, BulletGroup* explosionParts, Asteroid* theRock);
Asteroid* createAsteroid(AsteroidGroup* asteroids, GLint size, GLpoint translation);
void explodeAsteroid (Asteroid* theRock, BulletGroup* explosionParts);
int asteroidGroupInShipRange ( AsteroidGroup* asteroids, Ship* theShip);
int asteroidInShipRange ( Asteroid* theAst, Ship* theShip);


#endif
