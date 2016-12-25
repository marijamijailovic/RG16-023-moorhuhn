#include "object.h"

/*crtam kokoske u autu*/
void drawChickenKart(int index)
{
  float x,y,z,scale;
  int i;
  for(i=0; i < CHICKEN_KART_MAX; i++){
    if(chickensKart[i].alive){
      x = chickensKart[i].xCurr;
      y = chickensKart[i].yCurr;
      z = chickensKart[i].zCurr;
      scale = chickensKart[i].scale;
      glPushMatrix();
        glTranslatef(x,y,z);
        glScalef(scale,scale,scale);
        texture(KART);
      glPopMatrix();
    }
  }
}

void drawChicken(int id)
{
  if(chicken[id].alive){
    float x = chicken[id].xCurr;
    float y = chicken[id].yCurr;
    float z = chicken[id].zCurr;
    float scale = chicken[id].scale;
    glPushMatrix();
      glTranslatef(x,y,z);
      glScalef(scale,scale,scale);
      if(id == ISTRAZIVAC){
        glRotatef(angleRotation,0,1.0,0);
      }
      texture(id);
    glPopMatrix();
  }
}

/*crtam mrtvu kokosku*/
void dead(Object c)
{
  if(c.activeDeadChicken){
    glPushMatrix();
      glTranslatef(c.xCurr,c.yCurr,c.zCurr);
      texture(DEAD);
    glPopMatrix();
  }
}
