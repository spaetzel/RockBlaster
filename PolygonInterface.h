/*******************************************************************
* Program : CS388a Assignment #2 - Asteroids
* Author  : William Spaetzel
* Student#: 250115373
* File    : PolygonInterface.h
* Modified: Oct 24, 3003
* Handles creating, loading, displaying and gift wrapping polygons
********************************************************************/

#ifndef POLYGON_INTERFACE
#define POLGYON_INTERFACE

int loadPolygons(char* f1, Polygon Shapes[]);
void displayPolygon (Polygon* shape, GLpoint translation, GLint rotation, GLfloat scale);

/*********************************************** 
Gift wrapping convex hull algorithm taken from 
http://skal.planet-d.net/coding/hull.html
************************************************/
static float Angle(const GLpoint P0, const GLpoint P1, const GLpoint P2);
static int Compare(const GLpoint A, const GLpoint B);
static int Cmp_Lo(const void *a, const void *b);
static int Cmp_Hi(const void *a, const void *b);
static int Sweep(int Nb, const GLpoint* Pts, int* Ind);
int Convex_Hull_2D(int Nb, const GLpoint* Pts, int* Ind);

#endif
