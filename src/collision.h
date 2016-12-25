#ifndef COLLISION_H
#define COLLISION_H

#include <math.h>
#include "initialize.h"

int collisionChicken(Object c,Bullet b,float size);
int collisionSun(float x,float y,float z,float r,Bullet b);
void bulletCollision(void);

#endif
