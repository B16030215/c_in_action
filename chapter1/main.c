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
			Gameplay();
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


void MakeTetris(struct Tetris *tetris){
	
	//初始中心块 
	a[tetris->x][tetris->y] = b[0];
	
	switch(tetris->flag){
		case 1:{	//田字块 
			color(10);
			a[tetris->x][tetris->y-1] = b[1];
			a[tetris->x+2][tetris->y-1] = b[2];
			a[tetris->x+2][tetris->y] = b[3];
			break;
		}
		case 2:{	//横直线 
			color(13);
			a[tetris->x-2][tetris->y] = b[1];
			a[tetris->x+2][tetris->y] = b[2];
			a[tetris->x+4][tetris->y] = b[3];
			break;
		}
		case 3:{	//竖直线 
			color(13);
			a[tetris->x][tetris->y-1] = b[1];
			a[tetris->x][tetris->y-2] = b[2];
			a[tetris->x][tetris->y+1] = b[3];
			break;
		}
		case 4:{	//下丁字 
			color(11);
			a[tetris->x-2][tetris->y] = b[1];
			a[tetris->x+2][tetris->y] = b[2];
			a[tetris->x][tetris->y+1] = b[3];
			break;
		}
		case 5:{	//左丁字 
			color(11);
			a[tetris->x][tetris->y-1] = b[1];
			a[tetris->x-2][tetris->y] = b[2];
			a[tetris->x][tetris->y+1] = b[3];
			break;
		}
		case 6:{	//上丁字 
			color(11);
			a[tetris->x-2][tetris->y] = b[1];
			a[tetris->x+2][tetris->y] = b[2];
			a[tetris->x][tetris->y-1] = b[3];
			break;
		}
		case 7:{	//右丁字 
			color(11);
			a[tetris->x][tetris->y-1] = b[1];
			a[tetris->x][tetris->y+1] = b[2];
			a[tetris->x+2][tetris->y] = b[3];
			break;
		}
		case 8:{	//Z字 
			color(14);
			a[tetris->x-2][tetris->y] = b[1];
			a[tetris->x+2][tetris->y+1] = b[2];
			a[tetris->x][tetris->y+1] = b[3];
			break;
		}
		case 9:{	//竖Z字 
			color(14);
			a[tetris->x][tetris->y-1] = b[1];
			a[tetris->x-2][tetris->y] = b[2];
			a[tetris->x-2][tetris->y+1] = b[3];
			break;
		}
		case 10:{	//反Z字 
			color(14);
			a[tetris->x-2][tetris->y] = b[1];
			a[tetris->x][tetris->y-1] = b[2];
			a[tetris->x+2][tetris->y-1] = b[3];
			break;
		}
		case 11:{	//竖反Z字 
			color(14);
			a[tetris->x][tetris->y+1] = b[1];
			a[tetris->x-2][tetris->y] = b[2];
			a[tetris->x-2][tetris->y-1] = b[3];
			break;
		}
		case 12:{	//7字 
			color(12);
			a[tetris->x-2][tetris->y-1] = b[1];
			a[tetris->x][tetris->y-1] = b[2];
			a[tetris->x][tetris->y+1] = b[3];
			break;
		}
		case 13:{	//左7字 
			color(12);
			a[tetris->x-2][tetris->y] = b[1];
			a[tetris->x+2][tetris->y] = b[2];
			a[tetris->x+2][tetris->y-1] = b[3];
			break;
		}
		case 14:{	//上7字 
			color(12);
			a[tetris->x][tetris->y+1] = b[1];
			a[tetris->x+2][tetris->y+1] = b[2];
			a[tetris->x][tetris->y-1] = b[3];
			break;
		}
		case 15:{	//右7字 
			color(12);
			a[tetris->x+2][tetris->y] = b[1];
			a[tetris->x-2][tetris->y] = b[2];
			a[tetris->x-2][tetris->y+1] = b[3];
			break;
		}
		case 16:{	//反7字 
			color(12);
			a[tetris->x+2][tetris->y-1] = b[1];
			a[tetris->x][tetris->y-1] = b[2];
			a[tetris->x][tetris->y+1] = b[3];
			break;
		}
		case 17:{	//左反7字 
			color(12);
			a[tetris->x-2][tetris->y] = b[1];
			a[tetris->x+2][tetris->y] = b[2];
			a[tetris->x+2][tetris->y+1] = b[3];
			break;
		}
		case 18:{	//上反7字 
			color(12);
			a[tetris->x][tetris->y+1] = b[1];
			a[tetris->x-2][tetris->y+1] = b[2];
			a[tetris->x][tetris->y-1] = b[3];
			break;
		}
		case 19:{	//右反7字 
			color(12);
			a[tetris->x+2][tetris->y] = b[1];
			a[tetris->x-2][tetris->y] = b[2];
			a[tetris->x-2][tetris->y-1] = b[3];
			break;
		}
	}
}


