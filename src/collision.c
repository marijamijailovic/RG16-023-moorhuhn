#include "collision.h"

float max(float a, float b)
{
  return a > b ? a : b;
}
float min(float a, float b)
{
  return a < b ? a : b;
}
int collisionChicken(Object c,Bullet b,float size)
{
  float x, y, z, d;
  
  x = max(c.xCurr-size/2.0, min(b.xPos, c.xCurr + size/2.0));
  y = max(c.yCurr-size/2.0, min(b.yPos, c.yCurr + size/2.0));
  z = max(c.zCurr-size/2.0, min(b.zPos, c.zCurr + size/2.0));

  d = (x-b.xPos)*(x-b.xPos) + (y-b.yPos)*(y-b.yPos) + (z-b.zPos)*(z-b.zPos);

  if(d <= b.bulletSize){
      return 1;
  }
  return 0;
}

int collisionSun(float x,float y,float z,float r,Bullet b)
{
  float xB,yB,zB,rB,d;

  xB = b.xPos;
  yB = b.yPos;
  zB = b.zPos;
  rB = b.bulletSize;

  d = sqrt((x-xB)*(x-xB)+(y-yB)*(y-yB)+(z-zB)*(z-zB));

  if (d <= (r+rB)){
    return 1;
  }
  return 0;
}

void bulletCollision(void)
{
  int i,j,k;
  for (i=0; i<BULLET_MAX; i++){
      if (bullets[i].alive){
          for (j=0; j<CHICKEN_KART_MAX; j++){
            if(chickensKart[j].alive){
              if (collisionChicken(chickensKart[j],bullets[i],chickensKart[i].scale)){
                  bullets[i].alive = 0;
                  chickensKart[j].activeDeadChicken = 1;
                  chickensKart[j].alive = 0;
                  break;
              }
            }
          }
          for(k=0;k<7;k++){
            if(chicken[k].alive){
              if(collisionChicken(chicken[k],bullets[i],chicken[i].scale)){
                bullets[i].alive = 0;
                chicken[k].activeDeadChicken = 1;
                chicken[k].alive = 0;
                break;
              }
            }
          }
          if(sunAlive){
            if(collisionSun(xSun,ySun,zSun,rSun,bullets[i])){
              bullets[i].alive = 0;
              sunAlive = 0;
              cloudAlive = 0;
              starAlive = 1;
              glClearColor(0.1,0.1,0.1,1);
              break;
            }
          }
      }
  }
}
