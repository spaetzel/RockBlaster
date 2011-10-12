/*******************************************************************
* Program : CS388a Assignment #2 - Asteroids
* Author  : William Spaetzel
* Student#: 250115373
* File    : .c
* Modified: Oct 24, 3003
********************************************************************/

#include <stdio.h>
#include <math.h>

#include "AsteroidTypes.h"
#include "GlobalDefines.h"
#include "ShipTypes.h"
#include "ShipInterface.h"
#include "MathInterface.h"

void resetShip (Ship *theShip)
{
	theShip->translation.x = 0;
	theShip->translation.y = 0;
	theShip->direction.x=0;
	theShip->direction.y=0;
	theShip->rotation = 0;
	theShip->rotating = 0;
	theShip->accelerating = FALSE;
	theShip->timeLeftToFire = 0;
	theShip->status = ALIVE;
	theShip->timeLeftToSpawn = 0;
	theShip->flameOn = TRUE;
}

void updateShip (Ship *theShip, AsteroidGroup* asteroids, double_t secondsPassed)
{
	GLpoint newDir;
	GLfloat x, y ;

	if (theShip->status == ALIVE)
	{
		if (theShip->timeLeftToFire > 0)
			theShip->timeLeftToFire--;
	
		if (theShip->rotating != 0)
		{
			rotateShip (theShip, theShip->rotating);
			
			/* Set the rotation to the large value This is so that the
			player can rotate a small amount by tapping 
			the key and a large amount by holding it down */
	/*		if (abs(theShip->rotating) != LG_ROTATE)
			{

					if (theShip->rotating > 0)
					{
						theShip->rotating = LG_ROTATE*secondsPassed;
					}
					else
					{
						theShip->rotating = -LG_ROTATE*secondsPassed;
					}	
			}
     */
		}
			
			
				
	
		if (theShip->accelerating == TRUE)
			speedUpShip (theShip);
	
		theShip->translation.x += theShip->direction.x*secondsPassed;
		theShip->translation.y += theShip->direction.y*secondsPassed;
		x = theShip->translation.x ; 
		y = theShip->translation.y ;
		
		if (x > MAX_X) {
			theShip->translation.x = MIN_X + 1.0 ;
		}	
		if (x < MIN_X) {
			theShip->translation.x = MAX_X - 1.0 ;
		}
		if (y > MAX_Y) {
			theShip->translation.y = MIN_Y + 1.0 ;
		}
		if (y < MIN_Y) {
			theShip->translation.y = MAX_Y - 1.0 ; 
		}
	
		// The drag 
/*		newDir.x = theShip->direction.x * DRAG * secondsPassed;
		newDir.y = theShip->direction.y * DRAG * secondsPassed;
 
 
 theShip->direction = newDir;
 
*/	
	}
	else
	{ 
		if (theShip->timeLeftToSpawn <= 0)
		{
			
			if (theShip->status == HYPERSPACE)
			{
				theShip->status = ALIVE;
			}
			else if ( asteroids != NULL && !asteroidGroupInShipRange ( asteroids, theShip) )
			{
				theShip->status = ALIVE;
			}
		}
		else
		{
			theShip->timeLeftToSpawn--;
		}
	}
	
}


void accelerateShip (Ship *theShip)
{
	theShip->accelerating = TRUE;
}


void stopShipAccel (Ship *theShip)
{
	theShip->accelerating = FALSE;
}

void speedUpShip (Ship *theShip)
{
	GLfloat hyp;
	GLfloat addX = ACCEL*cos( theShip->rotation - PI/2 );
	GLfloat addY = ACCEL*sin( theShip->rotation + PI/2 );
	
	GLfloat newX = theShip->direction.x + addX;
	GLfloat newY = theShip->direction.y + addY;
	hyp = sqrt ( ( newY * newY) + ( newX * newX ) );
	
	if ( hyp < MAX_SHIP_SPEED)
	{
		theShip->direction.x += addX;
		theShip->direction.y += addY;
	}
	
}


void turnShipLeft (Ship *theShip, double secondsPassed)
{
	if (theShip->rotating >= 0.0)
	{
		theShip->rotating = -SM_ROTATE*secondsPassed;
	}
	
}

