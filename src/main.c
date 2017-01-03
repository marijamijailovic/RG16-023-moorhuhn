#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "callback.h"
#include "initialize.h"
#include "scene.h"
#include "object.h"
#include "collision.h"
#include "gui.h"

int main(int argc,char *argv[])
{
  /*Inicijalizacija GLUT-a*/
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

  /*Kreira se prozor*/
  /*glutInitWindowSize(700,700);
  glutInitWindowPosition(100,100);*/
  glutCreateWindow("Moorhuhn");
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

  /*Inicijalni tekst */
  strcpy(text,"Press G for New Game\nPress Esc for quit\n");

  /*oznacava da inicijalno treba da pise pocetni score:0 i time:1m:10s*/
  scoreID = 0;
  timeID = 0;

  /*br sekundi koliko traje partija*/
  startTime = 70;

  /*oznacava da li je igrica u toku*/
  gameOverID = 0;

  animationOnGoing = 0;
  animationChicken = 1;

  /*Ukljucuje se testiranje z-koordinate piksela. */
  glEnable(GL_DEPTH_TEST);

  /*OpenGl inicijalizacija*/
  glClearColor(0.6,0.8,0.9,1);

  /*Program ulazi u glavnu petlju*/
  glutMainLoop();

  return 0;
}

void onKeyboard(unsigned char key,int x,int y)
{
  switch(key){
    case 27:
      /*Zavrsava se igra*/
      exit(EXIT_FAILURE);
      break;
    /*ugao za koji pomeramo top*/
    case 'a':
    case 'A':
      angleLR += 1.2f; /*rotiramo pistolj levo*/
      break;
    case 'd':
    case 'D':
      angleLR -= 1.2f; /*rotiramo pistolj desno*/
      break;
    case 's':
    case 'S':
      angleTB -= 0.5f; /*rotiramo pistolj dole*/
      break;
    case 'w':
    case 'W':
      angleTB += 0.5f; /*rotiramo pistolj gore*/
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
            bullets[i].yPos = 0.55;
            bullets[i].zPos = 8.0;
            /*brzina metka po x,y,z koordinati*/
						bullets[i].xSpeed = angleLR/110;
						bullets[i].ySpeed = angleTB/110;
            bullets[i].zSpeed = 0.4;
            run = 0;
          }
        }
      }
      break;
    case 'g':
    case 'G':
      /*Startujemo igru*/
      if(!animationOnGoing){
        strcpy(text,"");/*brisemo inicijalni tekst*/
        /*postavljam parametre za vreme i rezultat*/
        oldTime = 0;
        prevTime = 0;
        rezultat = 0;
        /*ovde inizijalizujemo kokoske, jer ne zelim da se vidi
        gde su one inicijalno postavljene, pre nego sto igrica pocne*/
        initializeChicken();
        /*indikator za novu igru*/
        gameOverID = 0;
        /*aktiviramo score*/
        scoreID = 1;
        timeID = 1;
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
    if(TIMER_ID != id){
      return;
    }
    int index,i,j;
		/*pomeramo kokoske u kolima*/
    for(index=0;index<CHICKEN_KART_MAX;index++){
        if(chickensKart[index].alive){
            chickensKart[index].zCurr += 0.1;
          /*ako nam je kokoska pobegla, i nismo je ubili, izgubili smo igricu*/
          if(chickensKart[index].zCurr >= 6.5){
            chickensKart[index].alive = 0;
            gameOverID = 1;
          }
        }
        /*mrtva kokoska gubi svoju alfa vrednost, i tako nestaje polako sa scene*/
        if(!chickensKart[index].alive && chickensKart[index].activeDeadChicken){
          chickensKart[index].alpha -= 0.05;
          if(chickensKart[index].alpha < 0.0){
            chickensKart[index].alpha = 0.0;
          }
        }
    }

		/*pomeramo metke*/
    for(i=0;i<BULLET_MAX;i++){
			if(bullets[i].alive){
					bullets[i].xPos -= bullets[i].xSpeed;
					bullets[i].yPos += bullets[i].ySpeed;
					bullets[i].zPos -= bullets[i].zSpeed;
        /*ako nismo nista pogodili, a metak je dovoljno daleko, ne crta se vise*/
        if(bullets[i].zPos <= -50.0){
            bullets[i].alive = 0;
        }
			}
    }

    for(j = 0;j < 7; j++){
      /*rotiramo istrazivaca malo levo desno*/
      if(j == ISTRAZIVAC && chicken[ISTRAZIVAC].alive){
        if(chicken[ISTRAZIVAC].animationAction){
          angleRotation--;
          if(angleRotation < -75){
            chicken[ISTRAZIVAC].animationAction = 0;
          }
        }
        if(!chicken[ISTRAZIVAC].animationAction){
          angleRotation++;
          if(angleRotation > 0){
            chicken[ISTRAZIVAC].animationAction = 1;
          }
        }
      }
      /*preletanje ninje preko ulice - u vidu parabole*/
      if(j == NINJA && chicken[NINJA].alive){
        float vector = 0.07;
        chicken[NINJA].xCurr += vector;
        chicken[NINJA].yCurr = -1.0/100.0*(chicken[NINJA].xCurr*chicken[NINJA].xCurr)+2.0;
        /*sve  dok ne ubijemo ninju on prelece*/
        if(chicken[NINJA].xCurr >= 12.0){
          chicken[NINJA].xCurr = -17.5;
          chicken[NINJA].yCurr = 0.4;
        }
      }
      /*pomeramo letecu kokosku*/
      if(j == LETECA && chicken[LETECA].alive){
        chicken[LETECA].xCurr -= 0.01;
        chicken[LETECA].yCurr -= 0.005;
        chicken[LETECA].zCurr += 0.07;
        /*ako je otisla dovoljno daleko, i nismo je ubili,vracamo je na pocetak*/
        if(chicken[LETECA].zCurr >= 12.0){
          chicken[LETECA].xCurr = (float)getRand(-4.5,4.5);
          chicken[LETECA].yCurr = 5.5;
          chicken[LETECA].zCurr = -45.0;
        }
      }

      /*mrtva kokoska gubi svoju alfa vrednost, i tako nestaje polako sa scene*/
      if(!chicken[j].alive && chicken[j].activeDeadChicken){
        chicken[j].alpha -= 0.05;
        if(chicken[j].alpha < 0.0){
          chicken[j].alpha = 0.0;
        }
      }
    }

		/*proveravamo da li je metak pogodio neki objekat*/
    bulletCollision();

    /*parametar kako bi se bara talasala*/
    bara+=10;

    glutPostRedisplay();

    /*po potrebi pozivamo opet timer*/
    if (animationOnGoing) {
        glutTimerFunc(TIMER_INTERVAL, onTimer, TIMER_ID);
    }
}

