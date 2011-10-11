/*******************************************************************
* Program : CS388a Assignment #2 - Asteroids
* Author  : William Spaetzel
* Student#: 250115373
* File    : PolygonTypes.h
* Modified: Oct 24, 3003
* Holds the Polygon and GLpoint data types
********************************************************************/

#ifndef POLYGON_TYPES
#define POLYGON_TYPES

#include <GLUT/glut.h>
#include "GlobalDefines.h"

typedef struct
{ 
    GLfloat x, y ; 
} GLpoint ; 

typedef struct
{
   GLpoint vertex[MAX_VERTICES];
   GLint   numVertices ;
   GLfloat minx, maxx, miny, maxy ;     /* Polygon's bounding box */
}Polygon; 

#include "PolygonInterface.h"

#endif
