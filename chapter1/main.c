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

int a[80][80]={0}; //游戏的所有坐标 

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
			DrawGameframe();
			break;
		case 2:
			system("cls");
			break;
		case 3:
			break;
		case 4:
			break;
	}
	
}



void DrawGameframe(){
	
	//游戏标题 
	color(11);
	gotoxy(FrameX+Frame_width-7, FrameY-2);
	printf("趣味俄罗斯方块");
	
	color(2);
	gotoxy(FrameX+2*Frame_width+3, FrameY+7);
	printf("**********");
	
	color(3);
	//gotoxy(FrameX+2*Frame_width+13, FrameY+7);
	printf("下一出现方块：");
	
	color(2);
	gotoxy(FrameX+2*Frame_width+3, FrameY+13);
	printf("**********");
	
	//显示文字选项说明 
	color(14);
	gotoxy(FrameX+2*Frame_width+3, FrameY+15);
	printf("Esc：退出游戏");
	
	gotoxy(FrameX+2*Frame_width+3, FrameY+17);
	printf("↑键：旋转");
	
	gotoxy(FrameX+2*Frame_width+3, FrameY+19);
	printf("空格键：暂停游戏");
	
	//制表
	color(12);
	
	//打印角 
	gotoxy(FrameX, FrameY);
	printf("╔");
	gotoxy(FrameX+2*Frame_width-2, FrameY);
	printf("╗");
	gotoxy(FrameX, FrameY+Frame_height);
	printf("╚");
	gotoxy(FrameX+2*Frame_width-2, FrameY+Frame_height);
	printf("╝");
	
	a[FrameX][FrameY+Frame_height]=2;
	a[FrameX+2*Frame_width-2][FrameY+Frame_height]=2;
	
	
	for(i=2; i<2*Frame_width-2;i+=2){
		// 打印上边框 
		gotoxy(FrameX+i, FrameY);
		printf("═");
		//a[FrameX+i][FrameY]=2;
		// 打印下边框 
		gotoxy(FrameX+i, FrameY+Frame_height);
		printf("═");
		a[FrameX+i][FrameY+Frame_height]=2;
	}
	
	
	for(i=1; i<Frame_height;i+=1){
		// 打印左边框 
		gotoxy(FrameX, FrameY+i);
		printf("║");
		a[FrameX][FrameY+i]=2;
		// 打印右边框 
		gotoxy(FrameX+2*Frame_width-2, FrameY+i);
		printf("║");
		a[FrameX+2*Frame_width-2][FrameY+i]=2;
	}
	
}



int main(int argc, char *argv[]) {
	
	// 游戏名称 
	title();
	// 用户选项 
	welcome();
	
	return 0;
}
