#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

/******************宏定义***************/ 
#define FrameX 13
#define FrameY 3
#define Frame_height 20
#define Frame_width 18

/************定义全局变量*************/
int i,j,Temp,Temp1,Temp2;

int a[80][80]={0};
int b[4];


struct Tetris{
	int x;
	int y;
	int flag;
	int next;
	int speed;
	int number;
	int score;
	int level;
}; 

HANDLE hOut;


/*********函数声明************/
int color(int c); 
void gotoxy(int x, int y);
void DrawGameframe();
void Flag(struct Tetris *);
void MakeTetris(struct Tetris *);
void PrintTetris(struct Tetris *);
void CleanTetris(struct Tetris *);
int ifMove(struct Tetris *);
void Del_Fullline(struct Tetris *);
void Gameplay();
void regulation();
void explation();
void welcome();
void Replay(struct Tetris *);
void title();
void flower();
void close();

int color(int c){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
	return 0;
}

void gotoxy(int x, int y){
	COORD pos;
	pos.X = x;
	pos.Y = y;
	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void title(){
	color(15);
	gotoxy(24, 3);
	printf("趣 味 俄 罗 斯 方 块\n");
	
	color(11);
	gotoxy(18, 5);
	printf("▉");
	gotoxy(18,6);
	printf("▉▉");
	gotoxy(18,7);
	printf("▉");
	
	color(14);
	gotoxy(26,6);
	printf("▉▉");
	gotoxy(28,7);
	printf("▉▉");
	
	color(10);
	gotoxy(36,6);
	printf("▉▉");
	gotoxy(36,7);
	printf("▉▉");
	
	color(13);
	gotoxy(45,5);
	printf("▉");
	gotoxy(45,6);
	printf("▉");
	gotoxy(45,7);
	printf("▉");
	gotoxy(45,8);
	printf("▉");
	
	
	color(12);
	gotoxy(56,6);
	printf("▉");
	gotoxy(52,7);
	printf("▉▉▉");
	
}

void welcome(){
	
	int n; //接收用户输入的选项参数 
	
	int i,j = 1;
	
	color(14);
	
	for (i=9; i<=20; i++){
		for (j=15; j<=60; j++){
			gotoxy(j,i);
			if(i==9 || i==20) 
				printf("=");
			else if(j==15 || j==59)
				printf("||") ;
		}
	}
	
	// 打印选项 
	color(12);
	gotoxy(25,12);
	printf("1.开始游戏");
	gotoxy(40,12);
	printf("2.按键说明");
	gotoxy(25,17);
	printf("3.游戏规则");
	gotoxy(40,17);
	printf("4.退出");
	
	//选项选择提示
	color(3);
	gotoxy(21, 22);
	printf("请选择[1 2 3 4]:[ ]\b\b");
	
	//接收用户输入的参数 
	color(14);
	scanf("%d",&n);
	
	switch(n){
		case 1:
			system("cls");
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
	}
	
}


int main(int argc, char *argv[]) {
	
	// 游戏名称 
	title();
	// 用户选项 
	welcome();
	
	return 0;
}