void PrintTetris(struct Tetris *tetris){
	for(i=0; i<4; i++){
		b[i] = 1;
	}
	
	MakeTetris(tetris);
	
	for(i=tetris->x-2; i<=tetris->x+4; i+=2){
		for(j=tetris->y-2; j<=tetris->y+1; j++){
			if(a[i][j]==1 && j>FrameY){
				gotoxy(i,j);
				printf("▉");
			}
		}
	}
	
	color(4);
	gotoxy(FrameX+2*Frame_width+3, FrameY+1);
	printf("level : ");
	color(12);
	printf(" %d", tetris->level);
	
	color(4);
	gotoxy(FrameX+2*Frame_width+3, FrameY+3);
	printf("score : ");
	color(12);
	printf(" %d", tetris->score);
	
	color(4);
	gotoxy(FrameX+2*Frame_width+3, FrameY+5);
	printf("speed : ");
	color(12);
	printf(" %dms", tetris->speed);
	
	
	
}


// 返回值 0 为false 1 为true
int ifMove(struct Tetris *tetris){
	// 判断中心方块
	if(a[tetris->x][tetris->y] != 0){
		return 0;
	}
	else{
		if(
			(
				tetris->flag == 1 &&
				a[tetris->x][tetris->y-1] == 0 &&
				a[tetris->x+2][tetris->y-1] == 0 &&
				a[tetris->x+2][tetris->y] == 0
			) ||
			(
				tetris->flag == 2 &&
				a[tetris->x-2][tetris->y] == 0 &&
				a[tetris->x+2][tetris->y] == 0 &&
				a[tetris->x+4][tetris->y] == 0
			) ||
			(
				tetris->flag == 3 &&
				a[tetris->x][tetris->y-1] == 0 &&
				a[tetris->x][tetris->y-2] == 0 &&
				a[tetris->x][tetris->y+1] == 0
			) ||
			(
				tetris->flag == 4 &&
				a[tetris->x-2][tetris->y] == 0 &&
				a[tetris->x+2][tetris->y] == 0 &&
				a[tetris->x][tetris->y+1] == 0
			) ||
			(
				tetris->flag == 5 &&
				a[tetris->x][tetris->y-1] == 0 &&
				a[tetris->x-2][tetris->y] == 0 &&
				a[tetris->x][tetris->y+1] == 0
			) ||
			(
				tetris->flag == 6 &&
				a[tetris->x-2][tetris->y] == 0 &&
				a[tetris->x+2][tetris->y] == 0 &&
				a[tetris->x][tetris->y-1] == 0
			) ||
			(
				tetris->flag == 7 &&
				a[tetris->x][tetris->y-1] == 0 &&
				a[tetris->x][tetris->y+1] == 0 &&
				a[tetris->x+2][tetris->y] == 0
			) ||
			(
				tetris->flag == 8 &&
				a[tetris->x-2][tetris->y] == 0 &&
				a[tetris->x+2][tetris->y+1] == 0 &&
				a[tetris->x][tetris->y+1] == 0
			) ||
			(
				tetris->flag == 9 &&
				a[tetris->x][tetris->y-1] == 0 &&
				a[tetris->x-2][tetris->y] == 0 &&
				a[tetris->x-2][tetris->y+1] == 0
			) ||
			(
				tetris->flag == 10 &&
				a[tetris->x-2][tetris->y] == 0 &&
				a[tetris->x][tetris->y-1] == 0 &&
				a[tetris->x+2][tetris->y-1] == 0
			) ||
			(
				tetris->flag == 11 &&
				a[tetris->x][tetris->y+1] == 0 &&
				a[tetris->x-2][tetris->y] == 0 &&
				a[tetris->x-2][tetris->y-1] == 0
			) ||
			(
				tetris->flag == 12 &&
				a[tetris->x-2][tetris->y-1] == 0 &&
				a[tetris->x][tetris->y-1] == 0 &&
				a[tetris->x][tetris->y+1] == 0
			) ||
			(
				tetris->flag == 13 &&
				a[tetris->x-2][tetris->y] == 0 &&
				a[tetris->x+2][tetris->y] == 0 &&
				a[tetris->x+2][tetris->y-1] == 0
			) ||
			(
				tetris->flag == 14 &&
				a[tetris->x][tetris->y+1] == 0 &&
				a[tetris->x+2][tetris->y+1] == 0 &&
				a[tetris->x][tetris->y-1] == 0
			) ||
			(
				tetris->flag == 15 &&
				a[tetris->x+2][tetris->y] == 0 &&
				a[tetris->x-2][tetris->y] == 0 &&
				a[tetris->x-2][tetris->y+1] == 0
			) ||
			(
				tetris->flag == 16 &&
				a[tetris->x+2][tetris->y-1] == 0 &&
				a[tetris->x][tetris->y-1] == 0 &&
				a[tetris->x][tetris->y+1] == 0
			) ||
			(
				tetris->flag == 17 &&
				a[tetris->x-2][tetris->y] == 0 &&
				a[tetris->x+2][tetris->y] == 0 &&
				a[tetris->x+2][tetris->y+1] == 0
			) ||
			(
				tetris->flag == 18 &&
				a[tetris->x][tetris->y+1] == 0 &&
				a[tetris->x-2][tetris->y+1] == 0 &&
				a[tetris->x][tetris->y-1] == 0
			) ||
			(
				tetris->flag == 19 &&
				a[tetris->x+2][tetris->y] == 0 &&
				a[tetris->x-2][tetris->y] == 0 &&
				a[tetris->x-2][tetris->y-1] == 0
			)
			
		){
			return 1;
		}
		
	}
	
	return 0;
}

