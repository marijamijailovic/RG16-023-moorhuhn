#ifndef GUI_H
#define GUI_H

#include <GL/freeglut.h>
#include <string.h>
#include "initialize.h"
#include "callback.h"

#define SECOND 1000

int rezultat;
int startTime;
int prevTime;
int oldTime;
int scoreID;
int timeID;
char text[100];
char scoreText[20];
char timeText[20];

void renderString(float x, float y, float z, void *font,const char *string,float r,float g,float b);
void printScore();
void printTime();
void printText();
void gameOver();

#endif
