#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

/******************�궨��***************/ 
#define FrameX 13
#define FrameY 3
#define Frame_height 20
#define Frame_width 18

/************����ȫ�ֱ���*************/
int i,j,Temp,Temp1,Temp2;

int a[80][80]={0}; //��Ϸ���������� 

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


/*********��������************/
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
	printf("Ȥ ζ �� �� ˹ �� ��\n");
	
	color(11);
	gotoxy(18, 5);
	printf("��");
	gotoxy(18,6);
	printf("����");
	gotoxy(18,7);
	printf("��");
	
	color(14);
	gotoxy(26,6);
	printf("����");
	gotoxy(28,7);
	printf("����");
	
	color(10);
	gotoxy(36,6);
	printf("����");
	gotoxy(36,7);
	printf("����");
	
	color(13);
	gotoxy(45,5);
	printf("��");
	gotoxy(45,6);
	printf("��");
	gotoxy(45,7);
	printf("��");
	gotoxy(45,8);
	printf("��");
	
	
	color(12);
	gotoxy(56,6);
	printf("��");
	gotoxy(52,7);
	printf("������");
	
}

void welcome(){
	
	int n; //�����û������ѡ����� 
	
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
	
	// ��ӡѡ�� 
	color(12);
	gotoxy(25,12);
	printf("1.��ʼ��Ϸ");
	gotoxy(40,12);
	printf("2.����˵��");
	gotoxy(25,17);
	printf("3.��Ϸ����");
	gotoxy(40,17);
	printf("4.�˳�");
	
	//ѡ��ѡ����ʾ
	color(3);
	gotoxy(21, 22);
	printf("��ѡ��[1 2 3 4]:[ ]\b\b");
	
	//�����û�����Ĳ��� 
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
	
	//��Ϸ���� 
	color(11);
	gotoxy(FrameX+Frame_width-7, FrameY-2);
	printf("Ȥζ����˹����");
	
	color(2);
	gotoxy(FrameX+2*Frame_width+3, FrameY+7);
	printf("**********");
	
	color(3);
	//gotoxy(FrameX+2*Frame_width+13, FrameY+7);
	printf("��һ���ַ��飺");
	
	color(2);
	gotoxy(FrameX+2*Frame_width+3, FrameY+13);
	printf("**********");
	
	//��ʾ����ѡ��˵�� 
	color(14);
	gotoxy(FrameX+2*Frame_width+3, FrameY+15);
	printf("Esc���˳���Ϸ");
	
	gotoxy(FrameX+2*Frame_width+3, FrameY+17);
	printf("��������ת");
	
	gotoxy(FrameX+2*Frame_width+3, FrameY+19);
	printf("�ո������ͣ��Ϸ");
	
	//�Ʊ�
	color(12);
	
	//��ӡ�� 
	gotoxy(FrameX, FrameY);
	printf("�X");
	gotoxy(FrameX+2*Frame_width-2, FrameY);
	printf("�[");
	gotoxy(FrameX, FrameY+Frame_height);
	printf("�^");
	gotoxy(FrameX+2*Frame_width-2, FrameY+Frame_height);
	printf("�a");
	
	a[FrameX][FrameY+Frame_height]=2;
	a[FrameX+2*Frame_width-2][FrameY+Frame_height]=2;
	
	
	for(i=2; i<2*Frame_width-2;i+=2){
		// ��ӡ�ϱ߿� 
		gotoxy(FrameX+i, FrameY);
		printf("�T");
		//a[FrameX+i][FrameY]=2;
		// ��ӡ�±߿� 
		gotoxy(FrameX+i, FrameY+Frame_height);
		printf("�T");
		a[FrameX+i][FrameY+Frame_height]=2;
	}
	
	
	for(i=1; i<Frame_height;i+=1){
		// ��ӡ��߿� 
		gotoxy(FrameX, FrameY+i);
		printf("�U");
		a[FrameX][FrameY+i]=2;
		// ��ӡ�ұ߿� 
		gotoxy(FrameX+2*Frame_width-2, FrameY+i);
		printf("�U");
		a[FrameX+2*Frame_width-2][FrameY+i]=2;
	}
	
}



int main(int argc, char *argv[]) {
	
	// ��Ϸ���� 
	title();
	// �û�ѡ�� 
	welcome();
	
	return 0;
}
