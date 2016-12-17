#include "scene.h"

void lightSetup(void)
{
  /*Pozicija svetla (u pitanju je direkcionalno svetlo)*/
  GLfloat light_position[] = {3,-5,3,0};
  /*Ambijentalna boja svetla*/
  GLfloat light_ambient[] = {0.5,0.5,0.5,1};
  /*Difuzna boja svetla*/
  GLfloat light_diffuse[] = {0.5,0.5,0.8,1};
  /*Spekularna boja svetla*/
  GLfloat light_specular[] = {0.5,0.5,0.5,1};

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glLightfv(GL_LIGHT0,GL_POSITION,light_position);
  glLightfv(GL_LIGHT0,GL_AMBIENT,light_ambient);
  glLightfv(GL_LIGHT0,GL_DIFFUSE,light_diffuse);
  glLightfv(GL_LIGHT0,GL_SPECULAR,light_specular);
}

void materialSetup(void)
{
  /* Koeficijenti spekularne refleksije materijala. */
  GLfloat specular_coeffs[] = { 0.5, 0.5, 0.5, 1 };

  /* Koeficijent glatkosti materijala. */
  GLfloat shininess = 15;

  glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
  glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}

/*Iscrtava se glavna scena*/
void ground(void)
{
  glDisable(GL_LIGHTING);
    /*GLfloat diffuse_coeffs[] = {0.11,0.11,0.11,1};
    GLfloat ambient_coeffs[] = {0.0,0.0,0.0,1};
    glMaterialfv(GL_FRONT,GL_AMBIENT,ambient_coeffs);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse_coeffs);*/

    /*GLfloat diffuse_coeffs[] = {0.9,0.9,0.9,1};
    GLfloat ambient_coeffs[] = {0.0,0.0,0.0,1};
    glMaterialfv(GL_FRONT,GL_AMBIENT,ambient_coeffs);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse_coeffs);*/
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
      glTranslatef(-6.0,0,-22.0);
      glScalef(0.5,0.5,56.0);
      glColor3f(0.5,0.5,0.5);
      glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
      /*desni ivicnjak*/
      glTranslatef(6.0,0,-22.0);
      glScalef(0.5,0.5,56.0);
      glColor3f(0.5,0.5,0.5);
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

 glEnable(GL_LIGHTING);
}

