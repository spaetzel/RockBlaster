/*******************************************************************
* Program : CS388a Assignment #2 - Asteroids
* Author  : William Spaetzel
* Student#: 250115373
* File    : CollisionInterface.h
* Modified: Oct 24, 3003
* Description:	Detects the collision between all the game objects:
* 	Asteroids, Ships and Bullets
********************************************************************/


#ifndef COLLISION_INTERFACE
#define COLLISION_INTERFACE

#include "AsteroidTypes.h"
#include "ShipTypes.h"
#include "BulletTypes.h"

int checkShipCollision (AsteroidGroup* asteroids, Ship* theShip, BulletGroup* explosionParts);
int checkBoundingBox (Asteroid* theAst,  GLpoint pointA, GLpoint pointB);
int checkBulletCollision (AsteroidGroup* asteroids, BulletGroup* bullets, BulletGroup* explosionParts);
int checkIntersections (AsteroidGroup* asteroids , BulletGroup* explosionParts, GLpoint pointA, GLpoint pointB);
int pointInShipRange (GLpoint translation, Ship* theShip);


#endif