#include <stdlib.h>

#include <GLUT/glut.h>

#ifndef RockBlaster_main_h
#include "main.h"
#endif


#include "GlobalDefines.h"


#include <stdio.h>
#include <time.h>
#include <GLUT/glut.h>
#include "GlobalDefines.h"
#include "GameTypes.h"

/* <main>
 Input: int argc - the number of arguments passed
 char** argv - array of the arguments
 Output: none
 Description: Main program - initializes OpenGL and then starts the game
 */ 
int main(int argc,char* argv[])
{
	char* rocksFile = "rocks.dat";
	char* shipFile = "ship.dat";
	char* flameFile = "flame.dat";
	char* fontFile = "font.dat";
	char* scoresFile = "scores.txt";
	
	srand ( time(NULL) );
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(SIZ_X,SIZ_Y);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Asteroids by William Spaetzel");
	myInit();
	
	/* Set the filenames to the arguments - all arguments are optional but must be
     passed in order rockFile shipFile flameFile fontFile scoresFile */
	if ( argc >= 2)
		rocksFile = argv[1];
	
	if (argc >= 3)
		shipFile = argv[2];
	
	if (argc >= 4)
		flameFile = argv[3];
	
	if (argc >= 5)
		fontFile = argv[4];
	
	if (argc >= 6)
		scoresFile = argv[5];
    
	startGame (rocksFile, shipFile, flameFile, fontFile, scoresFile);
    
    
	return 0;
    
}