
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
void setup(){
  cout << "       BIENVENUE AU JEU CASEBRIQUE"<< endl;
  cout << "pressez 'p' pour commencer" << endl;
  cout << "pressez 's' pour depasser les niveaux lors du commencement du jeu (avant de presser 'p')" << endl;
  cout << "pressez 'a' pour aller a gauche" << endl;
  cout << "pressez 'd' pour aller a droite " << endl;
  cout << "pressez 'q' pour quitter le jeu " << endl;
  cout << "une fois que le balle toucher une brique tu gagnes 25point, si le balle ne touche pas la barre tu es perdue" << endl;
}
/* faire la cadre***********************************************************/
void cadre() { 
  for (int i=0; i<H; i++) {
      for (int j=0; j<L; j++)
	if (i==0||j==L-1||j==0||i==H-1)
	  tab[i][j]='I';
      cout << endl;
    }
}
/*afficher les elements******************************************************/
void display(){
  for (int i=0; i<H; i++){
      for(int j=0;j<L;j++)
	cout << tab[i][j];
      cout<< endl;
  }
}

/*clear screen*************************************************************/
void clear_screen() { 
  for(int i=0; i<H; i++)
    for (int j=0; j<L; j++)
      tab[i][j] = ' '; 
}

/*les briques******************************************************/
int s;
bool tab1[10][L];
void briquespresent1(){ //un table pour controller la presentation des briques, briquespresent1=position des briques du level 1
  for (s=2;s<10;s++)
    for (int i=0; i<L; i++){
      if (s==2 && (i>9 && i<30))
	tab1[2][i]=true;
      if (s==3 &&(i>12 && i<27))
	tab1[3][i]=true;    
    }
}

void briquespresent2(){// briquespresent2=position des briques du level 2
  for (s=2; s<10;s++)
    for (int i=0; i<L; i++){
      if (s==2){
	if ((i>7 && i<16)||(i>17 && i<22)||(i>23 && i<32))
	  tab1[2][i]=true;
      }
      if (s==3){
	if ((i>10 && i<17)||(i>22 && i<29))
	  tab1[3][i]=true;
      }
      if (s==4){
	if ((i>5 && i<14)||(i>25 && i<34)||(i>17 && i<22)) 
	  tab1[4][i]=true;
      }
    }
}

void briquespresent3(){// briquespresent3=position des briques du level 3 
  for (s=2; s<10;s++)
    for (int i=0; i<L; i++){
      if (s==2){
	if ((i%2==0 && i>3)&&(i<L-3))
	  tab1[2][i]=true;
      }
      if (s==3) { 
	if (i>12 && i<28) 
	  tab1[3][i]=true;
      }
      if (s==4) { 
	if ((i%2==0 && i>5)&&(i<L-5))
	tab1[4][i]=true;
      }
      if (s==5){
	if (i==7||i==11||i==15||i==19||i==23||i==27||i==31){
	  tab1[5][i]=true;
	  tab1[5][i+1]=true;
	}
      }
    }
}
/*faire afficher les briques***************************************************/
void briques(){ // si tab1[][]=true, on fait paraitre les briques, tab1[][]=false on n'affiche pas le briques.
    for (int i=0; i<L; i++){
      if (tab1[2][i]==true)
	tab[2][i]='X';
      if (tab1[3][i]==true)
	tab[3][i]='X';
      if (tab1[4][i]==true)
	tab[4][i]='X';
      if (tab1[5][i]==true)
	tab[5][i]='X';
    }
}

int key=read_keybord();
int n=27, m=12;
int cpt=0;
int dx=1, dy=1;
int x=1,y=1,a1=1;
char a2;
bool br=true;

/*faire la barre**************************************************************/

void labarre(){
  for(int i=0; i<L; i++){ 
    if(i>m && i<n)
       tab[H-2][i]='=';
  }
}
/*faire deplacer la barre******************************************************/
void keyprocess(char key) {
  if ((key=='a')&&(m>0)){ 
   n=n-2; m=m-2;
  }
 if ((key=='d') && (n<L-1)){
   m=m+2; n=n+2;
 }
}
/*faire afficher le niveau de jeu********************************************/
void level(){ 
  cout << "LEVEL " << a1 << endl;
}

