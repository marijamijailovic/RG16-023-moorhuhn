#ifndef SCENE_H
#define SCENE_H

#include <math.h>
#include "SOIL.h"
#include "initialize.h"

#define DEG2RAD 3.14/180.0

void ground(void);
void drawPuddle(void);
void drawSun(void);
void drawCloud(void);
void drawStar(void);
void drawHome(void);
void drawCar(void);
void drawWood(void);
void drawPumpkin(void);
void drawGun(float angleLR,float angleTB);
void drawBullets(void);

#endif
