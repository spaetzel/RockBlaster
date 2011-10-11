/*******************************************************************
* Program :	CS388a Assignment #2 - Asteroids
* Author  :	William	Spaetzel
* Student#:	250115373
* File	  :	CollisionImplementation.c
* Modified:	Oct	24,	3003
* Description:	Detects	the	collision between all the game objects:
*	Asteroids, Ships and Bullets
********************************************************************/

#include "GlobalDefines.h"
#include "CollisionInterface.h"
#include "CollisionTypes.h"
#include "AsteroidTypes.h"
#include "ShipTypes.h"
#include "BulletTypes.h"
#include "PolygonTypes.h"
#include "GameTypes.h"
#include "MathInterface.h"

/* checkBoundingBox
 Input:	Asteroid* theAst The asteroid to be	checked	against
		GLpoint	pointA The 1st endpoint	of the line	being checked
		GLpoint	pointB The 2nd endpoint	of the line	being checked
 Output: TRUE if one of	the	points is within the bounding box of the asteroid 
		FALSE otherwise
 Checks	to see if one of the points	is within the bounding box of the asteroid,	
*/

int	checkBoundingBox (Asteroid*	theAst,	 GLpoint pointA, GLpoint pointB)
{
	int	astMaxX, astMaxY, astMinX, astMinY;	/* The coordinates of the asteroids	bounding box */
	GLfloat	maxX, maxY,	minX, minY;	/* The extremes	of the two points */
	
	maxX = rmax (pointA.x, pointB.x);
	minX = rmin (pointA.x, pointB.x);
	maxY = rmax (pointA.y, pointB.y);
	minY = rmin (pointA.y, pointB.y);
	

	if (theAst->alive)
	{
		astMaxX	= theAst->translation.x+ ( theAst->shape->maxx / theAst->size ); 
		astMaxY	= theAst->translation.y+ ( theAst->shape->maxy/	theAst->size);
		astMinX	= theAst->translation.x+ ( theAst->shape->minx	/ theAst->size);
		astMinY	= theAst->translation.y+ ( theAst->shape->miny	/ theAst->size);

		if ( (maxX <= astMaxX && maxY <= astMaxY &&	maxX >=	astMinX	&& maxY	>= astMinY)	||
		(minX <= astMaxX &&	minY <=	astMaxY	&& minX	>= astMinX && minY >= astMinY)	)
		{
			/* a point is within the bounding box*/
			return TRUE;
		}
		
	}
	
	/* No point within the bounding box, we must have missed the asteroid */
	return FALSE;
}

/* checkIntersections
 Input:	AsteroidGroup* asteroids The group of asteroids to be checked
		BulletGroup* explosionParts The place where the animation of the explosion will be stored
		GLpoint	pointA The 1st endpoint	of the line	being checked
		GLpoint	pointB The 2nd endpoint	of the line	being checked
 Output: int The score recieved	by hitting the asteroids
 Checks	to see if the line with the endpoints pointA and pointB intersects any of the asteroids
*/
int	checkIntersections (AsteroidGroup* asteroids, BulletGroup* explosionParts, GLpoint pointA, GLpoint pointB)
{
	
	int	i, j; /* Counters */
	GLfloat	deltaXab, deltaXcd,	deltaYab, deltaYcd; /* Slopes of the lines */
	GLfloat	uX,	uY; /* The parameter in the parametric equations */
	GLpoint	pointC,	pointD; /* The endpoints of the asteroid line being checked*/

	deltaXab = pointB.x	- pointA.x;
	deltaYab = pointB.y	- pointA.y;
	

	for	( i	= 0; i < asteroids->numAsteroids; i++)
	{
		Asteroid* theAst = &asteroids->rocks[i];
		
		if ( theAst->alive && checkBoundingBox ( theAst, pointA, pointB	) )
		{

			for	( j	= 0; j < theAst->shape->numVertices	-1;	j++)
			{
				pointC.x = ( theAst->shape->vertex[j].x	/ theAst->size)	+ theAst->translation.x;
				pointC.y = (theAst->shape->vertex[j].y/	theAst->size)  + theAst->translation.y;
				pointD.x = (theAst->shape->vertex[j	+1].x /	theAst->size) +	theAst->translation.x;
				pointD.y = (theAst->shape->vertex[j	+1].y /	theAst->size) +	theAst->translation.y;
				
				deltaXcd = pointD.x	- pointC.x;
				deltaYcd = pointD.y	- pointC.y;
				
				if ( deltaXcd != deltaXab)
					uX =  (	pointA.x - pointC.x) / ( deltaXcd -	deltaXab) ;
				else
					uX = INFINITE;
				if ( deltaYcd != deltaYab)
					uY =  (	pointA.y - pointC.y) / ( deltaYcd -	deltaYab) ;
				else
					uY = INFINITE;

				if (  abs (uX -	uY)	< 1	)
				{
				
					/* The lines intersect - but line segments ?*/
					if ( uX	>= 0 &&	uX <= 1)
					{
						/* yes */
						return splitAsteroid (asteroids, explosionParts,  theAst );
					}
				}
			}
		}
	}

	return 0;
	
}

