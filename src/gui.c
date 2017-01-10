#include "gui.h"

void renderString(float x, float y, float z, void *font,const char *string,float r,float g,float b)
{
  glColor3f(r,g,b);
  glRasterPos3f(x, y, z);
  glutBitmapString((void*)font,(const unsigned char*)string);
}

void printText()
{
  renderString(-0.5,1.2,6.0,GLUT_BITMAP_TIMES_ROMAN_24,text,0,0,0);
}

void printScore()
{
  /*inicijalno ako nismo poceli igricu*/
  if(!scoreID){
    strcpy(scoreText,"Score: 0");
  }
  /*ako smo u igrici i nije nam isteklo vreme*/
  else{
    renderString(-10.0,5.5,-3.0,GLUT_BITMAP_HELVETICA_18,scoreText,1,0,0);
  }
}

void printTime()
{
  /*inicijalno ako nismo poceli igricu*/
  if(!timeID){
    strcpy(timeText,"01m:10s");
  }
  /*ako nam jos nije isreklo vreme*/
  else{
    renderString(10.0, 5.5, -3.0, GLUT_BITMAP_HELVETICA_18, timeText,1,0,0);
  }

  /*ako je vreme inicijalno, potavljamo ga na trenutno proteklo vreme*/
	if(oldTime == 0){
		oldTime = glutGet(GLUT_ELAPSED_TIME);
  }

  /*racunamo delta vreme*/
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	int deltaTime = currentTime - oldTime;
  /*ako je delta vece od prethodnog vremena, azuriramo trenutno vreme*/
	if (deltaTime >= prevTime + SECOND) {
    /*tako da oduzimam od vremena igrice, kako bi mi brojao u nazad*/
		int seconds = startTime - (deltaTime / SECOND);
    /*ako smo stigli do nule, zavrsavamo igricu*/
    if(seconds == -1){
      gameOverID = 1;
    }
    else{
	    sprintf(timeText, "%02dm:%02ds", seconds/60, seconds%60);
	    prevTime = deltaTime;
    }
  }
}

void gameOver()
{
  /*ispisujem rezultat ostvaren u igri, i dajemo mogucnost korisniku da bira sta hoce dalje*/
  sprintf(text,"Your score: %d\nPress G for New Game\nPress Esc for quit\n",rezultat);
  printText();

  /*vrsim ponovnu inicijalizaciju svih objekata*/
  initializeImages();
  initializeSunStar();
  initializeBulletsGun();

  /*slika kokoske gameover*/
  glColor3f(1.0,1.0,1.0);
  glPushMatrix();
    glTranslatef(0,0.0,7.2);
    glScalef(1.8,1.8,1.8);
    texture(GAME_OVER);
  glPopMatrix();

  /*pozadina ce biti plava, jer moze da bude i crna, a to ne zelim*/
  glClearColor(0.6,0.8,0.9,1);

  /*postavljam score i time na inicijalne vrednosti*/
  scoreID = 0;
  timeID = 0;
  printScore();
  printTime();

  /*prekidamo igricu*/
  animationOnGoing = 0;
  animationChicken = 0;
}
