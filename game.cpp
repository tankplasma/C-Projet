#include<iostream>
#include<conio.h>
#include<dos.h> 
#include <windows.h>
#include <time.h>

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70 

using namespace std; 
 
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int enemyY[3];
int enemyX[3];
int enemyFlag[3];
char car[4][4] = { ' ','±','±',' ', 
					'±','±','±','±', 
					' ','±','±',' ',
					'±','±','±','±' }; 
					
int carPos = WIN_WIDTH/2;
int score = 0; 

void GoToXY(int x, int y){
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}
void SetCurseur(bool visible, DWORD size) {
	if(size == 0)
		size = 20;	
	
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}
void AfficherBorder(){  
	for(int i=0; i<SCREEN_HEIGHT; i++){
		for(int j=0; j<17; j++){
			GoToXY(0+j,i); cout<<"±";
			GoToXY(WIN_WIDTH-j,i); cout<<"±";
		}
	} 
	for(int i=0; i<SCREEN_HEIGHT; i++){
		GoToXY(SCREEN_WIDTH,i); cout<<"±";
	} 
}
void EnemyGeneration(int ind){
	enemyX[ind] = 17 + rand()%(33);  
}
void AfficherEnemy(int ind){
	if( enemyFlag[ind] == true ){
		GoToXY(enemyX[ind], enemyY[ind]);   cout<<"****";  
		GoToXY(enemyX[ind], enemyY[ind]+1); cout<<" ** "; 
		GoToXY(enemyX[ind], enemyY[ind]+2); cout<<"****"; 
		GoToXY(enemyX[ind], enemyY[ind]+3); cout<<" ** ";  
	} 
}
void EffacerEnemy(int ind){
	if( enemyFlag[ind] == true ){
		GoToXY(enemyX[ind], enemyY[ind]); cout<<"    ";  
		GoToXY(enemyX[ind], enemyY[ind]+1); cout<<"    "; 
		GoToXY(enemyX[ind], enemyY[ind]+2); cout<<"    "; 
		GoToXY(enemyX[ind], enemyY[ind]+3); cout<<"    "; 
	} 
}
void ResetEnemy(int ind){
	EffacerEnemy(ind);
	enemyY[ind] = 1;
	EnemyGeneration(ind);
}

void AfficherCar(){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			GoToXY(j+carPos, i+22); cout<<car[i][j];
		}
	}
}
void EffacerCar(){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			GoToXY(j+carPos, i+22); cout<<" ";
		}
	}
}
 
int Collision(){
	if( enemyY[0]+4 >= 23 ){
		if( enemyX[0] + 4 - carPos >= 0 && enemyX[0] + 4 - carPos < 9  ){
			return 1;
		}
	}
	return 0;
} 
void Fin(){
	system("cls");
	cout<<endl;
	cout<<"\t\t--------------------------"<<endl;
	cout<<"\t\t---------- Perdu ---------"<<endl;
	cout<<"\t\t--------------------------"<<endl<<endl;
	cout<<"\t\tappuyez sur n'importe quelle touche pour retourner au menu.";
	getch();
}
void Score(){
	GoToXY(WIN_WIDTH + 7, 5);cout<<"Score: "<<score<<endl;
}

void Instructions(){
	
	system("cls");
	cout<<"Instructions";
	cout<<"\n----------------";
	cout<<"\n éviter une voiture en faisant droite gauche ";
	cout<<"\n\n appuyer sur a pour bouger a gauche";
	cout<<"\n appuyez sur d pour bouger a droite";
	cout<<"\n appuyer sur echap pour partir";
	cout<<"\n\nappuyer sur d'autre touches pour revenir au menu";
	getch();
}

void Play(){
	carPos = -1 + WIN_WIDTH/2;
	score = 0;
	enemyFlag[0] = 1;
	enemyFlag[1] = 0;
	enemyY[0] = enemyY[1] = 1;
	  
	system("cls"); 
	AfficherBorder(); 
	Score();
	EnemyGeneration(0);
	EnemyGeneration(1);
	
	GoToXY(WIN_WIDTH + 7, 2);cout<<"Car Game";
	GoToXY(WIN_WIDTH + 6, 4);cout<<"----------";
	GoToXY(WIN_WIDTH + 6, 6);cout<<"----------";
	GoToXY(WIN_WIDTH + 7, 12);cout<<"Control ";
	GoToXY(WIN_WIDTH + 7, 13);cout<<"-------- ";
	GoToXY(WIN_WIDTH + 2, 14);cout<<" A Key - Left";
	GoToXY(WIN_WIDTH + 2, 15);cout<<" D Key - Right"; 
	
	GoToXY(18, 5);cout<<"Press any key to start";
	getch();
	GoToXY(18, 5);cout<<"                      ";
	
	while(1){
		if(kbhit()){
			char ch = getch();
			if( ch=='a' || ch=='A' ){
				if( carPos > 18 )
					carPos -= 4;
			}
			if( ch=='d' || ch=='D' ){
				if( carPos < 50 )
					carPos += 4;
			} 
			if(ch==27){
				break;
			}
		} 
		
		drawCar(); 
		AfficherEnemy(0); 
		AfficherEnemy(1); 
		if( Collision() == 1  ){
			Fin();
			return;
		} 
		Sleep(50);
		EffacerCar();
		EffacerEnemy(0);
		EffacerEnemy(1);   
		
		if( enemyY[0] == 10 )
			if( enemyFlag[1] == 0 )
				enemyFlag[1] = 1;
		
		if( enemyFlag[0] == 1 )
			enemyY[0] += 1;
		
		if( enemyFlag[1] == 1 )
			enemyY[1] += 1;
		 
		if( enemyY[0] > SCREEN_HEIGHT-4 ){
			resetEnemy(0);
			score++;
			Score();
		}
		if( enemyY[1] > SCREEN_HEIGHT-4 ){
			resetEnemy(1);
			score++;
			Score();
		}
	}
}

int main()
{
	SetCurseur(0,0); 
	srand( (unsigned)time(NULL)); 
	 
	do{
		system("cls");
		GoToXY(10,5); cout<<" -------------------------- "; 
		GoToXY(10,6); cout<<" |        Voiture         | "; 
		GoToXY(10,7); cout<<" --------------------------";
		GoToXY(10,9); cout<<"1. jouer";
		GoToXY(10,10); cout<<"2. Instructions";	 
		GoToXY(10,11); cout<<"3. quitter";
		GoToXY(10,13); cout<<"choisissez: ";
		char op = getche();
		
		if( op=='1') Play();
		else if( op=='2') Instructions();
		else if( op=='3') exit(0);
		
	}while(1);
	
	return 0;
}