void CleanTetris(struct Tetris *tetris){
	for(i=0; i<4; i++){
		b[i] = 0;
	}
	
	MakeTetris(tetris);
	
	for(i=tetris->x-2; i<=tetris->x+4; i+=2){
		for(j=tetris->y-2; j<=tetris->y+1; j++){
			if(a[i][j]==0 && j>FrameY){
				gotoxy(i,j);
				printf("  ");
			}
		}
	}
}

void Del_Fullline(struct Tetris *tetris){
	int k, del_rows = 0;

	for(j=FrameY+Frame_height-1; j>FrameY+1; j--){
		k = 0;

		for(i=FrameX+2; i<2*Frame_width-2; i+=2){
			if(a[i][j]==1){
				k++;

				if(k==Frame_width-2){
					for(k=FrameX+2; k<FrameX+2*Frame_width-2; k+=2){
						a[k][j] = 0;
						gotoxy(k, j);
						printf("  ");			
					}

					for(k=j-1; k=FrameY; k--){
						if(a[i][k]==1){
							a[i][k] = 0;
							gotoxy(i,k);
							printf("  ");
							a[i][k+1] = 0;
							gotoxy(i,k+1);
							printf("▉");
						}
				 	}

					j++;
					del_rows++;
				}
			}
		}
	}

	tetris->score+=100*del_rows;

	if(del_rows>0 && (tetris->score%1000==0 || tetris->score/1000 > tetris->level-1)){
		tetris->speed-=20;
		tetris->level++;
	}

}

void Flag(struct Tetris *tetris){
	tetris->number++;
	srand(time(NULL));
	if(tetris->number==1){
		tetris->flag = rand()%19+1;
	}
	tetris->next = rand()%19+1;
}

