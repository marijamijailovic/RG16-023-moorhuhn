#include "callback.h"

void onKeyboard(unsigned char key,int x,int y)
{
  switch(key){
    case 27:
      /*Zavrsava se igra*/
      exit(-1);
      break;
    /*ugao za koji pomeramo top*/
    case 'a':
    case 'A':
      angleLR += 1.2f;
      break;
    case 'd':
    case 'D':
      angleLR -= 1.2f;
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
						bullets[i].xSpeed = angleLR/120;
						bullets[i].ySpeed = angleTB/120;
            bullets[i].zSpeed = 0.3;
            run = 0;
          }
        }
      }
      break;
    case 'g':
    case 'G':
      /*Startujemo igru*/
      if(!animationOnGoing){
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
    case 'f':
    case 'F':
      glutFullScreen();
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
          if(chickensKart[index].zCurr >= 10.0){
            chickensKart[index].alive = 0;
          }
        }
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
        if(bullets[i].zPos <= -50.0){
            bullets[i].alive = 0;
        }
			}
    }

    for(j = 0;j < 7; j++){
      /*rotiramo istrazivaca levo desno*/
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
      if(j == NINJA && chicken[NINJA].alive){
        /*preletanje ninje*/
        float vector = 0.07;
        chicken[NINJA].xCurr += vector;
        chicken[NINJA].yCurr = -1.0/100.0*(chicken[NINJA].xCurr*chicken[NINJA].xCurr)+2.0;
        if(chicken[NINJA].xCurr >= 12.0){
          chicken[NINJA].xCurr = -17.5;
          chicken[NINJA].yCurr = 0.4;
        }
      }

      if(j == LETECA && chicken[LETECA].alive){
        /*let kokokoske*/
        chicken[LETECA].xCurr -= 0.01;
        chicken[LETECA].yCurr -= 0.005;
        chicken[LETECA].zCurr += 0.07;
        if(chicken[LETECA].zCurr >= 12.0){
          chicken[LETECA].xCurr = (float)getRand(-4.5,4.5);
          chicken[LETECA].yCurr = 5.5;
          chicken[LETECA].zCurr = -45.0;
        }
      }

      if(!chicken[j].alive && chicken[j].activeDeadChicken){
        chicken[j].alpha -= 0.05;
        if(chicken[j].alpha < 0.0){
          chicken[j].alpha = 0.0;
        }
      }
    }

		/*proveravamo da li je metak pogodio neki objekat*/
    bulletCollision();

    bara+=10;

    glutPostRedisplay();

    if (animationOnGoing) {
        glutTimerFunc(TIMER_INTERVAL, onTimer, TIMER_ID);
    }
}

void chickenTimer(int id)
{
  if(TIMER_ID_CHICKEN != id){
    return;
  }

  chickenIndex++;
  chickensKart[chickenIndex].alive = 1;

  glutPostRedisplay();

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

  initializeLight();
  /*Ukljucujemo koriscenje glColor definisanih boja za materijale */
  glEnable(GL_COLOR_MATERIAL);

  if(!gameOverID){
    /*Iscrtava se postolje*/
    ground();
    drawStar();
    drawPuddle();
    drawKuca();
    drawAuto();
    drawDrvo();
    drawSun();
  	/*funkcija koja crta oblake*/
  	drawCloud();
    drawBundeva();

    int i;
    for(i=0;i<7;i++){
      drawChicken(i);
      if(!chicken[i].alive && chicken[i].activeDeadChicken){
        dead(chicken[i]);
      }
    }

    int count;
    for(count=1;count<=chickenIndex;count++){
  		/*crtaju se kokoske*/
      drawChickenKart(count);
      if(!chickensKart[count].alive && chickensKart[count].activeDeadChicken){
  			/*crta se mrtva koka*/
        dead(chickensKart[count]);
      }
      /*if(chickensKart[count].zCurr > 9.0){
        animationOnGoing = 0;
        chickensKart[count].zCurr = 8.0;
        chickensKart[count].alive = 0;
        die();
      }*/
    }

    drawGun(angleLR,angleTB);
    drawBullets();

    printScore();
    printTime();
  }
  else{
    gameOver();
    printScore();
  }
  /*Salje se nova slika na ekran*/
  glutSwapBuffers();
}