void drawCloud(void)
{
  glDisable(GL_LIGHTING);
  /*crtam sunce*/
  glColor3f(0.9,0.9,0);
  glPushMatrix();
    glTranslatef(58.0,22.5,-70.0);
    glutSolidSphere(5.0,60,30);
  glPopMatrix();

  /*TODO: trouglici oko sunca-zavrsiti
  glBegin(GL_POLYGON);
    glVertex3f(59.0,28.0,-70.0);
    glVertex3f(60.0,30.0,-70.0);
    glVertex3f(61.0,28.0,-70.0);
  glEnd();
  */

  glDepthMask(GL_FALSE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_TEXTURE_2D);

    if( 0 == texCloud)
     {
         printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
         exit(1);
     }

    glColor3f(1.0,1.0,1.0);
    glBindTexture(GL_TEXTURE_2D, texCloud);

    /*dva zajedno*/
    glPushMatrix();
    glTranslatef(-60.0,18.0,-70.0);
    glScalef(28.0,10.0,1.0);
    glBegin(GL_POLYGON);

      glTexCoord2f(0.0f, 0.0f);
      glVertex3f(0.0f, 0.0f,0.0f);

      glTexCoord2f(1.0f, 0.0f);
      glVertex3f(1.0f, 0.0f, 0.0f);

      glTexCoord2f(1.0f, 1.0f);
      glVertex3f(1.0f, 1.0f, 0.0f);

      glTexCoord2f(0.0f, 1.0f);
      glVertex3f(0.0f, 1.0f, 0.0f);

    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-90.0,26.0,-80.0);
    glScalef(50.0,17.0,1.0);
    glBegin(GL_POLYGON);

           glTexCoord2f(0.0f, 0.0f);
           glVertex3f(0.0f, 0.0f,0.0f);

           glTexCoord2f(1.0f, 0.0f);
           glVertex3f(1.0f, 0.0f, 0.0f);

           glTexCoord2f(1.0f, 1.0f);
           glVertex3f(1.0f, 1.0f, 0.0f);

           glTexCoord2f(0.0f, 1.0f);
           glVertex3f(0.0f, 1.0f, 0.0f);

     glEnd();
     glPopMatrix();


      /*mali*/
      glPushMatrix();
      glTranslatef(-80.0,12.0,-70.0);
      glScalef(5.0,3.0,1.0);
      glBegin(GL_POLYGON);

             glTexCoord2f(0.0f, 0.0f);
             glVertex3f(0.0f, 0.0f,0.0f);

             glTexCoord2f(1.0f, 0.0f);
             glVertex3f(1.0f, 0.0f, 0.0f);

             glTexCoord2f(1.0f, 1.0f);
             glVertex3f(1.0f, 1.0f, 0.0f);

             glTexCoord2f(0.0f, 1.0f);
             glVertex3f(0.0f, 1.0f, 0.0f);

       glEnd();
       glPopMatrix();

       /*sredina*/
       glPushMatrix();
       glTranslatef(-10.0,21.0,-65.0);
       glScalef(30.0,10.0,1.0);
       glBegin(GL_POLYGON);

              glTexCoord2f(0.0f, 0.0f);
              glVertex3f(0.0f, 0.0f,0.0f);

              glTexCoord2f(1.0f, 0.0f);
              glVertex3f(1.0f, 0.0f, 0.0f);

              glTexCoord2f(1.0f, 1.0f);
              glVertex3f(1.0f, 1.0f, 0.0f);

              glTexCoord2f(0.0f, 1.0f);
              glVertex3f(0.0f, 1.0f, 0.0f);

        glEnd();
        glPopMatrix();

       /*kod sunca*/
       glPushMatrix();
       glColor3f(1.0,1.0,1.0);
       glTranslatef(35.0,11.0,-60.0);
       glScalef(20.0,10.0,1.0);
       glBegin(GL_POLYGON);

              glTexCoord2f(0.0f, 0.0f);
              glVertex3f(0.0f, 0.0f,0.0f);

              glTexCoord2f(1.0f, 0.0f);
              glVertex3f(1.0f, 0.0f, 0.0f);

              glTexCoord2f(1.0f, 1.0f);
              glVertex3f(1.0f, 1.0f, 0.0f);

              glTexCoord2f(0.0f, 1.0f);
              glVertex3f(0.0f, 1.0f, 0.0f);

        glEnd();
        glPopMatrix();

  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_BLEND);
  glDepthMask(GL_TRUE);

  glEnable(GL_LIGHTING);

}

/*Crtaju se kokoske*/
void drawChicken(int index)
{
    float x,y,z;
    int i;

    glDepthMask(GL_FALSE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);

    GLfloat diffuse_coeffs[] = {0.2,0.2,0.2,1};
    GLfloat ambient_coeffs[] = {0.8,0.8,0.8,1};
    glMaterialfv(GL_FRONT,GL_AMBIENT,ambient_coeffs);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse_coeffs);
    for(i=0; i < CHICKEN_MAX; i++){
      if(chickens[i].alive){
        x=chickens[i].xCurr;
        y=chickens[i].yCurr;
        z=chickens[i].zCurr;
        glPushMatrix();

          if( 0 == chickens[i].tex)
           {
               printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
               exit(1);
           }

          glBindTexture(GL_TEXTURE_2D, chickens[i].tex);
          glTranslatef(x,y,z);
          glScalef(2.0,2.0,2.0);
          glBegin(GL_POLYGON);

                 glTexCoord2f(0.0f, 0.0f);
                 glVertex3f(0.0f, 0.0f,0.0f);

                 glTexCoord2f(1.0f, 0.0f);
                 glVertex3f(1.0f, 0.0f, 0.0f);

                 glTexCoord2f(1.0f, 1.0f);
                 glVertex3f(1.0f, 1.0f, 0.0f);

                 glTexCoord2f(0.0f, 1.0f);
                 glVertex3f(0.0f, 1.0f, 0.0f);

           glEnd();

        glPopMatrix();
      }
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_BLEND);
    glDepthMask(GL_TRUE);
}

