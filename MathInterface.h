/*******************************************************************
* Program : CS388a Assignment #2 - Asteroids
* Author  : William Spaetzel
* Student#: 250115373
* File    : MathInterface.h
* Modified: Oct 24, 3003
* Contains several math related functions for the game
********************************************************************/

#ifndef MATH_INTERFACE
#define MATH_INTERFACE

#include <stdlib.h>
#include <GLUT/glut.h>
#include "PolygonTypes.h"

int inRangeOf (float value, float checkTo, float range);
float  rmin ( float one, float two);
float  rmax ( float one, float two);
GLpoint rotatePoint (GLpoint point, float rotation);

#endif
