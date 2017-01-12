#include "callback.h"

void onKeyboard(unsigned char key,int x,int y)
{
  switch(key){
    case 27:
      /*Zavrsava se igra*/
      exit(EXIT_SUCCESS);
      break;
    /*ugao za koji pomeramo top*/
    case 'a':
    case 'A':
      angleLR += 5.0; /*rotiramo pistolj levo*/
      /*granica dokle moze da ide levo*/
      if(angleLR > 60.0){
        angleLR = 60.0;
      }
      break;
    case 'd':
    case 'D':
      angleLR -= 5.0; /*rotiramo pistolj desno*/
      /*granica dokle moze da ide desno*/
      if(angleLR < -60.0){
        angleLR = -60.0;
      }
      break;
    case 's':
    case 'S':
      angleTB -= 3.0; /*rotiramo pistolj dole*/
      /*granica dokle moze da ide dole*/
      if(angleTB < 0.5){
        angleTB = 0.5;
      }
      break;
    case 'w':
    case 'W':
      angleTB += 3.0; /*rotiramo pistolj gore*/
      /*granica dokle moze da ide gore*/
      if(angleTB > 18){
        angleTB = 18;
      }
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
            bullets[i].xSpeed = angleLR/100;
            bullets[i].ySpeed = angleTB/100;
            bullets[i].zSpeed = 0.5;
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
        /*indikator za novu igru*/
        gameOverID = 0;
        /*aktiviramo score*/
        scoreID = 1;
        timeID = 1;
        animationOnGoing = 1;
        animationChicken = 1;
        /*ovde inizijalizujemo kokoske, jer ne zelim da se vidi
        gde su one inicijalno postavljene, pre nego sto igrica pocne*/
        initializeChicken();
        glutTimerFunc(TIMER_CHICKEN,chickenTimer,TIMER_ID_CHICKEN);
        glutTimerFunc(TIMER_INTERVAL,onTimer,TIMER_ID);
      }
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

    for(j = 0;j < CHICKEN_MAX; j++){
      /*rotiramo istrazivaca malo levo desno*/
      if(j == EXPLORER && chicken[EXPLORER].alive){
        if(chicken[EXPLORER].animationAction){
          angleRotation--;
          if(angleRotation < -75){
            chicken[EXPLORER].animationAction = 0;
          }
        }
        if(!chicken[EXPLORER].animationAction){
          angleRotation++;
          if(angleRotation > 0){
            chicken[EXPLORER].animationAction = 1;
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
      if(j == FLY && chicken[FLY].alive){
        chicken[FLY].xCurr -= 0.01;
        chicken[FLY].yCurr -= 0.005;
        chicken[FLY].zCurr += 0.05;
        /*ako je otisla dovoljno daleko, i nismo je ubili,vracamo je na pocetak*/
        if(chicken[FLY].zCurr >= 12.0){
          chicken[FLY].xCurr = (float)getRand(-4.5,4.5);
          chicken[FLY].yCurr = 5.5;
          chicken[FLY].zCurr = -30.0;
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

  /*ozivljavamo kokosku u kolima*/
  chickenIndex++;
  chickensKart[chickenIndex].alive = 1;

  glutPostRedisplay();

  if(animationChicken){
    glutTimerFunc(TIMER_CHICKEN+4000,chickenTimer,TIMER_ID_CHICKEN);
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
  drawHome();
  /*auto*/
  drawCar();
  /*drvo*/
  drawWood();
  /*sunce*/
  drawSun();
  /*oblak*/
  drawCloud();
  /*bundeva*/
  drawPumpkin();

  /*ispisujemo odgovarajuci tekst*/
  printText();

  /*ako nam jos nije isteklo vreme*/
  if(!gameOverID){
    int i;
    for(i=0;i<CHICKEN_MAX;i++){
      /*kokoske*/
      drawChicken(i);
      /*mrtva kokoska*/
      if(!chicken[i].alive && chicken[i].activeDeadChicken){
        dead(chicken[i]);
      }
    }

    for(i=1;i<=chickenIndex;i++){
      /*kokoske u kolima*/
      drawChickenKart(i);
      /*mrtva kokoska*/
      if(!chickensKart[i].alive && chickensKart[i].activeDeadChicken){
        dead(chickensKart[i]);
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
