#include "object.h"

/*crtam kokoske u autu*/
void drawChickenKart(int index)
{
  float x,y,z,scale;
  int i;
  /*postavljam glColor3f, da bi mi ocuvao boju kokoske dok je ziva,inace
  bi mi pri prvom ubijanju neke od kokse,sve ostale postavljaju alfa na 0*/
  glColor3f(1.0,1.0,1.0);
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

/*crtam sve ostale kokoske na sceni*/
void drawChicken(int id)
{
  if(chicken[id].alive){
    /*postavljam glColor3f, da bi mi ocuvao boju kokoske dok je ziva,inace
    bi mi pri prvom ubijanju neke od kokse,sve ostale postavljaju alfa na 0.0*/
    glColor3f(1.0,1.0,1.0);
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
  glColor4f(1.0,1.0,1.0,c.alpha);
  glPushMatrix();
    glTranslatef(c.xCurr,c.yCurr,c.zCurr);
    texture(DEAD);
  glPopMatrix();
}