void chickenTimer(int id)
{
  if(TIMER_ID_CHICKEN != id){
    return;
  }

  /*ozivljavamo kokosku u kolima,*/
  chickenIndex++;
  chickensKart[chickenIndex].alive = 1;

  glutPostRedisplay();

  /*na svakih 4.5s*/
  if(animationChicken){
    glutTimerFunc(TIMER_CHICKEN+4500,chickenTimer,TIMER_ID_CHICKEN);
  }
}

void onReshape(int width, int height)
{
  /*Podesava se viewport*/
  glViewport(0,0,width,height);

  /*Podesava se projekcija*/
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60, width/(float)height,1,1000);
}

void onDisplay(void)
{
  /*Brise se prethodni sadrzaj prozora*/
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /*Podesavase vidna tacka*/
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0.0, 1.5, 9.0, 0, 0, 0, 0, 1, 0);

  /*inicijalizacija svetla*/
  initializeLight();
  /*Ukljucujemo koriscenje glColor definisanih boja za materijale */
  glEnable(GL_COLOR_MATERIAL);

  /*ispisi proteklo vreme*/
  printTime();
  /*ispisi rezultat*/
  printScore();

  /*Iscrtava se postolje*/
  ground();
  /*zvezde*/
  drawStar();
  /*bara*/
  drawPuddle();
  /*kuca*/
  drawKuca();
  /*auto*/
  drawAuto();
  /*drvo*/
  drawDrvo();
  /*sunce*/
  drawSun();
  /*oblak*/
  drawCloud();
  /*bundeva*/
  drawBundeva();

  /*ispisujemo odgovarajuci tekst*/
  printText();

  /*ako nam jos nije isteklo vreme*/
  if(!gameOverID){

    int i;
    for(i=0;i<7;i++){
      /*kokoske*/
      drawChicken(i);
      /*mrtva kokoska*/
      if(!chicken[i].alive && chicken[i].activeDeadChicken){
        dead(chicken[i]);
      }
    }

    int count;
    for(count=1;count<=chickenIndex;count++){
      /*kokoske u kolima*/
      drawChickenKart(count);
      if(!chickensKart[count].alive && chickensKart[count].activeDeadChicken){
  			/*mrtva kokoska*/
        dead(chickensKart[count]);
      }
    }

    /*pistolj*/
    drawGun(angleLR,angleTB);
    /*metak*/
    drawBullets();
  }
  /*isteklo je vreme*/
  else{
    /*crtamo meni za gameOver i novu igru*/
    gameOver();
  }

  /*Salje se nova slika na ekran*/
  glutSwapBuffers();
}
