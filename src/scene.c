#include "scene.h"

/*Iscrtava se glavna scena*/
void ground(void)
{
  glPushMatrix();
    int i;
    glColor3f(0.94,0.94,0.94);
    for(i=-51;i<=6;i+=10){
      /*isprekidana linija*/
      glBegin(GL_POLYGON);
        glNormal3f(0,1,0);
        glVertex3f(-0.5,0.0001,(float)i+1);
        glVertex3f(0.5,0.0001,(float)i+1);
        glVertex3f(0.5,0.0001,(float)i+6);
        glVertex3f(-0.5,0.0001,(float)i+6);
      glEnd();
    }

    /*put*/
    glBegin(GL_QUADS);
      glNormal3f(0,1,0);
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
      glNormal3f(0,1,0);
      glColor3f(0.0,0.8,0.0);
      glVertex3f(-5.0,0.5,6.0);
      glVertex3f(-5.0,0.5,-22.1);
      glVertex3f(-55.0,0.5,-22.1);
      glVertex3f(-55.0,0.5,6.0);
    glEnd();

    /*zelena povrsina--desno*/
    glBegin(GL_QUADS);
      glNormal3f(0,1,0);
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
    /*baru crtamo tako da izgleda kao elipsa*/
    glBegin(GL_POLYGON);
      glColor3f(0.1,0.5,0.9);
      int i;
      for(i=0; i < 360; i++)
      {
        float degInRad = i*(DEG2RAD);
        float u = cos(degInRad)*40.0;
        float v = sin(degInRad)*55.0;
        float diff_u, diff_v;

        /* Racunamo priblizne vrednosti izvoda funkcije u tacki u, v */
        diff_u = (function(u + 1, v) - function(u - 1, v)) / 2.0;
        diff_v = (function(u, v + 1) - function(u, v - 1)) / 2.0;

        /* Postavljamo normalu - vektor normalan na tangentnu ravan */
        /* Racuna se priblizan vektor normale: */
        glNormal3f(sin(-diff_u), 1, sin(-diff_v));
        /*y ce nam se menjati po sin, tako da bara lici kao da ima talasice*/
        glVertex3f(u,function(u,v),v);
      }
      glEnd();
  glPopMatrix();
}

void drawSun(void)
{
  /*crtam sunce, ako ga jos nismo upucali*/
  if(sunAlive){
    glPushMatrix();
      glColor3f(1.0,1.0,0.0);
      glTranslatef(xSun,ySun,zSun);
      glutSolidSphere(rSun,60,30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(35.0,16.0,-45.0);
    int i,k;
    for (i=0,k=15; i < 360; i+=30,k+=30)
    {
      float degInRadI = i*DEG2RAD;
      float deginRadK = k*DEG2RAD;
      glBegin(GL_TRIANGLES);
       glVertex2f(cos(degInRadI)*(rSun+1.5),sin(degInRadI)*(rSun+1.5));
       glVertex2f(cos(degInRadI)*(rSun),sin(degInRadI)*(rSun));
       glVertex2f(cos(deginRadK)*(rSun+1.5),sin(deginRadK)*(rSun+1.5));
      glEnd();
    }

    glPopMatrix();
  }
}

void drawCloud(void)
{
  /*ako smo ubili sunce,vise necemo crtati oblake*/
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
      texture(CLOUD);
    glPopMatrix();

     /*sredina*/
    glPushMatrix();
      glTranslatef(-10.0,21.0,-65.0);
      glScalef(30.0,10.0,1.0);
      texture(CLOUD);
    glPopMatrix();

     /*kod sunca*/
    glPushMatrix();
      glTranslatef(24.0,10.0,-40.0);
      glScalef(10.0,5.0,1.0);
      texture(CLOUD);
    glPopMatrix();
  }
}

void drawStar()
{
  /*ako smo ubii sunce, crtamo zvezde*/
  if(starAlive){
    int i;
    glLineWidth(1.0);
    for(i=0;i<5;i++){
      glBegin(GL_LINE_STRIP);
        glColor3f(0.8,0.8,0.0);
        /*od temena na vrhu,pa ide u smeru kazaljke na satu*/
        glVertex3f(star[i].xCurr,star[i].yCurr,star[i].zCurr);
        glVertex3f(star[i].xCurr+0.3,star[i].yCurr-0.3,star[i].zCurr);
        glVertex3f(star[i].xCurr+0.8,star[i].yCurr-0.3,star[i].zCurr);
        glVertex3f(star[i].xCurr+0.3,star[i].yCurr-0.6,star[i].zCurr);
        glVertex3f(star[i].xCurr+0.6,star[i].yCurr-0.9,star[i].zCurr);
        glVertex3f(star[i].xCurr,star[i].yCurr-0.7,star[i].zCurr);
        glVertex3f(star[i].xCurr-0.6,star[i].yCurr-0.9,star[i].zCurr);
        glVertex3f(star[i].xCurr-0.3,star[i].yCurr-0.6,star[i].zCurr);
        glVertex3f(star[i].xCurr-0.8,star[i].yCurr-0.3,star[i].zCurr);
        glVertex3f(star[i].xCurr-0.3,star[i].yCurr-0.3,star[i].zCurr);
        glVertex3f(star[i].xCurr,star[i].yCurr,star[i].zCurr);
      glEnd();
    }
  }
}

void drawWood()
{
  glColor3f(1.0,1.0,1.0);
  glPushMatrix();
    glTranslatef(4.0,0.5,-10.0);
    glScalef(3.0,3.0,1.0);
    texture(WOOD);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(-6.5,0.5,-10.0);
    glScalef(3.0,3.0,1.0);
    texture(WOOD);
  glPopMatrix();
}

void drawHome()
{
  glColor3f(1.0,1.0,1.0);
  glPushMatrix();
    glTranslatef(-6.5,1.0,2.8);
    glScalef(2.5,1.5,1.0);
    texture(HOME);
  glPopMatrix();
}

void drawCar()
{
  glColor3f(1.0,1.0,1.0);
  glPushMatrix();
    glTranslatef(9.5,0.5,-4.0);
    glScalef(3.5,2.0,1.0);
    texture(CAR);
  glPopMatrix();
}

void drawPumpkin()
{
  glPushMatrix();
    glTranslatef(8.5,0.5,-8.0);
    glScalef(1.5,1.5,1.5);
    texture(PUMPKIN);
  glPopMatrix();
}

void drawGun(float angleLR,float angleTB)
{
  glPushMatrix();

    glLineWidth(5.0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glBegin(GL_LINES);
      glColor4f(0.8,0.0,0.0,0.2);
      glVertex3f(xGun,yGun,zGun);
      glVertex3f(xGun-angleLR/10,yGun+angleTB/10,zGun-5);
    glEnd();
    glDisable(GL_BLEND);
    glColor3f(0.2,0.2,0.2);
    glTranslatef(xGun,yGun,zGun);
    glRotatef(angleLR,0,1,0);
    glRotatef(angleTB,1,0,0);
    glScalef(0.3,0.3,1.0);
    glutSolidCube(1);
  glPopMatrix();
}

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