void Gameplay(){
	int n;
	struct Tetris t, *tetris=&t;
	char ch;
	tetris->number = 0;
	tetris->speed = 300;
	tetris->score = 0;
	tetris->level = 1;

	while(1){
		Flag(tetris);
		Temp = tetris->flag;
		tetris->x = FrameX + 2*Frame_width+6;
		tetris->y = FrameY + 10;
		tetris->flag = tetris->next;
		PrintTetris(tetris);
		tetris->x = FrameX+Frame_width;
		tetris->y = FrameY-1;
		tetris->flag = Temp;

		while(1){

			label: PrintTetris(tetris);
			Sleep(tetris->speed);
			CleanTetris(tetris);
			Temp1 = tetris->x;
			Temp2 = tetris->flag;

			if(kbhit()){

				ch = getch();

				// 左
				if(ch==75){
					tetris->x-=2;
				}

				// 右
				if(ch==77){
					tetris->x+=2;
				}

				// 下 加速
				if(ch==80){
					if(ifMove(tetris)!=0){
						tetris->y+=2;
					}
					if(ifMove(tetris)==0){
						tetris->y = FrameY+Frame_height-2;
					}
				}

				// 上 变体
				if(ch==72){
					if(tetris->flag>=2 && tetris->flag<=3){
						tetris->flag++;
						tetris->flag%=2;
						tetris->flag+=2;
					}

					if(tetris->flag>=4 && tetris->flag<=7){
						tetris->flag++;
						tetris->flag%=4;
						tetris->flag+=4;
					}

					if(tetris->flag>=8 && tetris->flag<=11){
						tetris->flag++;
						tetris->flag%=4;
						tetris->flag+=8;
					}

					if(tetris->flag>=12 && tetris->flag<=15){
						tetris->flag++;
						tetris->flag%=4;
						tetris->flag+=12;
					}

					if(tetris->flag>=16 && tetris->flag<=19){
						tetris->flag++;
						tetris->flag%=4;
						tetris->flag+=16;
					}
				}

				// space
				if(ch==32){
					PrintTetris(tetris);
					while(1){
						if(kbhit()){
							ch=getch();
							if(ch==32){
								goto label;
							}
						}
					}
				}

				// esc
				if(ch==27){
					system("cls");
					memset(a, 0, 6400*sizeof(int));
					welcome();
				}

				if(ifMove(tetris) == 0){
					tetris->x = Temp1;
					tetris->flag = Temp2;
				}
				else {
					goto label;
				}

			}

			tetris->y++;
			if(ifMove(tetris) == 0){
				tetris->y--;
				PrintTetris(tetris);
				Del_Fullline(tetris);
				break;
			}

		}

		//已经到顶了，显示游戏结束
		for(i=tetris->y-2;i<tetris->y+2;i++)	
  		{
  			if(i==FrameY)
   			{
   				system("cls");	//清屏
                gotoxy(29,7);   //设置显示位置
                printf("   \n");
				color(12);	//红色
				printf("\t\t\t▉▉▉▉ ▉    ▉ ▉▉      \n");
                printf("\t\t\t▉       ▉▉  ▉ ▉  ▉    \n");
                printf("\t\t\t▉▉▉▉ ▉ ▉ ▉ ▉   ▉   \n");
				printf("\t\t\t▉       ▉  ▉▉ ▉  ▉    \n");
				printf("\t\t\t▉▉▉▉ ▉    ▉ ▉▉      \n");
				gotoxy(17,18);
				color(14);
				printf("我要重新玩一局-------1");
				gotoxy(44,18);
				printf("不玩了，退出吧-------2\n");
				int n;
				gotoxy(32,20);
				printf("选择[1/2]:");
				color(11);
				scanf("%d", &n);	//输入 1 或 2
    			switch (n)			//分支语句
    			{
    				case 1:
        				system("cls");
        				Replay(tetris);       	//重新开始
        				break;
    				case 2:
        				exit(0);
        				break;
    			}
   			}
  		}
  		
  		tetris->flag = tetris->next;	//清除右侧下一个方框的图形
  		tetris->x=FrameX+2*Frame_width+6;
  		tetris->y=FrameY+10;
  		CleanTetris(tetris);
  		
	}
}

void Replay(struct Tetris *tetris){
	system("cls");
	memset(a, 0, 6400*sizeof(int));
	DrawGameframe();
	Gameplay();
}


int main(int argc, char *argv[]) {
	
	// 游戏名称 
	title();
	// 用户选项 
	welcome();
	
	return 0;
}
