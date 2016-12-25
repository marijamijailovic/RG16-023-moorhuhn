#ifndef SCENE_H
#define SCENE_H

#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include "SOIL.h"
#include "initialize.h"

#define DEG2RAD 3.14/180.0

void ground(void);
void drawPuddle(void);
void drawSun(void);
void drawCloud(void);
void drawStar(void);
void drawKuca(void);
void drawAuto(void);
void drawDrvo(void);
void drawBundeva(void);
void drawGun(float angleLR,float angleTB);
void drawBullets(void);

#endif
