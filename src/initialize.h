#ifndef INITIALIZE_H
#define INITIALIZE_H

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "SOIL.h"

#define CHICKEN_KART_MAX 20
#define IMAGES_MAX 14
#define BULLET_MAX 100

/*definisem makroe za teksture*/
#define ISTRAZIVAC 0
#define NOVINAR 1
#define NINJA 2
#define PECAROS 3
#define STUDENT 4
#define KOKASTATUA 5
#define LETECA 6
#define DEAD 7
#define KART 8
#define BUNDEVA 9
#define CLOUD 10
#define DRVO 11
#define KUCA 12
#define AUTO 13

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

typedef struct Object{
  float xCurr;
  float yCurr;
  float zCurr;
  float scale;
  int alive;
  int animationAction;
  int activeDeadChicken;
}Object;

Object chickensKart[CHICKEN_KART_MAX];
Object chicken[8];
Object star[5];

int tex[IMAGES_MAX];

int chickenIndex;

/*animacija za baru*/
float bara;

float angleLR;
float angleTB;

int getRand(int min,int max);
void initialize(void);
void lightSetup(void);
void materialSetup(void);
void renderBitmapString(float x, float y, void *font,const char *string,float r,float g,float b);
void texture(int texId);

#endif
