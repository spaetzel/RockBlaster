/*******************************************************************
* Program : CS388a Assignment #2 - Asteroids
* Author  : William Spaetzel
* Student#: 250115373
* File    : PolygonImplementation.c
* Modified: Oct 24, 3003
* Handles creating, loading, displaying and gift wrapping polygons
********************************************************************/

#include <stdio.h>
#include <GLUT/glut.h>
#include <stdlib.h>

#include "GlobalDefines.h"
#include "PolygonTypes.h"
#include "PolygonInterface.h"

/* displayPolgyon
 Input: Polygon* shape The polygon to display
		GLpoint translation How to translate the polygon when displaying
		GLint rotation How many degrees to rotate the polygon
		GLfloat scale How much to divide the vertices by - inverse scale
 Output: none
 Displays the passed polygon to the screen using the passed attributes
*/
void displayPolygon (Polygon* shape, GLpoint translation, GLint rotation, GLfloat scale)
{
	int j; /* Counter */
	
	glPushMatrix() ;
	glTranslatef(translation.x, translation.y,0.0) ;
	
	glPushMatrix() ;
	glRotatef(rotation,0.0f,0.0f,1.0f);

	glBegin(GL_LINES);
	for (j = 0 ; j < ( shape->numVertices - 1 ) ; j++) {
		glVertex2f(shape->vertex[j].x / scale, shape->vertex[j].y / scale);
		glVertex2f(shape->vertex[j+1].x / scale, shape->vertex[j+1].y / scale);
	}
	glEnd();
	
	/* Draw the dots at each vertex - makes it look more like a vector screen */
	glBegin(GL_POINTS);
	for (j = 0 ; j < ( shape->numVertices  ) ; j++) {
		glVertex2f(shape->vertex[j].x / scale, shape->vertex[j].y / scale);			
	}
	glEnd();
	
	
	
	glPopMatrix(); /* Pop Rotation */
	glPopMatrix(); /* Pop Translation */
}
	
/* loadPolgyons
 Input: char* f1 File to load the polygons from
		Polygon Shapes[] Where to store the polgyons
 Output: The number of polygons successfully loaded, -1 if the file fails to open
Loads Polygons from the passed filename
*/
int loadPolygons(char* f1, Polygon Shapes[])
{ 
	FILE *fd1 ; /* file pointer */
	int i, j, numPolygons; /* Counters */
	GLfloat minx, maxx, miny, maxy ; /* the bounding box for the polygon currently being read */

	if ((fd1 = fopen(f1,"r")) == NULL) {
		return -1 ;
	} 

	minx = MAX_X ;
	maxx = MIN_X ;
	miny = MAX_Y ;
	maxy = MIN_Y ;
	
	fscanf(fd1,"%d",&numPolygons) ;
	for (i = 0 ; i < numPolygons ; i++) 
	{
		fscanf(fd1,"%d",&(Shapes[i]).numVertices) ;
		for ( j = 0 ; j < (Shapes[i]).numVertices ; j++)
		{
			fscanf(fd1,"%f",&((Shapes[i]).vertex[j].x)) ; 
			fscanf(fd1,"%f",&((Shapes[i]).vertex[j].y)) ; 

			if ((Shapes[i]).vertex[j].x < minx)
			{ 
				minx = (Shapes[i]).vertex[j].x  ;
			}
			if ((Shapes[i]).vertex[j].x > maxx) { 
				maxx = (Shapes[i]).vertex[j].x  ;
			}
			if ((Shapes[i]).vertex[j].y < miny) { 
				miny = (Shapes[i]).vertex[j].y  ;
			}
			if ((Shapes[i]).vertex[j].y > maxy) { 
				maxy = (Shapes[i]).vertex[j].y  ;
			}
			(Shapes[i]).minx = minx ;
			(Shapes[i]).maxx = maxx ;
			(Shapes[i]).miny = miny ;
			(Shapes[i]).maxy = maxy ;
		}
		
  }
  fclose(fd1) ;
  return numPolygons;
}

/*********************************************** 
The rest of this file contains the 
Gift wrapping convex hull algorithm taken from 
http://skal.planet-d.net/coding/hull.html
************************************************/

///////////////////////////////////////////////////////// 
// some utils 
static const GLpoint *Sort_Pts; 
// bweuark! Damned qsort() API :( 
static float Angle(const GLpoint P0, const GLpoint P1, const GLpoint P2) 
{ 

	// "Angle" between P0->P1 and P0->P2. 
	// actually returns: ||(P1-P0) ^ (P2-P0)|| 
	float dx21 = P2.x - P1.x; 
	float dy21 = P2.y - P1.y; 
	float dx10 = P1.x - P0.x; 
	float dy10 = P1.y - P0.y; 
	return (dy21*dx10 - dx21*dy10);
} 

static int Compare(const GLpoint A, const GLpoint B) 
{ 
	if (A.x<B.x) 
		return 1; 
	else if (A.x>B.x)
		 return -1; 
	else 
		return 0; 
} 

static int Cmp_Lo(const void *a, const void *b) 
{ 
	return Compare( Sort_Pts[*(int*)a], Sort_Pts[*(int*)b] ); 
} 

static int Cmp_Hi(const void *a, const void *b) 
{ 
	return Compare( Sort_Pts[*(int*)b], Sort_Pts[*(int*)a] ); 
} 

#define SWAP(i,j) { int Tmp = Ind[i]; Ind[i] = Ind[j]; Ind[j] = Tmp; } 

////////////////////////////////////////////////////////// 
// Gift Wrap algorithm
 ////////////////////////////////////////////////////////// 

 static int Sweep(int Nb, const GLpoint* Pts, int* Ind) 
{ 
	int i, n; n = 1; 
	for(i=n+1; i<Nb; ++i) 
	{ 
		// search where to insert point #i into the chain Ind[0..n] 
		while(n-->0) 
			if ( Angle( Pts[Ind[i]], Pts[Ind[n]], Pts[Ind[n+1]] ) > 0.0 ) 
				break; 
			// Triangle (n,n+1,n+2) will be clockwise. 
			n += 2; SWAP(n,i); 
		} 
	return n; 
} 

int Convex_Hull_2D(int Nb, const GLpoint* Pts, int* Ind) 
{ 
	int n;
	if (Nb<=2) 
		return Nb; 
	Sort_Pts = Pts; // nasty. Only to overcome qsort()'s API  
	// First sweep, to find lower boundary. 
	// Points are sorted right to left.

		
	qsort(Ind, Nb, sizeof(int), Cmp_Lo); 
	n = Sweep(Nb, Pts, Ind);  
	// Second sweep, to find upper boundary 
	// Actually, we sort the remaining [n..Nb] partition in 
	// reverse order (left to right) -> The sweep loop is the same.  
	Ind[Nb] = Ind[0]; 
	// Close cycle with leftmost point 
	//qsort(Ind+n, Nb-n, sizeof(int), Cmp_Hi); 
	n += Sweep(Nb+1-n, Pts, Ind+n); 
	Ind[n] = Ind[Nb]; // restore 
	return n; 
	return 1;
 }




