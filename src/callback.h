#ifndef CALLBACK_H
#define CALLBACK_H

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

/*Flag za odredjivanje da li je animacija u toku*/
static int animationOnGoing;
static int animationChicken;

#endif
