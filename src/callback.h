#ifndef CALLBACK_H
#define CALLBACK_H

#include <GL/glut.h>
#include <stdio.h>

/*Timers*/
#define TIMER_ID 1
#define TIMER_INTERVAL 40
#define TIMER_ID_CHICKEN 2
#define TIMER_CHICKEN 0

/*Deklarisemo funkcije*/
static void onKeyboard(unsigned char key,int x,int y);
static void onReshape(int width, int height);
static void onDisplay(void);
static void onTimer(int id);
static void chickenTimer(int id);

void renderBitmapString(float x, float y, void *font,const char *string,float r,float g,float b);

/*Flag za odredjivanje da li je animacija u toku*/
static int animationOnGoing;
static int animationChicken;

/*Pozicija kamere*/
float x=5.0f,y=1.0f,z=10.0f;

int chickenIndex = 0;

float angle = 0.0;

#endif
