#include<GL/glut.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<math.h>

/*Timers*/
#define TIMER_ID 1
#define TIMER_INTERVAL 40
#define TIMER_ID_CHICKEN 2
#define TIMER_CHICKEN 0

/*Deklarisemo funkcije*/
static void onKeyboard(unsigned char key,int x,int y);
static void onReshape(int width, int height);
static void onDisplay(void);
static void onTimer(int value);
static void chickenTimer(int id);
static void presKey(int key, int x, int y);
static void releaseKey(int key, int x, int y);

static void moveMe(int i);

static void ground(void);
static void drawChicken(int index);
static void die(void);

void renderBitmapString(float x, float y, void *font,const char *string,float r,float g,float b);

/*Flag za odredjivanje da li je animacija u toku*/
static int animationOnGoing;
static int animationChicken;
/*Pozicija kamere*/
float x=0.0f,y=1.0f,z=10.0f,lx=0.0f;
int deltaMove = 0;

#define CHICKEN_MAX 20

typedef struct Chicken{
  /*Velicina kokoske*/
  float chickenSize;
  /*koordinate sfere*/
  float xCurr;
  float yCurr;
  float zCurr;
  float rotate;
  int alive;
}Chicken;

Chicken chickens[CHICKEN_MAX];

int index;
int chickenIndex = 0;
float timerCurrent;

int main(int argc,char *argv[]){

  /*Inicijalizacija GLUT-a*/
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

  /*Kreira se prozor*/
  glutInitWindowSize(500,500);
  glutInitWindowPosition(100,100);
  glutCreateWindow("Moorhuhn");

  /*Registruju se callback funkcije*/
  glutKeyboardFunc(onKeyboard);
  glutSpecialFunc(presKey);
  glutSpecialUpFunc(releaseKey);
  glutReshapeFunc(onReshape);
  glutDisplayFunc(onDisplay);

  animationOnGoing = 0;
  animationChicken = 1;

  /*koordinate sfere*/
  srand(time(NULL));
  for(index = 0;index<CHICKEN_MAX;index++){
    chickens[index].chickenSize = 0.7;
    chickens[index].xCurr = 2.0*(float)rand()/RAND_MAX-1.0;
    chickens[index].yCurr = 0.5*(float)rand()/RAND_MAX;
    chickens[index].zCurr = (float)rand()/(float)RAND_MAX-2.0;
    chickens[index].rotate = 30.0;
    chickens[index].alive = 0;
  }

  /*OpenGl inicijalizacija*/
  glClearColor(0.6,0.8,0.9,1);
  glEnable(GL_DEPTH_TEST);

  glutTimerFunc(TIMER_CHICKEN,chickenTimer,TIMER_ID_CHICKEN);

  /*Program ulazi u glavnu petlju*/
  glutMainLoop();

  return 0;
}

static void presKey(int key, int x, int y) {

    switch (key) {
        case GLUT_KEY_LEFT : deltaMove = -1;break;
        case GLUT_KEY_RIGHT : deltaMove = 1;break;
    }
}

void releaseKey(int key, int x, int y) {

    switch (key) {
        case GLUT_KEY_LEFT : if (deltaMove < 0)
                                 deltaMove = 0;
                             break;
        case GLUT_KEY_RIGHT : if (deltaMove > 0)
                                 deltaMove = 0;
                             break;
    }
}

static void onKeyboard(unsigned char key,int x,int y){
  switch(key){
    case 27:
      /*Zavrsava se igra*/
      exit(-1);
      break;
    case 'g':
    case 'G':
      /*Startujemo igru*/
      if(!animationOnGoing){
        animationOnGoing = 1;
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

static void onReshape(int width, int height){
  /*Podesava se view port*/
  glViewport(0,0,width,height);

  /*Podesava se projekciju*/
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60, width/(float)height,1,1000);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(x, y, z, 0, 0, 0, 0, 1, 0);
}

static void onDisplay(void){

  if (deltaMove)
      moveMe(deltaMove);

  /*Brise se prethodni sadrzaj prozora*/
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /*Iscrtava se postolje*/
  ground();
  int count;
  for(count=1;count<=chickenIndex;count++){
    drawChicken(count);
    if(chickens[count].zCurr > 6.0){
      animationOnGoing = 0;
      chickens[count].zCurr = 6.0;
      die();
    }
  }

  renderBitmapString(-5,5,GLUT_BITMAP_9_BY_15,"Score:0",1.0,1.0,1.0);

  /*Salje se nova slika na ekran*/
  glutSwapBuffers();
}

static void onTimer(int id)
{
    if(TIMER_ID!=id)
      return;

    int i;
    for(i=0;i<CHICKEN_MAX;i++){
        if(chickens[i].alive == 1){
          chickens[i].zCurr += 0.1;
        }
    }

    glutPostRedisplay();

    if (animationOnGoing) {
        glutTimerFunc(TIMER_INTERVAL, onTimer, TIMER_ID);
    }
}

void chickenTimer(int id){
    if(TIMER_ID_CHICKEN!=id)
      return;

    chickenIndex++;
    chickens[chickenIndex].alive = 1;
    glutPostRedisplay();

    if(animationChicken){
      glutTimerFunc(TIMER_CHICKEN+2500,chickenTimer,TIMER_ID_CHICKEN);
    }
}

/*Za pomeranje kamere*/
void moveMe(int i) {
    lx = lx + i*0.1;
    glLoadIdentity();
    gluLookAt(x, y, z,
              lx,0,0,
              0.0f,1.0f,0.0f);
}

/*Iscrtava se glavna scena*/
static void ground(){
  glPushMatrix();
    glColor3f(0,0.8,0.2);
    glBegin(GL_QUADS);
      glVertex3f(-6,-1,-6);
      glVertex3f(-6,-1,6);
      glVertex3f(6,-1,6);
      glVertex3f(6,-1,-6);
    glEnd();
  glPopMatrix();

}

/*Crtaju se kokoske*/
static void drawChicken(int index){
    glPushMatrix();
      glColor3f(1,0,0);
      glTranslatef(chickens[index].xCurr,chickens[index].yCurr,chickens[index].zCurr);
      glutSolidSphere(chickens[index].chickenSize,40,2);
    glPopMatrix();
}

void renderBitmapString(float x, float y, void *font,const char *string,float r,float g, float b){
  glColor3f(r,g,b);
  glRasterPos2f(x, y);
  glutBitmapString(font,string);
}

void die(){
  printf("Game Over!\n");
  exit(-1);
}
