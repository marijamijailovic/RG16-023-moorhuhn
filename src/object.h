#ifndef OBJECT_H
#define OBJECT_H

#include <GL/glut.h>
#include "SOIL.h"
#include "initialize.h"

float angleRotation; /*ugao rotacije istrazivaca*/

void drawChickenKart(int index);
void drawChicken(int id);
void dead(Object c);

#endif
