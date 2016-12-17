#ifndef SCENE_H
#define SCENE_H

#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "SOIL.h"

#define CHICKEN_MAX 20
#define BULLET_MAX 100

typedef struct Chicken{
  /*Velicina kokoske*/
  float chickenSize;
  /*koordinate sfere*/
  float xCurr;
  float yCurr;
  float zCurr;
  float rotate;
  int alive;
  GLuint texDead;
  int activeDeadChicken;
  GLuint tex;
}Chicken;
Chicken chickens[CHICKEN_MAX];

typedef struct Bullet{
  float bulletSize;
  float xPos;
  float yPos;
  float zPos;
  int alive;
}Bullet;
Bullet bullets[BULLET_MAX];

GLuint texCloud;

extern void ground(void);
extern void drawCloud(void);
extern void drawChicken(int index);
extern void drawSun(float sunRotationParametar);
extern void die(void);
extern void drawGun(float angleLR,float angleTB);
extern void drawBullets(void);
extern int collision(Chicken c,Bullet b);
extern void bulletChickenCollision(void);
extern void dead(Chicken c);
extern void loadObj();
extern void lightSetup(void);
extern void materialSetup(void);

#endif
