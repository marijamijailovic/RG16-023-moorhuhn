#include "initialize.h"

void initializeImages(void)
{
  char *images[] = {
                   "images/explorer.png",
                   "images/journalist.png",
                   "images/ninja.png",
                   "images/fisher.png",
                   "images/student.png",
                   "images/statue.png",
                   "images/fly.png",
                   "images/driver.png",
                   "images/dead.png",
                   "images/kart.png",
                   "images/pumpkin.png",
                   "images/cloud.png",
                   "images/wood.png",
                   "images/home.png",
                   "images/car.png",
                   "images/gameover.png"
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
}
void initializeChicken(void)
{
  chickenIndex = 0;

  float koordinateKokosaka[CHICKEN_MAX][3] = {
                                {6.5,0.45,0.0}, /*istrazivac*/
                                {-7.0,0.55,-0.5}, /*novinar*/
                                {-15.0,0.4,-1.5}, /*ninja*/
                                {-7.0,0.5,-8.5}, /*pecaros*/
                                {-9.5,0.5,-0.5}, /*student*/
                                {8.5,1.8,-8.0}, /*koka statua*/
                                {0.0,5.5,-45.0}, /*leteca*/
                                {11.5,1.5,-4.5} /*vozac*/
                           };

  srand(time(NULL));

  /*inicijalizacija kokoski*/
  {
       int index;
       for(index = 0;index < CHICKEN_KART_MAX;index++){
         chickensKart[index].xCurr = (float)getRand(-4.5,4.5);
         chickensKart[index].yCurr = 0.3*((float)rand()/RAND_MAX);
         chickensKart[index].zCurr = (float)getRand(-45,-10);
         chickensKart[index].alive = 0;
         chickensKart[index].activeDeadChicken = 0;
         chickensKart[index].scale = 2.0;
         chickensKart[index].alpha = 1.0;
        }

      int i;
      for(i=0;i<CHICKEN_MAX;i++){
        chicken[i].xCurr = koordinateKokosaka[i][0];
        chicken[i].yCurr = koordinateKokosaka[i][1];
        chicken[i].zCurr = koordinateKokosaka[i][2];
        chicken[i].alive = 1;
        chicken[i].activeDeadChicken = 0;
        chicken[i].alpha = 1.0;
        chicken[i].animationAction = 1;
        if(i == FISHER){
          chicken[i].scale = 1.5;
        }
        else if(i == STATUE){
          chicken[i].scale = 1.5;
        }
        else if(i == DRIVER){
          chicken[i].scale = 0.8;
        }
        else{
          chicken[i].scale = 1.0;
        }
      }
  }
}
void initializeSunStar(void)
{
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
}

void initializeBulletsGun(void)
{
  /*za ugao rotacije pistolja*/
  angleLR = 0;
  angleTB = 0;

  /*inicijalizacija metaka*/
  {
    int i;
    for(i = 0;i < BULLET_MAX; i++){
      bullets[i].bulletSize = 0.08;
      bullets[i].alive = 0;
    }
  }

  /*inicijalizacija pistolja*/
  {
    xGun = 0.0, yGun = 0.5, zGun = 8.0;
  }
}
/*generise random broj iz zadatog intervala*/
int getRand(int min,int max)
{
	  return(rand()%(max-min)+min);
}

/*postavljanje tekstura na scenu, koristeci SOIL biblioteku*/
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

void initializeLight(void)
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
