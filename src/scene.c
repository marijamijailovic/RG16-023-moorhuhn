#include "scene.h"

/*Iscrtava se glavna scena*/
void ground(void)
{
  glPushMatrix();
    int i;
    glColor3f(0.94,0.94,0.94);
    for(i=-51;i<=6;i+=10){
      glBegin(GL_POLYGON);
        glVertex3f(-0.5,0.0001,(float)i+1);
        glVertex3f(0.5,0.0001,(float)i+1);
        glVertex3f(0.5,0.0001,(float)i+6);
        glVertex3f(-0.5,0.0001,(float)i+6);
      glEnd();
    }

    glBegin(GL_QUADS);
      glColor3f(0.24,0.24,0.24);
      glVertex3f(-6,0,-50);
      glVertex3f(-6,0,6);
      glVertex3f(6,0,6);
      glVertex3f(6,0,-50);
    glEnd();

    glPushMatrix();
      /*levi ivicnjak*/
      glColor3f(0.5,0.5,0.5);
      glTranslatef(-6.0,0,-22.0);
      glScalef(0.5,0.5,56.0);
      glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
      /*desni ivicnjak*/
      glColor3f(0.5,0.5,0.5);
      glTranslatef(6.0,0,-22.0);
      glScalef(0.5,0.5,56.0);
      glutSolidCube(1);
    glPopMatrix();

    /*zelena povrsina--levo*/
    glBegin(GL_QUADS);
      glColor3f(0.0,0.8,0.0);
      glVertex3f(-5.0,0.5,6.0);
      glVertex3f(-5.0,0.5,-22.1);
      glVertex3f(-55.0,0.5,-22.1);
      glVertex3f(-55.0,0.5,6.0);
    glEnd();

    /*zelena povrsina--desno*/
    glBegin(GL_QUADS);
      glColor3f(0.0,0.8,0.0);
      glVertex3f(5.0,0.5,6.0);
      glVertex3f(5.0,0.5,-22.1);
      glVertex3f(55.0,0.5,-22.1);
      glVertex3f(55.0,0.5,6.0);
    glEnd();
  glPopMatrix();
}

float function(float u, float v)
{
    return 0.5*sin((bara + u * v) / 150);
}

void drawPuddle(void)
{
  glPushMatrix();

    glTranslatef(-8.5,0.6,-8.3);
    glScalef(0.05,0.05,0.05);
    glBegin(GL_POLYGON);
    glColor3f(0.0,0.305,0.8);
    for(int i=0; i < 360; i++)
    {
      float degInRad = i*(DEG2RAD);
      float u = cos(degInRad)*40.0;
      float v = sin(degInRad)*55.0;
      glVertex3f(u,function(u,v),v);
    }
    glEnd();
  glPopMatrix();
}

void drawSun(void)
{
  /*crtam sunce*/
  if(sunAlive){
    glPushMatrix();
      glColor3f(0.9,0.9,0);
      glTranslatef(xSun,ySun,zSun);
      glutSolidSphere(rSun,60,30);
    glPopMatrix();
  }

  /*TODO: trouglici oko sunca-zavrsiti
  glBegin(GL_POLYGON);
    glVertex3f(59.0,28.0,-70.0);
    glVertex3f(60.0,30.0,-70.0);
    glVertex3f(61.0,28.0,-70.0);
  glEnd();
  */
}

void drawCloud(void)
{
  if(cloudAlive){
    glColor3f(1.0,1.0,1.0);
    /*dva zajedno*/
    glPushMatrix();
      glTranslatef(-60.0,18.0,-70.0);
      glScalef(28.0,10.0,1.0);
      texture(CLOUD);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(-90.0,26.0,-80.0);
      glScalef(50.0,17.0,1.0);
      texture(CLOUD);
    glPopMatrix();

    /*mali*/
    glPushMatrix();
      glTranslatef(-80.0,18.0,-70.0);
      glScalef(5.0,3.0,1.0);
      texture(10);
    glPopMatrix();

     /*sredina*/
    glPushMatrix();
      glTranslatef(-10.0,21.0,-65.0);
      glScalef(30.0,10.0,1.0);
      texture(10);
    glPopMatrix();

     /*kod sunca*/
    glPushMatrix();
      glTranslatef(24.0,10.0,-40.0);
      glScalef(10.0,5.0,1.0);
      texture(CLOUD);
    glPopMatrix();
  }
}