/*faire afficher le score du joueux ****************************************/
void score(){ 
  cout << "Votre score: " << cpt << endl;
}

/*compter le score**********************************************************/
void compter(){
  /*quand le balle toucher la brique, la brique disparait et le score augmente,chaque brique=25point******************/
  if (tab[x][y]=='X'){
    tab1[x][y]=false;
    dx=-1*dx;
    cpt=cpt+25;
    if (tab[x][y+1]=='X'){
      tab1[x][y+1]=false;
      cpt=cpt+25;
    }  
  }
  /*quand on depasse level 1 ou level 2, on presser 'g' pour continuer, quand on fini level 3, le programme arrete.*/
  if ((a1==1 && cpt==850)||(a1==2 && cpt==2150)||(a1==3 && cpt==3675)){
    tab[x][y+1]=' ';
    tab[x][y-1]=' ';
    tab[x][y]='O';
    cadre();
    system("clear");
    setup();
    level();
    score();
    display();
    if(a1==2||a1==1) { 
    cout << "BRAVO!!!!"<< endl;
    cout << "YOU PASSE LEVEL " << a1  << "!!!" << endl;
    cout << "Voulez vous continuer? " << endl;
    cout << "Pressez 'g' pour le niveau suivant,pressez 'q' pour quitter " << endl;
    cin >> a2;
    if (a2=='g'){
      a1=a1+1;
      br=true;
      x=1;
      y=1;
      dx=1;
      dy=1;
    }
  }
    if (a1==3 && cpt==3675){
      
      cout << "TRES EXCELLENT VOUS PASSEZ LES TROIS NIVEAUX!!!" << endl;
      cout << "YOU WIN!!!!!!!!" << endl;
      exit(0);
    }    
  }  
}
/*faire le balle********************************************************/
void leballe() {
  if (br==true && a1==1){
    briquespresent1();
    cpt=0;
  }
  if(br==true && a1==2){
    briquespresent2();
  }
  if (br==true && a1==3){
    briquespresent3();
  }
  br=false;
  briques();
  compter();

  tab[x][y]='O';
  if(y==L-2)  dy=-1;
  if (x==1)   dx=1;
  if (y==1)   dy=1;
  if(x==H-3 && tab[x+1][y]=='=')  dx=-1;

  if (x==H-2 && tab[x+1][y]==' '){ // quand le balle ne touche pas la barre, le joueux est perdu
    if (dx==1){
      x=+dx;
      y=+dy;
    }
    if (dx==-1){
      x=+dx;
      y=-dy;
    }
    cadre();
    system("clear");
    setup();
    level();
    score();
    display();
    cout << "YOU LOSE!!!! " << endl;
    exit(0);  
  }
  x+=dx;
  y+=dy;
}

/******************************************************************************/

int main() {
  int key;
  int t=0;
  do
    {
      key=read_keybord();
      clear_screen();
      labarre();
      if (t==0) { //dans la premier fois que le programme marche, on doit presser 'p' pour commencer
	if (key=='s') {// presser 's' pour depasser les niveaux avant de jouer (avant de presser 'p'pour commencer). 
	  a1=a1+1;
	  if (a1==2)  //si on choisi level 2 pour jouer le cpt est automatiquement 850.
	    cpt=850;
	  if (a1==3)  //si on choisi level 3 pour jouer le cpt est automatiquement 2150.
	    cpt=2150;
	  if (a1>3){  // si on presse 's' sans arret, le programme reste toujours au niveau 3.
	    a1=3;
	  }
	}
	if (key=='p') {
	  t=1;
	  leballe();
	}
      }
      else {   // apres la premiere fois que le programme marche, tout se passe normalement
	leballe();
      }
      keyprocess(key);
      cadre();
      system("clear");
      setup();
      level();
      score();
      display();
      if (a1==1){  // a chaque niveau de jeu, la vitesse augmente.
	usleep(12*10000); 
      }
      if (a1==2){ 
	usleep(10*10000);
      }
      if (a1==3) { 
	usleep(8*10000);
      }

    }
  while(key!='q'); // quand on presse 'q' le programme arrete.
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
