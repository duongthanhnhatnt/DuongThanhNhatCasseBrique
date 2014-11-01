//*****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <termios.h>
#include <fcntl.h>

using namespace std;

int read_keybord();
/******************************************************************************/
#define H 20
#define L 40
char tab[H][L];

/* faire la cadre***********************************************************/
void cadre() {  
 
  for (int i=0; i<H;i++) {
      for (int j=0; j<L; j++)
	if (i==0||i==H-1||j==L-1||j==0)
	  tab[i][j]='I';
      cout << endl;
    }
  for (int i=0; i<H; i++){
      for(int j=0;j<L;j++)
	cout << tab[i][j];
      cout<< endl;
    }
}

/*clear screen*************************************************************/
void clear_screen() { 
  for (int i=1; i<H-1; i++)
    for (int j=1; j<L-1; j++)
      tab[i][j] = ' '; 
}

/*fair le balle***************************************************************/
int x=1,y=1;
int dx=1, dy=1;
void leballe() {
  tab[x][y]='O';
  if(x==H-3)  dx=-1;
  if(y==L-2)  dy=-1;
  if (x==1)   dx=1;
  if (y==1)   dy=1;
  x+=dx;
  y+=dy;    
}
   
/*faire la barre**************************************************************/

int n=12,m=26;
int key=read_keybord();

void labarre() {
  for(int i=0;i<L;i++)
    {
      if (i>n && i<m)
	tab[H-2][i]='=';
    }
  for (int i=0; i<L; i++)
    cout << tab[H-2][i];
 
}
/*faire deplacer la barre******************************************************/
void keyprocess(char key) {
  if ((key=='a')&&(n>0)){ 
   n--; m--;
  }
 if ((key=='d') && (m<L-1)){
   m++; n++;
 }
}


/*faire les briques************************************************************/

int i=0, j=0;
int b1[H][L];
int a=0;

void briques() { 
  for (i=0;i<L;i++)
    {  
      if ((i>9 && i<30) && i!=a) 
	  tab[2][i]='X';
      if ((i>12 && i<27) && i!=a)
	tab[3][i]='X';
    }
}
  /* if ((y>9 && y<30)&& x==3) {
    tab[2][y]=' ';
    a=y;
  }
  if ((y>12 && y<27)&& x==4) {
    tab[3][y]=' ';
    a=y;
  }
}
  */  
/*faire disparaitre les briques************************************************/




/*compte le score**************************************************************/
 int cpt=0;
 void compte() {
   if (dx==1 && (y>n && y<m) && x==H-3)
     cpt=cpt+50;
   if (dx==1 && (y<=n && y>=m) && x==H-3) { 
     cout << " you lose!" << endl; 
     cout << "your score:" << cpt << endl;
     exit(0);
     
   }
 }   
/******************************************************************************/

int main() {
  int key;
  int score=0;
  do
    { 
      key=read_keybord();
      clear_screen();
      briques();
      labarre();
      leballe();     
      keyprocess(key);
      compte();
      cadre();     
      usleep(10*10000);    
    }
  while(key!='q');
}
/******************************************************************************/

int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }

  return 0;
}

int read_keybord() {
  int key;
  if (kbhit())
    key = getc(stdin);
  else
    key = 0;
  return key;
}

/******************************************************************************/
