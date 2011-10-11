/*******************************************************************
* Program : CS388a Assignment #2 - Asteroids
* Author  : William Spaetzel
* Student#: 250115373
* File    : .h
* Modified: Oct 24, 3003
********************************************************************/

#ifndef SHIP_INTERFACE
#define SHIP_INTERFACE

#include "AsteroidTypes.h"
#include "PolygonTypes.h"
#include "ShipTypes.h"

void resetShip (Ship *theShip);
void updateShip (Ship *theShip, AsteroidGroup* asteroids);

void accelerateShip (Ship *theShip);
void turnShipLeft (Ship *theShip);
void turnShipRight (Ship *theShip);
void rotateShip (Ship *theShip, GLfloat rotation);
void displayShip (Ship* theShip);
void stopShipTurn (Ship *theShip);
void stopShipAccel (Ship *theShip);
void speedUpShip (Ship *theShip);
void explodeShip ( Ship* theShip);
Polygon* getShipConvexHull ( Ship* theShip);
void hyperspaceShip ( Ship* theShip);

#endif
