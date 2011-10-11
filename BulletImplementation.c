/*******************************************************************
* Program : CS388a Assignment #2 - Asteroids
* Author  : William Spaetzel
* Student#: 250115373
* File    : .c
* Modified: Oct 24, 3003
********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "GlobalDefines.h"
#include "BulletTypes.h"
#include "BulletInterface.h"
#include "ShipTypes.h"
#include "PolygonTypes.h"

/* createBullets
 Input: BulletGroup* bullets The group of bullets to be initialized
 Output: None
	Initializes all the bullets in the passed groupo, setting them to have a
	lifeleft value of -1 which means they shouldn't be displayed
*/
void createBullets (BulletGroup* bullets)
{
	int i;
	for (i = 0; i < MAX_STORE_BULLETS; i++)
	{
		bullets->bullet[i].lifeLeft = -1;
	}
	bullets->numBullets= 0;
}

/* fireBullet
 Input: BulletGroup* bullets The group of bullets to add to
		Ship* theShip	The ship that is firing the bullet
 Output: TRUE if a bullet was fired FALSE otherwise
	Fires a bullet from the passed ship if the ship meets the 
	requirements to fire: Can only have MAX_BULLETS bullets 
	going at once and can only fire if timeLeftToFire is 0
*/
int fireBullet (BulletGroup* bullets, Ship *theShip)
{
	if (theShip->timeLeftToFire == 0 && bullets->numBullets < MAX_BULLETS )
	{
		GLpoint bulDir; /* The direction on the new bullet */
		GLfloat shipTotalSpeed; /* The hypoteneuse of the ship's x and y directions */
		GLfloat shipX, shipY; /* The ship's x and y directions */

		/*Set it so the ship cannot fire until FIRE_DELAY frames have passed */
		theShip->timeLeftToFire = FIRE_DELAY;

		/* Turn shipX and shipY into a unit vector */
		shipX = theShip->direction.x;
		shipY = theShip->direction.y;
		shipTotalSpeed = sqrt ( shipX * shipX + shipY * shipY);

		// JUST CHANGED - TEST ME!
		if (shipTotalSpeed != 0)
		{
		//	shipX = shipX / (shipTotalSpeed * cos ( theShip->rotation) );
		//	shipY = shipY / (shipTotalSpeed * sin ( theShip->rotation) );
		}
			
		bulDir.x =  ( shipX + BULLET_SPEED * sin ( theShip->rotation ) ) ;
		bulDir.y =  ( shipY + BULLET_SPEED * cos ( theShip->rotation ) ) ;

		createBullet (bullets, theShip->translation, bulDir, MAX_LIFE);
		bullets->numBullets++;
	 
		/* A bullet was successfully fired */
		return TRUE;
	}
	else
	{
		/* No bullet was fired */
		return FALSE;
	}
}

/* createBullet
 Input: BulletGroup* bullets The group of bullets to add to
		GLpoint translation The translation to give the new bullet
		GLpoint direction The direction to give the new bullet
		GLfloat lifeLeft the lifeleft to give the new bullet
 Output: none
 Checks to find the first free  space for a new bullet and then adds a 
 bullet with the passed attributes at that location
*/

void createBullet (BulletGroup* bullets, GLpoint translation, GLpoint direction, GLfloat lifeLeft)
{
	int freeBullet; /* the index where the bullet will be added */
	for (freeBullet = 0; freeBullet < MAX_STORE_BULLETS; freeBullet++)
	{
		if (bullets->bullet[freeBullet].lifeLeft<=0)
		{
			/* We found a free space */
			break;
		}		
	}
	if ( freeBullet < MAX_STORE_BULLETS)
	{
		bullets->bullet[freeBullet].translation = translation;
		bullets->bullet[freeBullet].direction = direction;
		bullets->bullet[freeBullet].lifeLeft = lifeLeft;
	}
	bullets->numBullets++;
}

/* updateBullets
 Input: BulletGroup* bullets The group of bullets to be updated
 Output: none
Updates teh posion of all the bullets using their direction, as well as checking
to see if any bullets have expired, removing the ones which have
*/

void updateBullets (BulletGroup* bullets)
{
	int i;
	GLfloat x, y ;
	for (i = 0 ; i <  MAX_STORE_BULLETS ; i++)
	{
		if ( bullets->bullet[i].lifeLeft > 0)
		{
			bullets->bullet[i].lifeLeft -= REMOVE_LIFE;
			/* If we just killed the bullet */
			if (bullets->bullet[i].lifeLeft <= 0)
			{
				bullets->bullet[i].lifeLeft = 0;
				bullets->numBullets--;
			}
			else
			{
				/* The bullet is alive, update it */

				bullets->bullet[i].translation.x += bullets->bullet[i].direction.x;
				bullets->bullet[i].translation.y += bullets->bullet[i].direction.y;

				/* Wrapping */
				x = bullets->bullet[i].translation.x ; 
				y = bullets->bullet[i].translation.y ;
				if (x > MAX_X) {
					bullets->bullet[i].translation.x = MIN_X + 1.0 ;
				}
				if (x < MIN_X) {
					bullets->bullet[i].translation.x = MAX_X - 1.0 ;
				}
				if (y > MAX_Y) {
					bullets->bullet[i].translation.y = MIN_Y + 1.0 ;
				}
				if (y < MIN_Y) {
					bullets->bullet[i].translation.y = MAX_Y - 1.0 ; 
				}
			}	
		}
		
	}
}

/* displayBullets
 Input: BulletGroup* bullets The group of bullets to be displayed
 Output: none
 Displays all the bullets to the screen, also updates the numBullets counter
 to the number of bullets which were successfully displayed
*/

void displayBullets(BulletGroup* bullets)
{
	int i; /* counter */
	int displayed = 0; /* The number of bullets displayed */
	glBegin(GL_POINTS);
		for (i = 0 ; i < MAX_STORE_BULLETS; i++) {
			if (bullets->bullet[i].lifeLeft > 0)
			{
				glVertex2f (bullets->bullet[i].translation.x, bullets->bullet[i].translation.y);
				displayed++;
			}
		}
	glEnd();
	bullets->numBullets = displayed;

	
}
