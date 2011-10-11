/*******************************************************************
* Program : CS388a Assignment #2 - Asteroids
* Author  : William Spaetzel
* Student#: 250115373
* File    : ShipTypes.h
* Modified: Oct 24, 3003
* Holds the Ship data type
********************************************************************/

#ifndef SHIP_TYPES
#define SHIP_TYPES


#include "PolygonTypes.h"




typedef struct
{                            
	Polygon* shape; 	/*The shape of this asteroid */
	Polygon* flameShape;	/*The shape of the flame */
	GLint 	flameOn;	/* If the flame should be shown*/
	GLfloat rotation; 	/* How much the shop is rotated */
	GLpoint direction;      /* Direction of the ship */
	GLpoint translation;   	/* Position of the ship*/
	GLfloat rotating;	/*How much to rotate the ship per frame */
	GLint 	accelerating;	/* Are the ship's thrusters on? */
	enum StatusModes {ALIVE, DEAD, HYPERSPACE} status;  /* Is the ship alive, dead or in hyperspace */           
	GLint timeLeftToFire; /*How many frames until the ship can fire again */
	GLint timeLeftToSpawn; /* How many frames until the ship can come back to life or from hyperspace*/
}Ship;

#include "ShipInterface.h"

#endif
