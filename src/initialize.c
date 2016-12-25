#include "initialize.h"

void initialize(void)
{
  chickenIndex = 0;
  angleLR = 0;
  angleTB = 0;

  char *images[] = {
                   "images/istrazivac.png",
                   "images/novinar.png",
                   "images/ninja.png",
                   "images/pecaros.png",
                   "images/student.png",
                   "images/kokastatua.png",
                   "images/leteca.png",
                   "images/dead.png",
                   "images/kart.png",
                   "images/bundeva.png",
                   "images/cloud.png",
                   "images/drvo.png",
                   "images/kuca.png",
                   "images/auto.png"
                 };

  int i;
  for(i=0;i<IMAGES_MAX;i++){
    tex[i] = SOIL_load_OGL_texture
         (
             images[i],
             SOIL_LOAD_AUTO,
             SOIL_CREATE_NEW_ID,
             SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
         );
  }

  float koordinateKokosaka[][3] = {
                                {6.5,0.45,0.0}, /*istrazivac*/
                                {-7.0,0.55,-0.5}, /*novinar*/
                                {-15.0,0.4,-1.5}, /*ninja*/
                                {-7.2,0.2,-8.5}, /*pecaros*/
                                {-9.5,0.5,-0.5}, /*student*/
                                {8.5,1.8,-8.0}, /*koka statua*/
                                {0.0,5.5,-45.0} /*leteca*/
                           };

  srand(time(NULL));

  /*inicijalizacija kokoski*/
  {
       int index;
       for(index = 0;index < CHICKEN_KART_MAX;index++){
         chickensKart[index].xCurr = (float)getRand(-4.5,4.5);
         chickensKart[index].yCurr = 0.3*((float)rand()/RAND_MAX);
         chickensKart[index].zCurr = (float)getRand(-30,0);
         chickensKart[index].alive = 0;
         chickensKart[index].activeDeadChicken = 0;
         chickensKart[index].scale = 2.0;
       }
      int i;
      for(i=0;i<7;i++){
        chicken[i].xCurr = koordinateKokosaka[i][0];
        chicken[i].yCurr = koordinateKokosaka[i][1];
        chicken[i].zCurr = koordinateKokosaka[i][2];
        chicken[i].alive = 1;
        chicken[i].activeDeadChicken = 0;
        chicken[i].animationAction = 1;
        if(i == PECAROS){
          chicken[i].scale = 2.0;
        }
        else if(i == KOKASTATUA){
          chicken[i].scale = 1.5;
        }
        else{
          chicken[i].scale = 1.0;
        }
      }
  }

  /*inicijalizacija sunca*/
  {
    xSun = 35.0, ySun = 16.0, zSun = -45.0, rSun = 2.5;
    sunAlive = 1;
  }

  cloudAlive = 1;
  starAlive = 0;
  /*inicijalizacija zvezdica*/
  {
    int i;
    for(i=0;i<5;i++){
      star[i].xCurr = (float)getRand(-35,35);
      star[i].yCurr = (float)getRand(10,15);
      star[i].zCurr = (float)getRand(-35,-45);
    }
  }

  /*inicijalizacija metaka*/
  {
    int index;
    for(index = 0;index < BULLET_MAX; index++){
      bullets[index].bulletSize = 0.08;
      bullets[index].alive = 0;
    }
  }

  /*OpenGl inicijalizacija*/
  glClearColor(0.6,0.8,0.9,1);
}

int getRand(int min,int max)
{
	  return(rand()%(max-min)+min);
}

void texture(int texId)
{
  glDepthMask(GL_FALSE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_TEXTURE_2D);

  int i;
  for(i=0;i<IMAGES_MAX;i++){
    if(i == texId){
      if( 0 == tex[texId])
       {
           printf( "SOIL %d loading error: '%s'\n",texId, SOIL_last_result() );
           exit(1);
       }

      glBindTexture(GL_TEXTURE_2D, tex[texId]);

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
     }
   }

   glBindTexture(GL_TEXTURE_2D, 0);
   glDisable(GL_BLEND);
   glDepthMask(GL_TRUE);
}

void lightSetup(void)
{
  /*Pozicija svetla (u pitanju je direkcionalno svetlo)*/
  GLfloat light_position[] = {0,1,3,0};
  /*Ambijentalna boja svetla*/
  GLfloat light_ambient[] = {0.5,0.5,0.5,1};
  /*Difuzna boja svetla*/
  GLfloat light_diffuse[] = {0.5,0.5,0.5,1};
  /*Spekularna boja svetla*/
  GLfloat light_specular[] = {0.5,0.5,0.5,1};

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glLightfv(GL_LIGHT0,GL_POSITION,light_position);
  glLightfv(GL_LIGHT0,GL_AMBIENT,light_ambient);
  glLightfv(GL_LIGHT0,GL_DIFFUSE,light_diffuse);
  glLightfv(GL_LIGHT0,GL_SPECULAR,light_specular);
}

/*void renderBitmapString(float x, float y, void *font,const char *string,float r,float g, float b)
{
  glColor3f(r,g,b);
  glRasterPos2f(x, y);
  glutBitmapString(font,string);
}*/
