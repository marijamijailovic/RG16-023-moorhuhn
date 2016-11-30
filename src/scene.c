#include "scene.h"

void lightSetup(void){
  /*Pozicija svetla (u pitanju je direkcionalno svetlo)*/
  GLfloat light_position[] = {1,1,1,0};
  /*Ambijentalna boja svetla*/
  GLfloat light_ambient[] = {0.8,0.5,0,1};
  /*Difuzna boja svetla*/
  GLfloat light_diffuse[] = {1,1,0,1};
  /*Spekularna boja svetla*/
  GLfloat light_specular[] = {0.5,0.5,0.5,1};

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);/*sta znace ovi brojevi od 0-7?*/
  glLightfv(GL_LIGHT0,GL_POSITION,light_position);
  glLightfv(GL_LIGHT0,GL_AMBIENT,light_ambient);
  glLightfv(GL_LIGHT0,GL_DIFFUSE,light_diffuse);
  glLightfv(GL_LIGHT0,GL_SPECULAR,light_specular);
}

void materialSetup(void){
  /* Koeficijenti spekularne refleksije materijala. */
  GLfloat specular_coeffs[] = { 0.5, 0.5, 0.5, 1 };

  /* Koeficijent glatkosti materijala. */
  GLfloat shininess = 15;

  glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
  glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}

/*Iscrtava se glavna scena*/
void ground(void){
  glPushMatrix();
    GLfloat diffuse_coeffs[] = {0,1,0,1};
    GLfloat ambient_coeffs[] = {0,0.8,0,1};
    glMaterialfv(GL_FRONT,GL_AMBIENT,ambient_coeffs);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse_coeffs);
    glBegin(GL_QUADS);
      glVertex3f(-6,-1,-6);
      glVertex3f(-6,-1,6);
      glVertex3f(6,-1,6);
      glVertex3f(6,-1,-6);
    glEnd();
  glPopMatrix();

}

/*Crtaju se kokoske*/
void drawChicken(int index){
    float x,y,z;
    int i;
    for(i=0; i < CHICKEN_MAX; i++){
      if(chickens[i].alive){
        x=chickens[i].xCurr;
        y=chickens[i].yCurr;
        z=chickens[i].zCurr;
        glPushMatrix();
          GLfloat diffuse_coeffs[] = {1,0,0,1};
          GLfloat ambient_coeffs[] = {0.8,0,0,1};
          glMaterialfv(GL_FRONT,GL_AMBIENT,ambient_coeffs);
          glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse_coeffs);
          glTranslatef(x,y,z);
          glutWireSphere(chickens[index].chickenSize,40,20);
        glPopMatrix();
      }
    }
}

/*crtamo top*/
void drawGun(float angle){
  float size = 0.2;
  float x = 4.0, y = 0.5, z = 9.0;
  glPushMatrix();
    GLfloat diffuse_coeffs[] = {0.0,0,0.0,1};
    GLfloat ambient_coeffs[] = {0.5,0.5,0.5,1};
    glMaterialfv(GL_FRONT,GL_AMBIENT,ambient_coeffs);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse_coeffs);
    glTranslatef(x,y,z);
    glRotatef(angle,0,1,0);
    glutSolidTeapot(size);
  glPopMatrix();
}

void die(void){
  printf("Game Over!\n");
  exit(-1);
}

/*crtamo metke*/
void drawBullets(float angle)
{
    float x, y, z;
    int i;
    for(i=0; i < BULLET_MAX; i++){
      if(bullets[i].active){
        x=bullets[i].xPos;
        y=bullets[i].yPos;
        z=bullets[i].zPos;
        glPushMatrix();
          GLfloat diffuse_coeffs[] = {0.2,0,0.6,1};
          GLfloat ambient_coeffs[] = {0.6,0,0.9,1};
          glMaterialfv(GL_FRONT,GL_AMBIENT,ambient_coeffs);
          glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse_coeffs);
          glTranslatef(x,y,z);
          glutSolidSphere(bullets[i].bulletSize,20,10);
        glPopMatrix();
      }
    }
}

int collision(Chicken c,Bullet b){
  float xC = c.xCurr,yC = c.yCurr,zC = c.zCurr;
  float xB = b.xPos,yB = b.yPos,zB = b.zPos;
  float rC = c.chickenSize;
  float rB = b.bulletSize;
  if (sqrt(pow((xC-xB),2)+pow((yC-yB),2)+pow((zC-zB),2)) <= (rC+rB)) {
    return 1;
  }
  return 0;
}

void bulletChickenCollision(void)
{
    int i,j;
    for (i=0; i<BULLET_MAX; i++){
        if (bullets[i].active){
            for (j=0; j<CHICKEN_MAX; j++){
              if(chickens[j].alive){
                if (collision(chickens[j],bullets[i])){
                    bullets[i].active = 0;
                    chickens[j].alive = 0;
                    break;
                }
              }
            }
        }
    }
}
