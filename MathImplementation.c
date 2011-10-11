/*******************************************************************
* Program : CS388a Assignment #2 - Asteroids
* Author  : William Spaetzel
* Student#: 250115373
* File    : MathImplementation.c
* Modified: Oct 24, 3003
* Contains several math related functions for the game
********************************************************************/

#include <GLUT/glut.h>
#include <math.h>
#include "MathTypes.h"
#include "MathInterface.h"
#include "PolygonTypes.h"

/* rotatePoint
 Input: GLpoint point The point to rotate 
 	float rotation How many radians to roate the point
 Output: GLpoint rotated around the origin by rotation radians
 Rotates and returns the passed point
*/
GLpoint rotatePoint (GLpoint point, float rotation)
{
	/* x' = x cos f - y sin f */
	/* y' = y cos f + x sin f */
	GLpoint rotated;
	rotated.x = point.x * cos (- rotation  ) - point.y * sin (- rotation );	
	rotated.y = point.y * cos (- rotation  ) + point.x *  sin (- rotation );	
	return rotated;
}

/* inRangeOf
 Input: float value The value to see if its in the range
 	float checkTo	The value being checked against
	float range How close to checkTo is in the range
 Output: int TRUE if value is within range of checkTo FALSE otherwise
 Checks to see if value is within range of checkTo
*/
int inRangeOf (float value, float checkTo, float range)
{
	if ( (value < checkTo) && checkTo - range <= value)
			return TRUE;
	else if ( (value > checkTo) && checkTo + range >= value)
		return TRUE;
	else if ( value == checkTo)
		return TRUE;
	
	else
	{
		return FALSE;
	}
}

/* min
 Input: float one The 1st number to check
 	float two The 2nd number to check
 Output: float the smaller of the two numbers
 Returns the smaller of the two numbers
*/
float rmin ( float one, float two)
{
	if ( one < two )
	{
		return one;
	}
	else
	{ 	
		return two;
	}
}

/* max
 Input: float one The 1st number to check
 	float two The 2nd number to check
 Output: float the larger of the two numbers
 Returns the larger of the two numbers
*/
float rmax ( float one, float two)
{
	if ( one > two )
	{
		return one;
	}
	else
	{ 	
		return two;
	}
}