void turnShipRight (Ship *theShip, double secondsPassed)
{
	if (theShip->rotating <= 0.0)
	{
		theShip->rotating = SM_ROTATE * secondsPassed;
	}
	
}

void stopShipTurn (Ship *theShip)
{
	theShip->rotating = 0;
}

/* rotates the ship and checks if the roataion is near a 90
 dregree angle if so it rounds to that angle
 */
 
void rotateShip (Ship *theShip, GLfloat rotation)
{
	GLfloat newRot;
	newRot = theShip->rotation+ rotation; 	
	
	if (newRot > 2*PI)
		newRot = newRot - 2*PI;
	
	if (newRot < 0)
	{
		newRot = newRot + 2 * PI;
	}
	
	/* Round the angle to any of the 90 degrees, since the user likely would want
	to be facing that direction if they are within RANGE radians of the angle */
    if (inRangeOf (newRot, 0, RANGE) )
		newRot = 0;
	else if (inRangeOf (newRot, PI/2, RANGE) )
		newRot = PI/2;
	else if (inRangeOf (newRot, PI, RANGE) )
		newRot = PI;
	else if (inRangeOf ( newRot, PI + PI/2, RANGE) )
		newRot = PI + PI/2;
	else if (inRangeOf (newRot, 2*PI, RANGE) )	
		newRot = 2*PI;
	
	theShip->rotation = newRot;
		
		
}



void displayShip (Ship* theShip)
{
	if (theShip -> status == ALIVE)
	{
		displayPolygon ( theShip->shape, theShip->translation, theShip->rotation * -DEGINRAD, 1);
		if (theShip->accelerating)
		{
			if ( theShip->flameOn )
			{
				displayPolygon ( theShip->flameShape, theShip->translation, theShip->rotation * -DEGINRAD, 1);
				theShip->flameOn = FALSE;
			}
			else
			{
				theShip->flameOn = TRUE;
			}
		}
	}

}


void explodeShip ( Ship* theShip)
{
	resetShip ( theShip);
	theShip->status = DEAD;
	theShip->timeLeftToSpawn = SPAWN_TIME;
	
}  

void hyperspaceShip ( Ship* theShip)
{

 	if (theShip->status == ALIVE)
	{
		theShip->status = HYPERSPACE;
		theShip->timeLeftToSpawn = HYPERSPACE_TIME;
		theShip->direction.x= theShip->direction.y = 0;
		theShip->translation.x = (rand() % (int)MAX_X*2) - MAX_X;
		theShip->translation.y = (rand() % (int)MAX_Y*2) - MAX_Y;
	}
	
}  



Polygon* getShipConvexHull ( Ship* theShip)
{
	int i;
	int* pointsInHull = (int*) malloc ( MAX_VERTICES * sizeof (int) );
	Polygon allVertices;
	Polygon* hull = (Polygon*) malloc ( sizeof ( Polygon) );
	
	int numShipVertices = theShip->shape->numVertices -1;
	allVertices.numVertices =  2* numShipVertices;
	for ( i = 0; i < numShipVertices; i++)
	{ 

		allVertices.vertex[i]= allVertices.vertex[i+ numShipVertices] 
			=  rotatePoint( theShip->shape->vertex[i], theShip->rotation );
		pointsInHull[i]= i;
		
	}

	for (i =0; i < numShipVertices; i++ )
	{
		allVertices.vertex[i+ numShipVertices].x += theShip->direction.x;
		allVertices.vertex[i+ numShipVertices].y += theShip->direction.y;
		pointsInHull[i + numShipVertices]= i + numShipVertices;
	}
	
	
	hull->numVertices = Convex_Hull_2D(allVertices.numVertices, allVertices.vertex, pointsInHull);
	
	for (i = 0; i < hull->numVertices; i++)
	{
		hull->vertex[i] = allVertices.vertex[pointsInHull[i] ];
	}
	hull->vertex [i+1] = hull->vertex[0];
	hull->numVertices++;
	
	return hull;
}

	
