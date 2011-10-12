/*******************************************************************
* Program : CS388a Assignment #2 - Asteroids
* Author  : William Spaetzel
* Student#: 250115373
* File    : .h
* Modified: Oct 24, 3003
********************************************************************/

#ifndef BULLET_INTERFACE
#define BULLET_INTERFACE

#include "ShipTypes.h"
#include "BulletTypes.h"


void createBullets (BulletGroup* bullets);
int fireBullet (BulletGroup* bullets, Ship *theShip);
void updateBullets (BulletGroup* bullets, double secondsPassed);
void displayBullets(BulletGroup* bullets);
void createBullet (BulletGroup* bullets, GLpoint translation, GLpoint direction, GLfloat lifeLeft);


#endif