/*crtamo pistolj*/
void drawGun(float angleLR,float angleTB)
{
  float x = 0.0, y = 0.5, z = 8.0;
  glPushMatrix();
    GLfloat diffuse_coeffs[] = {0.15,0.15,0.15,1};
    GLfloat ambient_coeffs[] = {0.1,0.1,0.1,1};
    glMaterialfv(GL_FRONT,GL_AMBIENT,ambient_coeffs);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse_coeffs);
    glColor3f(0.2,0.2,0.2);
    glTranslatef(x,y,z);
    glRotatef(angleLR,0,1,0);
    glRotatef(angleTB,1,0,0);
    glScalef(0.25,0.3,1.0);
    glutSolidCube(1);
  glPopMatrix();
}

void die(void){
  printf("Game Over!\n");
  exit(-1);
}

/*crtamo metke*/
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
          GLfloat diffuse_coeffs[] = {0.25,0.25,0.25,1};
          GLfloat ambient_coeffs[] = {0.1,0.1,0.1,1};
          glMaterialfv(GL_FRONT,GL_AMBIENT,ambient_coeffs);
          glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse_coeffs);
          glColor3f(0.5,0.5,0.5);
          glTranslatef(x,y,z);
          glutSolidSphere(bullets[i].bulletSize,20,10);
        glPopMatrix();
      }
    }
}

/*crtamo mrtvu kokosku*/
void dead(Chicken c)
{

  glDepthMask(GL_FALSE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_TEXTURE_2D);

  if(c.activeDeadChicken){
    glPushMatrix();

      if( 0 == c.texDead)
       {
           printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
           exit(1);
       }

      glBindTexture(GL_TEXTURE_2D, c.texDead);
      glTranslatef(c.xCurr,c.yCurr,c.zCurr);
      glBegin(GL_POLYGON);

             glTexCoord2f(0.0f, 0.0f);
             glVertex3f(0.0f, 0.0f,0.0f);

             glTexCoord2f(1.0f, 0.0f);
             glVertex3f(1.0f, 0.0f, 0.0f);

             glTexCoord2f(1.0f, 1.0f);
             glVertex3f(1.0f, 1.0f, 0.0f);

             glTexCoord2f(0.0f, 1.0f);
             glVertex3f(0.0f, 1.0f, 0.0f);

       glEnd();

    glPopMatrix();
  }
  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_BLEND);
  glDepthMask(GL_TRUE);
}

float max(float a, float b)
{
  return a > b ? a : b;
}
float min(float a, float b)
{
  return a < b ? a : b;
}
int collision(Chicken c,Bullet b)
{
  float x, y, z, d;

  /*1.0 je velicina mog aabbboxa oko kokoske*/
  x = max(c.xCurr-0.5, min(b.xPos, c.xCurr + 0.5));
  y = max(c.yCurr-0.5, min(b.yPos, c.yCurr + 0.5));
  z = max(c.zCurr-0.5, min(b.zPos, c.zCurr + 0.5));

  d = sqrt((x-b.xPos)*(x-b.xPos) + (y-b.yPos)*(y-b.yPos) + (z-b.zPos)*(z-b.zPos));

  if(d <= b.bulletSize)
      return 1;

  return 0;
}

void bulletChickenCollision(void)
{
  int i,j;
  for (i=0; i<BULLET_MAX; i++){
      if (bullets[i].alive){
          for (j=0; j<CHICKEN_MAX; j++){
            if(chickens[j].alive){
              if (collision(chickens[j],bullets[i])){
                  bullets[i].alive = 0;
                  chickens[j].activeDeadChicken = 1;
                  chickens[j].alive = 0;
                  break;
              }
            }
          }
      }
  }
}
