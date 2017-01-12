#include <GL/glut.h>
#include <stdio.h>
#include "callback.h"
#include "initialize.h"

int main(int argc,char *argv[])
{
  /*Inicijalizacija GLUT-a*/
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

  /*Kreira se prozor*/
  /*glutInitWindowSize(700,700);
  glutInitWindowPosition(100,100);*/
  glutCreateWindow("Moorhuhn");

  /*odmah ga otvara u full screen-u*/
  glutFullScreen();

  /*Registruju se callback funkcije*/
  glutKeyboardFunc(onKeyboard);
  glutReshapeFunc(onReshape);
  glutDisplayFunc(onDisplay);

  /*za inicijalizaciju slicica*/
  initializeImages();
  /*za inicijalizaciju sunca i zvezdi*/
  initializeSunStar();
  /*inicijalizacija metaka i pistolja*/
  initializeBulletsGun();

  /*inicijalizacija svetla*/
  initializeLight();
  /*Ukljucujemo koriscenje glColor definisanih boja za materijale */
  glEnable(GL_COLOR_MATERIAL);

  /*Inicijalni tekst */
  strcpy(text,"Press G for New Game\nPress Esc for quit\n");

  /*oznacava da inicijalno treba da pise pocetni score:0 i time:1m:10s*/
  scoreID = 0;
  timeID = 0;

  /*br sekundi koliko traje partija*/
  startTime = 70;

  animationOnGoing = 0;
  animationChicken = 0;

  /*Ukljucuje se testiranje z-koordinate piksela. */
  glEnable(GL_DEPTH_TEST);

  /*OpenGl inicijalizacija*/
  glClearColor(0.6,0.8,0.9,1);

  /*Program ulazi u glavnu petlju*/
  glutMainLoop();

  return 0;
}