/*crtam zvezdu*/
void drawStar()
{
  if(starAlive){
    int i;
    for(i=0;i<5;i++){
      glBegin(GL_LINES);
        glColor3f(0.5,0.5,0.0);
        glVertex3f(star[i].xCurr,star[i].yCurr,star[i].zCurr);
        glVertex3f(star[i].xCurr+0.3,star[i].yCurr-0.3,star[i].zCurr);
        glVertex3f(star[i].xCurr+0.3,star[i].yCurr-0.3,star[i].zCurr);
        glVertex3f(star[i].xCurr+0.8,star[i].yCurr-0.3,star[i].zCurr);
        glVertex3f(star[i].xCurr+0.8,star[i].yCurr-0.3,star[i].zCurr);
        glVertex3f(star[i].xCurr+0.3,star[i].yCurr-0.6,star[i].zCurr);
        glVertex3f(star[i].xCurr+0.3,star[i].yCurr-0.6,star[i].zCurr);
        glVertex3f(star[i].xCurr+0.6,star[i].yCurr-0.9,star[i].zCurr);
        glVertex3f(star[i].xCurr+0.6,star[i].yCurr-0.9,star[i].zCurr);
        glVertex3f(star[i].xCurr,star[i].yCurr-0.7,star[i].zCurr);
        glVertex3f(star[i].xCurr,star[i].yCurr-0.7,star[i].zCurr);
        glVertex3f(star[i].xCurr-0.6,star[i].yCurr-0.9,star[i].zCurr);
        glVertex3f(star[i].xCurr-0.6,star[i].yCurr-0.9,star[i].zCurr);
        glVertex3f(star[i].xCurr-0.3,star[i].yCurr-0.6,star[i].zCurr);
        glVertex3f(star[i].xCurr-0.3,star[i].yCurr-0.6,star[i].zCurr);
        glVertex3f(star[i].xCurr-0.8,star[i].yCurr-0.3,star[i].zCurr);
        glVertex3f(star[i].xCurr-0.8,star[i].yCurr-0.3,star[i].zCurr);
        glVertex3f(star[i].xCurr-0.3,star[i].yCurr-0.3,star[i].zCurr);
        glVertex3f(star[i].xCurr-0.3,star[i].yCurr-0.3,star[i].zCurr);
        glVertex3f(star[i].xCurr,star[i].yCurr,star[i].zCurr);
      glEnd();
    }
  }
}

void drawDrvo()
{
  glColor3f(1.0,1.0,1.0);
  glPushMatrix();
    glTranslatef(4.0,0.5,-10.0);
    glScalef(3.0,3.0,1.0);
    texture(DRVO);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(-6.5,0.5,-10.0);
    glScalef(3.0,3.0,1.0);
    texture(DRVO);
  glPopMatrix();
}

/*crtam kucu*/
void drawKuca()
{
  glColor3f(1.0,1.0,1.0);
  glPushMatrix();
    glTranslatef(-6.5,1.0,2.8);
    glScalef(2.5,1.5,1.0);
    texture(KUCA);
  glPopMatrix();
}

/*crtam auto*/
void drawAuto()
{
  glColor3f(1.0,1.0,1.0);
  glPushMatrix();
    glTranslatef(8.0,0.5,-3.0);
    glScalef(3.5,2.0,1.0);
    texture(AUTO);
  glPopMatrix();
}

/*crtam bundevu*/
void drawBundeva()
{
  glPushMatrix();
    glTranslatef(8.5,0.5,-8.0);
    glScalef(1.5,1.5,1.5);
    texture(BUNDEVA);
  glPopMatrix();
}

/*crtam pistolj*/
void drawGun(float angleLR,float angleTB)
{
  float x = 0.0, y = 0.5, z = 8.0;
  glPushMatrix();
    glColor3f(0.2,0.2,0.2);
    glTranslatef(x,y,z);
    glRotatef(angleLR,0,1,0);
    glRotatef(angleTB,1,0,0);
    glScalef(0.3,0.3,1.0);
    glutSolidCube(1);
  glPopMatrix();
}

/*crtam metke*/
void drawBullets()
{
    float x, y, z;
    int i;
    for(i=0; i < BULLET_MAX; i++){
      if(bullets[i].alive){
        x=bullets[i].xPos;
        y=bullets[i].yPos;
        z=bullets[i].zPos;
        glPushMatrix();
          glColor3f(0.5,0.5,0.5);
          glTranslatef(x,y,z);
          glutSolidSphere(bullets[i].bulletSize,20,10);
        glPopMatrix();
      }
    }
}
