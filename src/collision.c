#include "collision.h"

float max(float a, float b)
{
  return a > b ? a : b;
}
float min(float a, float b)
{
  return a < b ? a : b;
}
/*kolizija objekta sa metkom, size je velicina mog aabb boxa*/
int collisionChicken(Object c,Bullet b,float size)
{
  float x, y, z, d;

  x = max(c.xCurr-size/2.0, min(b.xPos, c.xCurr + size/2.0));
  y = max(c.yCurr-size/2.0, min(b.yPos, c.yCurr + size/2.0));
  z = max(c.zCurr-size/2.0, min(b.zPos, c.zCurr + size/2.0));

  d = sqrt((x-b.xPos)*(x-b.xPos) + (y-b.yPos)*(y-b.yPos) + (z-b.zPos)*(z-b.zPos));

  if(d <= b.bulletSize){
      return 1;
  }
  return 0;
}

/*kolizija sa suncem*/
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

/*za svaki metak i za svaki od objekata proveravam koliziju*/
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
                  /*u zavisnosti na kojoj udaljenosti je kokoska ubijena toliko poena dobijamo*/
                  if(chickensKart[j].zCurr <= -25.0){
                    rezultat += 30;
                  }
                  else if(chickensKart[j].zCurr > -25.0 && chickensKart[j].zCurr <= 0){
                    rezultat += 25;
                  }
                  else{
                    rezultat += 15;
                  }
                  sprintf(scoreText, "Score: %d", rezultat);
                  break;
              }
            }
          }
          for(k=0;k<CHICKEN_MAX;k++){
            if(chicken[k].alive){
              if(collisionChicken(chicken[k],bullets[i],chicken[k].scale)){
                /*sve ostale kokoske nose isti br bodova*/
                if(k!=STATUE){
                  bullets[i].alive = 0;
                  chicken[k].activeDeadChicken = 1;
                  chicken[k].alive = 0;
                  rezultat += 20;
                  sprintf(scoreText, "Score: %d", rezultat);
                }
                /*statua nam jedina donosi negativne poene, nije kokoska, statua je!*/
                else{
                  bullets[i].alive = 0;
                  rezultat -= 20;
                  sprintf(scoreText, "Score: %d", rezultat);
                }
                break;
              }
            }
          }
          /*nosi najvise, jer nam je daleko*/
          if(sunAlive){
            if(collisionSun(xSun,ySun,zSun,rSun,bullets[i])){
              bullets[i].alive = 0;
              sunAlive = 0;
              cloudAlive = 0;
              starAlive = 1;
              glClearColor(0.1,0.1,0.1,1);
              rezultat += 50;
              sprintf(scoreText, "Score: %d", rezultat);
              break;
            }
          }
      }
  }
}
