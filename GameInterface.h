

#ifndef GAME_INTERFACE
#define GAME_INTERFACE

#include <GLUT/glut.h>
#include "GameTypes.h"

void myInit();
void switchGameMode (GameMode newMode);
void myDisplay();
void myReshape(int w, int h);
void resetLevel(int level);
void updateDisplay();
void playingSpecialKeyboard(int theKey, int mouseX, int mouseY);
void playingSpecialKeyboardUp(int theKey, int mouseX, int mouseY);
void playingKeyboard(unsigned char theKey, int mouseX, int mouseY);
void helpKeyboard (unsigned char theKey, int mouseX, int mouseY);
void coinKeyboard (unsigned char theKey, int mouseX, int mouseY);
void coinSpecialKeyboard (int theKey, int mouseX, int mouseY);
void initialsKeyboard (unsigned char theKey, int mouseX, int mouseY);
void initialsSpecialKeyboard (int theKey, int mouseX, int mouseY);
void startGame(char* asteroidFile, char* shipFile, char* flameFile, char* fontFile, char* hiFile);
void setupCoinMessages();
int checkCollisions();
void resetGame ();

#endif
