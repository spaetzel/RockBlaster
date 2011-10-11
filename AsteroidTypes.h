/*******************************************************************
* Program : CS388a Assignment #2 - Asteroids
* Author  : William Spaetzel
* Student#: 250115373
* File    : AsteroidTypes.h
* Modified: Oct 24, 3003
* Description: Contains the Asteroid and AsteroidGroup data structures
********************************************************************/

#ifndef ASTEROID_TYPES
#define ASTEROID_TYPES

#include <GLUT/glut.h>

#include "GlobalDefines.h"
#include "PolygonTypes.h"

/* Data type for an asteroid */
typedef struct
{                       
	Polygon* shape; 	/*The shape of this asteroid */
	enum AsteroidSize {LARGE=1, MEDIUM=2, SMALL=4} size; 	/* The size of this asteroid - divide all vertex coords by this*/
	GLpoint direction;   /* Direction of a rock */
	GLpoint translation;  /* Position of a rock */
	GLfloat speed; /*The speed of the asteroid */
	GLint   alive ;    /* Should the asteroid be shown? */
}Asteroid;

/*Data type for a group of asteroids */
typedef struct{                     
	Asteroid rocks[MAX_ROCKS]; /* All the asteroids in the group  */
	GLint numAsteroids ; /* how many asteroids are there? */
	GLint	timeLeftToSpawn; /* How long until the asteroids should be shown on the screen */
} AsteroidGroup;

#include "AsteroidInterface.h"

#endif
