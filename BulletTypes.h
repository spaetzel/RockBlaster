/*******************************************************************
* Program : CS388a Assignment #2 - Asteroids
* Author  : William Spaetzel
* Student#: 250115373
* File    : BulletTypes.h
* Modified: Oct 24, 3003
* Hold the data structures for the bullet module
********************************************************************/

#ifndef BULLET_TYPES
#define BULLET_TYPES

#include "PolygonTypes.h"
#include "GlobalDefines.h"

typedef struct
{                
	GLpoint direction;  /* What to add to the translation of the bullet every frame */ 
	GLpoint translation;  /* The position of the bullet */
	GLfloat lifeLeft; 	/* How many frames until the bullet will be killed */
}Bullet;

typedef struct
{
	Bullet bullet [MAX_STORE_BULLETS]; /* The bullets in the group */
	GLint numBullets; /* How many bullets are in the group */
}BulletGroup;


#include "BulletInterface.h"

#endif 
