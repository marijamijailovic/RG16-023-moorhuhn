#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "scene.h"
#include "callback.h"

int main(int argc,char *argv[])
{

  /*Inicijalizacija GLUT-a*/
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

  /*Kreira se prozor*/
  glutInitWindowSize(700,700);
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
      chickens[index].xCurr = (float)getRand(-5,5);
      chickens[index].yCurr = 0.3*((float)rand()/RAND_MAX);
      chickens[index].zCurr = (float)getRand(-30,0);
      chickens[index].alive = 0;
      chickens[index].activeDeadChicken = 0;
      chickens[index].tex  = SOIL_load_OGL_texture
         (
             "kart1.dds",
             SOIL_LOAD_AUTO,
             SOIL_CREATE_NEW_ID,
             SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
         );
		 	chickens[index].texDead = SOIL_load_OGL_texture
         (
             "Dead.png",
             SOIL_LOAD_AUTO,
             SOIL_CREATE_NEW_ID,
             SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
         );
    }

  }

  /*inicijalizacija metaka*/
  {
    int index;
    for(index = 0;index < BULLET_MAX; index++){
      bullets[index].bulletSize = 0.08;
			bullets[index].alive = 0;
			bullets[index].xPos = 0.0;
			bullets[index].yPos = 0.5;
			bullets[index].zPos = 8.0;
    }
  }

	/*inicijalizacija oblaka*/
	{
		 texCloud = SOIL_load_OGL_texture
				(
						"cloud3.png",
						SOIL_LOAD_AUTO,
						SOIL_CREATE_NEW_ID,
						SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				);
		}

  /*OpenGl inicijalizacija*/
  glClearColor(0.6,0.8,0.9,1);
  /* Ukljucuje se testiranje z-koordinate piksela. */
  glEnable(GL_DEPTH_TEST);

  /*Program ulazi u glavnu petlju*/
  glutMainLoop();

  return 0;
}

static void onKeyboard(unsigned char key,int x,int y)
{
  switch(key){
    case 27:
      /*Zavrsava se igra*/
      exit(-1);
      break;
    /*ugao za koji pomeramo top*/
    case 'a':
    case 'A':
      angleLR += 1.5f;
      break;
    case 'd':
    case 'D':
      angleLR -= 1.5f;
      break;
    case 's':
    case 'S':
      angleTB -= 0.5f;
      break;
    case 'w':
    case 'W':
      angleTB += 0.5f;
      break;
    /*ispaljujemo metke*/
    case 32:
    /* Trazimo prvi slobodan slot u kome mozemo da zapamtimo
     * novi metak */
      {
        int i,run = 1;
        for (i=0;run && (i<BULLET_MAX);i++){
          if(!bullets[i].alive){
						bullets[i].alive = 1;
						bullets[i].xPos = 0.0;
						bullets[i].yPos = 0.5;
						bullets[i].zPos = 8.0;
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
        glutTimerFunc(TIMER_CHICKEN,chickenTimer,TIMER_ID_CHICKEN);
        glutTimerFunc(TIMER_INTERVAL,onTimer,TIMER_ID);
      }
      break;
    case 'p':
    case 'P':
      /*Pauza */
      animationOnGoing = 0;
      break;
  }
}

void onTimer(int id)
{
    if(TIMER_ID == id){
      int index,i;
			/*pomeramo kokoske*/
      for(index=0;index<CHICKEN_MAX;index++){
          if(chickens[index].alive){
              chickens[index].zCurr += 0.1;
            if(chickens[index].zCurr >= 10.0){
              chickens[index].alive = 0;
            }
          }
      }

			/*pomeramo metke*/
      for(i=0;i<BULLET_MAX;i++){
				if(bullets[i].alive){
						bullets[i].xPos -= angleLR/1000;
						bullets[i].yPos += angleTB/1000;
						bullets[i].zPos -= 0.1;
          if(bullets[i].zPos <= -20.0){
              bullets[i].alive = 0;
          }
				}
      }

			/*proveravamo da li je metak pogodio kokosku*/
      bulletChickenCollision();
    }

      glutPostRedisplay();

      if (animationOnGoing) {
          glutTimerFunc(TIMER_INTERVAL, onTimer, TIMER_ID);
      }
}

void chickenTimer(int id)
{
    if(TIMER_ID_CHICKEN == id){

      chickenIndex++;
      chickens[chickenIndex].alive = 1;

      glutPostRedisplay();

      if(animationChicken){
        glutTimerFunc(TIMER_CHICKEN+2500,chickenTimer,TIMER_ID_CHICKEN);
      }
    }
}

static void onReshape(int width, int height)
{
  /*Podesava se viewport*/
  glViewport(0,0,width,height);

  /*Podesava se projekcija*/
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60, width/(float)height,1,1000);
}

static void onDisplay(void)
{

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

	/*funkcija koja crta oblake*/
	drawCloud();

  int count;
  for(count=1;count<=chickenIndex;count++){
		/*crtaju se kokoske*/
    drawChicken(count);
    if(chickens[count].alive == 0){
			/*crta se mrtva koka*/
      dead(chickens[count]);
    }
    /*if(chickens[count].zCurr > 9.0){
      animationOnGoing = 0;
      chickens[count].zCurr = 8.0;
      chickens[count].alive = 0;
      die();
    }*/
  }

  /*TODO dodati jos objekata za ubijanje*/

  drawGun(angleLR,angleTB);
  drawBullets();

  /*TODO postaviti score*/
  renderBitmapString(-5,5,GLUT_BITMAP_9_BY_15,"Score:0",1.0,1.0,1.0);

  /*Salje se nova slika na ekran*/
  glutSwapBuffers();
}

int getRand(int min,int max)
{
	  return(rand()%(max-min)+min);
}

void renderBitmapString(float x, float y, void *font,const char *string,float r,float g, float b)
{
  glColor3f(r,g,b);
  glRasterPos2f(x, y);
  glutBitmapString(font,string);
}
