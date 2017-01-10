#ifndef INITIALIZE_H
#define INITIALIZE_H

#include <GL/glut.h>
#include <stdio.h>
#include <time.h>
#include "SOIL.h"

#define CHICKEN_KART_MAX 20
#define CHICKEN_MAX 8
#define IMAGES_MAX 16
#define BULLET_MAX 100

/*definisem makroe za teksture*/
#define EXPLORER 0
#define JOURNALIST 1
#define NINJA 2
#define FISHER 3
#define STUDENT 4
#define STATUE 5
#define FLY 6
#define DRIVER 7
#define DEAD 8
#define KART 9
#define PUMPKIN 10
#define CLOUD 11
#define WOOD 12
#define HOME 13
#define CAR 14
#define GAME_OVER 15

typedef struct Bullet{
  float bulletSize;
  float xPos;
  float yPos;
  float zPos;
  float xSpeed;
  float ySpeed;
  float zSpeed;
  int alive;
}Bullet;
Bullet bullets[BULLET_MAX];

/*Koordinate sunca*/
float xSun,ySun,zSun,rSun;
/*flag koji odredjuje da li smo upucali sunce ili ne*/
int sunAlive;
/*flag za oblake*/
int cloudAlive;
/*flag za zvezde*/
int starAlive;

/*Koordinate za pistolj*/
float xGun,yGun,zGun;

typedef struct Object{
  float xCurr;
  float yCurr;
  float zCurr;
  float scale;
  int alive;
  float alpha;
  int animationAction;
  int activeDeadChicken;
}Object;

Object chickensKart[CHICKEN_KART_MAX];
Object chicken[CHICKEN_MAX];
Object star[5];

int gameOverID;

int tex[IMAGES_MAX];

int chickenIndex;

float bara;

float angleLR;
float angleTB;

int getRand(int min,int max);
void initializeImages(void);
void initializeChicken(void);
void initializeSunStar(void);
void initializeBulletsGun(void);
void initializeLight(void);
void texture(int texId);

#endif
