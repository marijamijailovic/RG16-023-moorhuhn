#ifndef CALLBACK_H
#define CALLBACK_H

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include "initialize.h"
#include "scene.h"
#include "object.h"
#include "collision.h"
#include "gui.h"

/*Timers*/
#define TIMER_ID 1
#define TIMER_INTERVAL 30
#define TIMER_ID_CHICKEN 2
#define TIMER_CHICKEN 0

/*Deklarisemo funkcije*/
void onKeyboard(unsigned char key,int x,int y);
void onReshape(int width, int height);
void onDisplay(void);
void onTimer(int id);
void chickenTimer(int id);

/*Flag za odredjivanje da li je animacija u toku*/
int animationOnGoing;
int animationChicken;

#endif