/* checkBulletCollision
 Input:	AsteroidGroup* asteroids All the asteroids currently onscreen
	BulletGroup* bullets The bullets being checked
	BulletGroup* explosionParts	The	bullets	that represent the explosion of	asteroids
 Output: int The score recieved	by hitting the asteroids
 Checks	to see if any of the bullets collide with any asteroid and returns the value of the 
 asteroids that	were destroyed
*/
int	checkBulletCollision (AsteroidGroup* asteroids,	BulletGroup* bullets, BulletGroup* explosionParts)
{
	int	i; /* Counter */
	int returnVal, collisionVal; /* Values of the collisions*/

	returnVal =	0;
	for	(i = 0;	i <	MAX_BULLETS; i++)
	{
		if (bullets->bullet[i].lifeLeft	> 0)
		{

			GLpoint	pointA,	pointB;
			
			/* Checks behind and ahead of the bullet so	that it	is difficult for the asteroid to go	
			 between the bullets */
			pointA.x = bullets->bullet[i].translation.x	;
			pointA.y = bullets->bullet[i].translation.y	;
			pointB.x = bullets->bullet[i].translation.x	+  bullets->bullet[i].direction.x;
			pointB.y = bullets->bullet[i].translation.y	+  bullets->bullet[i].direction.y;
		
			collisionVal = 
				checkIntersections (asteroids,	explosionParts , pointA, pointB);

			
			if ( collisionVal != 0)
			{
				bullets->bullet[i].lifeLeft	= 0;
				bullets->numBullets	--;
				returnVal+=collisionVal;
			}
		}
	}
	return returnVal;
}

/* checkShipCollision
 Input:	AsteroidGroup* asteroids All the asteroids currently onscreen
	Ship* theShip The ship being checked against
	BulletGroup* explosionParts	The	bullets	that represent the explosion of	asteroids
 Output: int The score recieved	by hitting the asteroids
 Checks	to see if the ship collides	with any asteroid and returns the value	of the 
 asteroids that	were destroyed
*/
int	checkShipCollision (AsteroidGroup* asteroids, Ship*	theShip, BulletGroup* explosionParts)
{

	Polygon* hull =	getShipConvexHull (theShip); /*	The	convex hull	including the ship and the ship	at 
													its	next position */
	GLpoint	pointA,	pointB;	/* The endpoints of	the	line currently being checked */
	int	i; /* Counter */
	int	collisionVal; /* The score returned	by hitting an asteroid */

	/* Go through each line	of the convex hull and check if	it intersects with an asteroid */
	for	(i = 0;	i <	hull->numVertices; i++)
	{
		pointA.x = hull->vertex[i].x + theShip->translation.x;
		pointA.y = hull->vertex[i].y + theShip->translation.y;
		pointB.x = hull->vertex[i+1].x + theShip->translation.x;
		pointB.y = hull->vertex[i+1].y + theShip->translation.y;;
		collisionVal = checkIntersections (	asteroids, explosionParts, pointA, pointB );

		if (collisionVal !=	0)
		{
			/* The ship	hit	an asteroid	*/
			return collisionVal;
		}
	}

	/* Didn't hit anything */
	return 0;	
}

/* checkShipCollision
 Input:	GLpoint translation The point being checked
	Ship* theShip The ship being checked against
 Output: int TRUE if the point is within the range of the ship, FALSE otherwise
 Checks	to see if the point is within RANGE_SIZE pixels of the ship
*/
int	pointInShipRange (GLpoint translation, Ship* theShip)
{
	GLfloat	rangeMaxX, rangeMaxY, rangeMinX, rangeMinY;
	
	rangeMinX =	theShip->translation.x - RANGE_SIZE;
	rangeMinY =	theShip->translation.y - RANGE_SIZE;
	rangeMaxX =	theShip->translation.x + RANGE_SIZE;
	rangeMaxY =	theShip->translation.y + RANGE_SIZE;

	if ( translation.x < rangeMaxX &&  translation.x > rangeMinX &&
		 translation.y < rangeMaxY &&  translation.y > rangeMinY )
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}

}