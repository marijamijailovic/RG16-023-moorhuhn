#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "scene.h"
#include "callback.h"

int main(int argc,char *argv[]){

  /*Inicijalizacija GLUT-a*/
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

  /*Kreira se prozor*/
  glutInitWindowSize(1000,700);
  glutInitWindowPosition(100,100);
  glutCreateWindow("Moorhuhn");

  /*Registruju se callback funkcije*/
  glutKeyboardFunc(onKeyboard);
  glutReshapeFunc(onReshape);
  glutDisplayFunc(onDisplay);

  animationOnGoing = 0;
  animationChicken = 1;

  /*inicijalizacija kokoski*/
  {
    srand(time(NULL));
    int index;
    for(index = 0;index < CHICKEN_MAX;index++){
      chickens[index].chickenSize = 0.5;
      chickens[index].xCurr = 4.0*((float)rand()/RAND_MAX);
      chickens[index].yCurr = 0.3*((float)rand()/RAND_MAX);
      chickens[index].zCurr = (float)rand()/(float)RAND_MAX;
      chickens[index].rotate = 30.0;
      chickens[index].alive = 0;
    }
  }

  /*inicijalizacija metaka*/
  {
    int index;
    for(index = 0;index < BULLET_MAX; index++){
      bullets[index].bulletSize = 0.05;
      bullets[index].xPos = 4.0;
      bullets[index].yPos = 0.5;
      bullets[index].zPos = 9.0;
      bullets[index].active = 0;
    }
  }

  /*OpenGl inicijalizacija*/
  glClearColor(0.6,0.8,0.9,1);
  glEnable(GL_DEPTH_TEST);

  glutTimerFunc(TIMER_CHICKEN,chickenTimer,TIMER_ID_CHICKEN);

  /*Program ulazi u glavnu petlju*/
  glutMainLoop();

  return 0;
}

static void onKeyboard(unsigned char key,int x,int y){
  switch(key){
    case 27:
      /*Zavrsava se igra*/
      exit(-1);
      break;
    /*ugao za koji pomeramo top*/
    case 'a':
      angle -= 3.0f;
      glutPostRedisplay();
      break;
    case 'd':
      angle += 3.0f;
      glutPostRedisplay();
      break;
    /*ispaljujemo metke*/
    case 'f':
    case 'F':
    /* Trazimo prvi slobodan slot u kome mozemo da zapamtimo
     * novi metak */
      {
        int i,run = 1;
        for (i=0;run && (i<BULLET_MAX);i++){
          if(!bullets[i].active){
            bullets[i].active = 1;
            bullets[i].xPos = 4.0;
            bullets[i].yPos = 0.5;
            bullets[i].zPos = 9.0;
            run = 0;
          }
        }
      }
      break;
    case 'g':
    case 'G':
      /*Startujemo igru*/
      if(!animationOnGoing){
        animationOnGoing = 1;
        glutTimerFunc(TIMER_INTERVAL,onTimer,TIMER_ID);
      }
      break;
    case 's':
    case 'S':
      /*Pauza */
      animationOnGoing = 0;
      break;
  }
}

void onTimer(int id)
{
    if(TIMER_ID == id){
      int i,j;
      for(i=0;i<CHICKEN_MAX;i++){
          if(chickens[i].alive){
            chickens[i].zCurr += 0.1;
            if(chickens[i].zCurr >= 10.0){
              chickens[i].alive = 0;
            }
          }
      }
      for(j=0;j<BULLET_MAX;j++){
          if(bullets[j].active){
            bullets[j].zPos -= 0.1;
            /*bullets[j].yPos += 0.005;*/
            bullets[j].xPos += angle/1000;
            if(bullets[j].zPos <= 7.0){
              bullets[j].active = 0;
            }
          }
      }

      /*TODO napravi eksploziju,i popraviti kretanje metkica,i samu koliziju*/
      bulletChickenCollision();

      glutPostRedisplay();

      if (animationOnGoing) {
          glutTimerFunc(TIMER_INTERVAL, onTimer, TIMER_ID);
      }
    }
}

void chickenTimer(int id){
    if(TIMER_ID_CHICKEN == id){

      chickenIndex++;
      chickens[chickenIndex].alive = 1;

      glutPostRedisplay();

      if(animationChicken){
        glutTimerFunc(TIMER_CHICKEN+2500,chickenTimer,TIMER_ID_CHICKEN);
      }
    }
}

static void onReshape(int width, int height){
  /*Podesava se viewport*/
  glViewport(0,0,width,height);

  /*Podesava se projekcija*/
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60, width/(float)height,1,1000);

}

static void onDisplay(void){

  /*Brise se prethodni sadrzaj prozora*/
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /*Podesavase vidna tacka*/
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(x, y, z, 0, 0, 0, 0, 1, 0);

  lightSetup();
  materialSetup();

  /*Iscrtava se postolje*/
  ground();

  int count;
  for(count=1;count<=chickenIndex;count++){
    drawChicken(count);
    /*if(chickens[count].zCurr > 6.0){
      animationOnGoing = 0;
      chickens[count].zCurr = 6.0;
      chickens[count].alive = 0;
      die();
    }*/
  }

  /*TODO dodati jos objekata za ubijanje*/

  drawGun(angle);
  drawBullets(angle);

  /*TODO postaviti score*/
  renderBitmapString(-5,5,GLUT_BITMAP_9_BY_15,"Score:0",1.0,1.0,1.0);

  /*Salje se nova slika na ekran*/
  glutSwapBuffers();
}

void renderBitmapString(float x, float y, void *font,const char *string,float r,float g, float b){
  glColor3f(r,g,b);
  glRasterPos2f(x, y);
  glutBitmapString(font,string);
}
