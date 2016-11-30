#ifndef SCENE_H
#define SCENE_H

#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

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
}Chicken;
Chicken chickens[CHICKEN_MAX];

typedef struct Bullet{
  float bulletSize;
  float xPos;
  float yPos;
  float zPos;
  int active;
}Bullet;
Bullet bullets[BULLET_MAX];

extern void ground(void);
extern void drawChicken(int index);
extern void die(void);
extern void drawGun(float angleGun);
extern void drawBullets(float angleBullet);
extern int collision(Chicken c,Bullet b);
extern void bulletChickenCollision(void);

extern void lightSetup(void);
extern void materialSetup(void);

#endif
