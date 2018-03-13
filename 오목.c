#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
//////////////////////////////////////////////////////////////////////////////////////////////
#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define ENTER 13
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;

typedef struct player{
	char name[20];
	int win;
	int lose;
	struct player *next;
}Player;

void setcursortype(CURSOR_TYPE c)
{
 CONSOLE_CURSOR_INFO CurInfo;
 switch (c) {
 case NOCURSOR:
  CurInfo.dwSize=1;
  CurInfo.bVisible=FALSE;
  break;
 case SOLIDCURSOR:
  CurInfo.dwSize=100;
  CurInfo.bVisible=TRUE;
  break;
 case NORMALCURSOR:
  CurInfo.dwSize=20;
  CurInfo.bVisible=TRUE;
  break;
 }
 SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&CurInfo);
}


//////////////////////////////////////////////////////////////////////////////////////////////
int win_player=0;
int lose_player=0;
char playname[20];
int a=8;
int b=8;
int fx=18;
int fy=9;
int count_white=0;
int count_black=0;
char black[3];
char white[3];
char star[3];
char back[15][15][3];
char background[3];
char p1[20];
char p2[20];
int judge=0;
char nKey;
char nKey_1;
int mx=1, my=10;
int zpx=2, zpy=1;
int zx=2, zy=1;
int player=0;
void zgotoxy(int x, int y);
void zmovezy(char nkey);
void help();
void ground();
void status(int player, int x, int y);
int count=0;
void win();
int stone[20][20];//0->無 1->白 2->黑
void reground(int x, int y);
void restone(int x, int y);
void setcolor(int color, int bgcolor);
const char *zone[3] = {
	{"┌┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┐\n"},
	{"├┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┤\n"},
	{"└┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┘\n"}};

//////////////////////////////////////////////////////////////////////////////////////////////
void mgotoxy(int x, int y);
void movexy(char nkey);
void menu_oneortwo(int x, int y);
void help();
void Back();
void printf_back();
void Black();
void White();
void judge_black();
void judge_white();
void save_p1();
void play1();
void gotoxy(int x, int y);
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	setcursortype(NOCURSOR);
    
	strcpy(white,"○"); 
 	strcpy(black,"●");
	strcpy(background,"┼");
 	strcpy(star,"◎");

	srand((unsigned int)time(NULL));
	menu();
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
/*void add_node()
{
	Player *data;
	Player *head;
	
	FILE* fp;
	fp=fopen("data.txt","w");
	head=data;

	if(data==NULL)
	{
		data=(Player*)malloc(sizeof(Player));
		fprintf(fp,"%s: %d",win_player,playname);
	}
	else
	{
		while(data!=NULL)
			data=data->next;
	}
	
}*/
//////////////////////////////////////////////////////////////////////////////////////////////
void ground()
{
	int g;
	setcolor(0,15);
	printf("%s", zone[0]);
	for(g=0;g<16;g++)
	printf("%s", zone[1]);
	printf("%s", zone[2]);
	
}
//////////////////////////////////////////////////////////////////////////////////////////////
void play2()
{
	ground();
	//커서를 숨김
	SetCursor(0);
	zgotoxy(zx, zy);
	printf("⊙");
	status(player, zpx, zpy);	
	while(1)
	{
		if(_kbhit())
		{
			nKey=_getch();
			zmovezy(nKey);
		}
	}
	exit(1);
}
//////////////////////////////////////////////////////////////////////////////////////////////
void zgotoxy(int x, int y)
{
	COORD Pos={x, y};
	SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	zx=x;
	zy=y;
}
//////////////////////////////////////////////////////////////////////////////////////////////
void zmovezy(char nkey)
{
	int zpx=zx;	
	int zpy=zy;

	reground(zpx, zpy);
	zgotoxy(zpx, zpy); 
	restone(zpx, zpy);
	switch(nkey)
	{
		case UP:
			if(zpy!=1)
				zpy--;
			else if(zpy==1)
				zpy=16;
			zgotoxy(zpx, zpy);
			printf("⊙");
			break;
		case DOWN:
			if(zpy!=16)
				zpy++;
			else if(zpy==16)
				zpy=1;
			zgotoxy(zpx, zpy);
			printf("⊙");
			break;
		case RIGHT:
			if(zpx!=30)
				{zpx++;
				zpx++;}
			else if(zpx==30)
				zpx=2;
			zgotoxy(zpx, zpy);
			printf("⊙");
			break;
		case LEFT:
			if(zpx!=2)
				{zpx--;
			    zpx--;}
			else if(zpx==2)
				zpx=30;
			zgotoxy(zpx, zpy);
			printf("⊙");
			break;
		case ENTER:
			count++;
			if(player==0)
			{
				if(stone[zpx][zpy]==2)
					break;
				stone[zpx][zpy]=1;
				printf("○");
				player=1;
				break;
			}
			else if(player==1)
			{
				if(stone[zpx][zpy]==1)
					break;
				stone[zpx][zpy]=2;
				printf("●");
				player=0;
				break;
			}
	}

	status(player, zpx, zpy);	


	win();
}
//////////////////////////////////////////////////////////////////////////////////////////////
void reground(int x, int y)
{
	if(x==0)
	{
		if(y==0)
			printf("┌");
		else if(y==17)
			printf("└");
		else
			printf("├");
	}
	else if(x==32)
	{
		if(y==0)
			printf("┐");
		else if(y==17)
			printf("┘");
		else
			printf("┤");
	}
	else
	{
		if(y==0)
			printf("┬");
		else if(y==17)
			printf("┴");
		else
			printf("┼");
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////
void restone(int x, int y)
{
	if(stone[x][y]==1)
	{
		printf("○");
	}
	if(stone[x][y]==2)
	{
		printf("●");
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////
void setcolor(int color,int bgcolor) // 글자색과 바둑판 색 설정
{
	color &= 0xf;
	bgcolor &= 0xf;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgcolor<<4) | color);
}
//////////////////////////////////////////////////////////////////////////////////////////////
void win()
{
	int i;
	int j;

	//흰색 승//
	for(j=0; j<15; j++)
	{
		for(i=0;i<33;i++)
		{
			if(stone[i][j]==1&&stone[i+2][j]==1&&stone[i+4][j]==1&&stone[i+6][j]==1&&stone[i+8][j]==1)
			{
				i=4;
				j=20;
				zgotoxy(i, j);
				printf("White WIN");
				getch();
				exit(1);
			}
		}
	}

	for(i=0; i<33; i++)
	{
		for(j=0;j<15;j++)
		{
			if(stone[i][j]==1&&stone[i][j+1]==1&&stone[i][j+2]==1&&stone[i][j+3]==1&&stone[i][j+4]==1)
			{
				i=4;
				j=20;
				zgotoxy(i, j);
				printf("White WIN");
				getch();
				exit(1);
			}
		}
	}

	//흑색 승//
	for(j=0; j<15; j++)
	{
		for(i=0;i<33;i++)
		{
			if(stone[i][j]==2&&stone[i+2][j]==2&&stone[i+4][j]==2&&stone[i+6][j]==2&&stone[i+8][j]==2)
			{
				i=4;
				j=20;
				zgotoxy(i, j);
				printf("Black WIN");
				getch();
				exit(1);
			}
		}
	}

	for(i=0; i<33; i++)
	{
		for(j=0;j<15;j++)
		{
			if(stone[i][j]==2&&stone[i][j+1]==2&&stone[i][j+2]==2&&stone[i][j+3]==2&&stone[i][j+4]==2)
			{
				i=4;
				j=20;
				zgotoxy(i, j);
				printf("Black WIN");
				getch();
				exit(1);
			}
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////
void status(int player, int x, int y)
{
	int rex=x;
	int rey=y;
	if(player==0)
	{
		x=4;
		y=22;
		zgotoxy(x, y);
		printf("Turn: ○     횟수:%d", count);
	}
	else if(player==1)
	{
		x=4;
		y=22;
		zgotoxy(x,y);
		printf("Turn: ●     횟수:%d", count);
	}
		zgotoxy(rex, rey);
	}
//////////////////////////////////////////////////////////////////////////////////////////////
int menu()
{
	//커서를 숨김
	SetCursor(0);
	printf("\n\n");
	printf("    ●●●      ●●●●\n");
	printf("   ●    ●     ●    ●\n");
	printf("   ●    ●     ●●●●\n");
	printf("    ●●●         ●\n");
	printf("      ●     ●●●●●●●\n");   
	printf("      ●\n");
	printf(" ●●●●●●   ●●●●\n");
	printf("                      ●\n");
	printf("   Start\n   How to play\n   Exit");
	mx=1;
	my=10;
	mgotoxy(mx, my);
	printf("▶");

	while(1)
	{
	if(_kbhit())
	{
		nKey=_getch();
		movexy(nKey);
	}
	}
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////
void help()
{
	printf("\n\n\n\n조작키: 방향키+Enter\n바둑돌을 먼저 5개를 나란히 놓으면 승리합니다");
	printf("\n\n\n\n\n돌아가려면 'Enter'를 눌러주세요");

}
//////////////////////////////////////////////////////////////////////////////////////////////
void mgotoxy(int x, int y)
{
	COORD Pos={x, y};
	SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	mx=x;
	my=y;
}
//////////////////////////////////////////////////////////////////////////////////////////////
void movexy(char nkey)
{
	int px=mx;
	int py=my;
	mgotoxy(px, py);
	printf("  ");
	switch(nkey)
	{
		case ENTER:
			if(py==10)
			{
				system("cls");
				mgotoxy(mx, my);
				printf("   일인용\n    이인용");
				mgotoxy(mx, my);
	            printf("▶");
				menu_oneortwo(mx, my);
				exit(1);
			}
			//도움말//
			else if(py==11)
			{
				system("cls");
				help();
			while(1)
			{
				nKey=_getch();
				if(nKey==ENTER)
				{
					system("cls");
					menu();
				}
			}
			}
			//나가기//
			else
			{
				system("cls");
				exit(0);
			}
			break;
		case UP:
			if(py!=10)
				py--;
			else if(py==10)
				py=12;
			mgotoxy(px, py);
			printf("▶");
			break;
		case DOWN:
			if(py!=12)
				py++;
			else if(py==12)
				py=10;
			mgotoxy(px, py);
			printf("▶");
			break;
	}

}
//////////////////////////////////////////////////////////////////////////////////////////////
void menu_oneortwo(int x, int y)
{
	int k;
	x=1;
	y=10;
	k=1;
	while(k==1)
	{
		mgotoxy(x, y);
									
		nKey_1=_getch();
		switch(nKey_1)
		{
		case ENTER:
				if(y==10)
					{system("cls");
					 //1인용시작//
					play1();
					}
				else if(y==11)
				{
					system("cls");
					//2인용시작//
					play2();
				}
				k=2;
				break;
		case UP:
			if(y!=10)
				y--;
			else if(y==10)
				y=11;
			printf(" ");
			mgotoxy(x, y);
			printf("▶");
			break;
		case DOWN:
			if(y!=11)
				y++;
			else if(y==11)
				y=10;
			printf(" ");
			mgotoxy(x, y);
			printf("▶");
			break;
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
void Back()
{
	int i,j;
	
	for(i=0;i<15;i++)
		for(j=0;j<15;j++)
			strcpy(back[i][j],background);

}
//////////////////////////////////////////////////////////////////////////////////////////////
void play1()
{

	printf("1p 이름: ");
	scanf("%s",p1);

 	
	Back();
	printf_back();
	
	while(1)
	{
		Black();
		judge_black();
		
		if(judge==1)
			break;

		White();
		judge_white();
		
		if(judge==1)
			break;
	}
	system("cls");
	printf_back();
	printf("\n");
	system("pause");

}
//////////////////////////////////////////////////////////////////////////////////////////////
void printf_back()
{
	int i,j;
	system("cls");
	printf("┏┯┯┯┯┯┯┯┯┯┯┯┯┯┯┯┓");
	for(i=0;i<15;i++)
	{
		printf("\n");
		printf("┠");
		for(j=0;j<15;j++)
			printf("%s",back[i][j]);
		printf("┨");
	}
	printf("\n┗┷┷┷┷┷┷┷┷┷┷┷┷┷┷┷┛\n\n");

	printf("     %s: %d\n\n",p1,count_black);
	printf("      컴퓨터 : %d",count_white);
}
//////////////////////////////////////////////////////////////////////////////////////////////

void gotoxy(int x, int y)
{
	COORD Pos={x, y};
	SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	fx=x;
	fy=y;
}

//////////////////////////////////////////////////////////////////////////////////////////////
void Black()//my stone
{
	int x,y,move;
	char save[3];

	x=a;
	y=b;

	strcpy(save,back[x][y]);
	strcpy(back[x][y],star);
	printf_back();	
	
	
	

	while(1)
	{
		
		move=getch();

		switch(move)
		{
		case UP:
		{	if(x!=0)
			{	
				strcpy(back[x][y],save);
				strcpy(save,back[x-1][y]);
				gotoxy(fx,fy);
				printf("%s",back[x][y]);
				x--;
				fy--;
				gotoxy(fx,fy);
				printf("%s",star);
			}
			break;
		}//up
		case LEFT:
		{	if(y!=0)
			{
				strcpy(back[x][y],save);
				strcpy(save,back[x][y-1]);
				gotoxy(fx,fy);
				printf("%s",back[x][y]);
				y--;
				fx-=2;
				gotoxy(fx,fy);
				printf("%s",star);
			}
			break;
		}//left
		case RIGHT:
		{	if(y!=14)
			{
				strcpy(back[x][y],save);
				strcpy(save,back[x][y+1]);
				gotoxy(fx,fy);
				printf("%s",back[x][y]);
				y++;
				fx+=2;
				gotoxy(fx,fy);
				printf("%s",star);
				
			}
			break;
		}//right
		case DOWN:
		{	if(x!=14)
			{
				strcpy(back[x][y],save);
				strcpy(save,back[x+1][y]);
				gotoxy(fx,fy);
				printf("%s",back[x][y]);
				x++;
				fy++;
				gotoxy(fx,fy);
				printf("%s",star);
				
			}
			break;
		}//down
		case '\r':
			{
				if(strcmp(back[x][y],background)==0)
				{
					strcpy(back[x][y],"●");
					goto leap;
				}
	
				else
				{
					system("cls");
					printf("둘 수 없는 곳입니다.\n");
					system("pause");
					printf_back();
				}
				break;
			}//enter is end
		}
	}//black stone is move
leap:;

	  
    count_black++;
    a=x;
    b=y;
	
	
}
//////////////////////////////////////////////////////////////////////////////////////////////
void White()
{
 	int x,y,i,m,n;
//////////////////////////////////////////////최우선 공격///////////////////////////////////////////////////////////// 
	for(x=0;x<15;x++)
		for(y=0;y<15;y++)////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////양쪽이 뚫려있는경우로 수정
		{
			if(strcmp(back[x][y],white)==0)
			{
				if(strcmp(back[x-1][y],background)==0 && strcmp(back[x+1][y],white)==0 && strcmp(back[x+2][y],white)==0 && strcmp(back[x+3][y],white)==0 && strcmp(back[x+4][y],background)==0)
				{
					i=rand()%2;

					if(i==0)
					{
						strcpy(back[x-1][y],white);
						x--;
						goto jump;
					}
				

					else
					{
						strcpy(back[x+4][y],white);
						x+=4;
						goto jump;
					}
				}
				//세로

				else if(strcmp(back[x][y-1],background)==0 && strcmp(back[x][y+1],white)==0 && strcmp(back[x][y+2],white)==0 && strcmp(back[x][y+3],white)==0 && strcmp(back[x][y+4],background)==0)
				{
					i=rand()%2;

					if(i==0)
					{
						strcpy(back[x][y-1],white);
						y--;
						goto jump;
					}
					
					else
					{
						strcpy(back[x][y+4],white);
						y+=4;
						goto jump;
					}	
				}//가로

				else if(strcmp(back[x-1][y-1],background)==0 && strcmp(back[x+1][y+1],white)==0 && strcmp(back[x+2][y+2],white)==0 && strcmp(back[x+3][y+3],white)==0 && strcmp(back[x+4][y+4],background)==0)
				{
					i=rand()%2;

					if(i==0)
					{
						strcpy(back[x-1][y-1],white);
						x--;
						y--;
						goto jump;
					}

					else
					{
						strcpy(back[x+4][y+4],white);
						x+=4;
						y+=4;
						goto jump;
					}
				}//오른쪽 아래 대각선

				else if(strcmp(back[x-1][y+1],background)==0 && strcmp(back[x+1][y-1],white)==0 && strcmp(back[x+2][y-2],white)==0 && strcmp(back[x+3][y-3],white)==0 && strcmp(back[x+4][y-4],background)==0)
				{
					i=rand()%2;

					if(i==0)
					{
						strcpy(back[x-1][y+1],white);
						x--;
						y++;
						goto jump;
					}

					else
					{
						strcpy(back[x+4][y-4],white);
						x+=4;
						y-=4;
						goto jump;
					}
				}//왼쪽 아래 대각선
			}
		}//횐돌 4개 끝
		
	for(x=0;x<15;x++)//흰돌 3+1
		for(y=0;y<15;y++)
		{
			if(strcmp(back[x][y],white)==0)
			{
				if(x<10 && strcmp(back[x-1][y],background)==0 && strcmp(back[x+1][y],white)==0 && strcmp(back[x+2][y],white)==0 && strcmp(back[x+3][y],background)==0 && strcmp(back[x+4][y],white)==0 && strcmp(back[x+5][y],background)==0)
				{
					strcpy(back[x+3][y],white);
					x+=3;
					goto jump;
				}//가로

				else if(y<11 && strcmp(back[x][y+1],white)==0 && strcmp(back[x][y+2],white)==0 && strcmp(back[x][y+3],background)==0 && strcmp(back[x][y+4],white)==0)
				{
					strcpy(back[x][y+3],white);
					y+=3;
					goto jump;
				}//세로
				
				else if(x<11 && y<11 && strcmp(back[x+1][y+1],white)==0 && strcmp(back[x+2][y+2],white)==0 && strcmp(back[x+3][y+3],background)==0 && strcmp(back[x+4][y+4],white)==0)
				{
					strcpy(back[x+3][y+3],white);
					x+=3;
					y+=3;
					goto jump;
				}//오른쪽 아래 대각선

				else if(x<11 && y>4 && strcmp(back[x+1][y-1],white)==0 && strcmp(back[x+2][y-2],white)==0 && strcmp(back[x+3][y-3],background)==0 && strcmp(back[x+4][y-4],white)==0)
				{
					strcpy(back[x+3][y-3],white);
					x+=3;
					y-=3;
					goto jump;
				}//왼쪽 아래 대각선
			}
		}//흰돌 3+1 끝

	for(x=0;x<15;x++)//흰돌 2+2
		for(y=0;y<15;y++)
		{
			if(strcmp(back[x][y],white)==0)
			{
				if(x<11 && strcmp(back[x+1][y],white)==0 && strcmp(back[x+2][y],background)==0 && strcmp(back[x+3][y],white)==0 && strcmp(back[x+4][y],white)==0)
				{
					strcpy(back[x+2][y],white);
					x+=2;
					goto jump;
				}//가로

				else if(y<11 && strcmp(back[x][y+1],white)==0 && strcmp(back[x][y+2],background)==0 && strcmp(back[x][y+3],white)==0 && strcmp(back[x][y+4],white)==0)
				{
					strcpy(back[x][y+2],white);
					y+=2;
					goto jump;
				}//세로
				
				else if(x<11 && y<11 && strcmp(back[x+1][y+1],white)==0 && strcmp(back[x+2][y+2],background)==0 && strcmp(back[x+3][y+3],white)==0 && strcmp(back[x+4][y+4],white)==0)
				{
					strcpy(back[x+2][y+2],white);
					x+=2;
					y+=2;
					goto jump;
				}//오른쪽 아래 대각선

				else if(x<11 && y>4 && strcmp(back[x+1][y-1],white)==0 && strcmp(back[x+2][y-2],background)==0 && strcmp(back[x+3][y-3],white)==0 && strcmp(back[x+4][y-4],white)==0)
				{
					strcpy(back[x+2][y-2],white);
					x+=2;
					y-=2;
					goto jump;
				}//왼쪽 아래 대각선
			}
		}//흰돌 2+2 끝

		
	for(x=0;x<15;x++)//흰돌 1+3
		for(y=0;y<15;y++)
		{
			if(strcmp(back[x][y],white)==0)
			{
				if(x<11 && strcmp(back[x+1][y],background)==0 && strcmp(back[x+2][y],white)==0 && strcmp(back[x+3][y],white)==0 && strcmp(back[x+4][y],white)==0)
				{
					strcpy(back[x+1][y],white);
					x++;
					goto jump;
				}//가로

				else if(y<11 && strcmp(back[x][y+1],background)==0 && strcmp(back[x][y+2],white)==0 && strcmp(back[x][y+3],white)==0 && strcmp(back[x][y+4],white)==0)
				{
					strcpy(back[x][y+1],white);
					y++;
					goto jump;
				}//세로
				
				else if(x<11 && y<11 && strcmp(back[x+1][y+1],background)==0 && strcmp(back[x+2][y+2],white)==0 && strcmp(back[x+3][y+3],white)==0 && strcmp(back[x+4][y+4],white)==0)
				{
					strcpy(back[x+1][y+1],white);
					x++;
					y++;
					goto jump;
				}//오른쪽 아래 대각선

				else if(x<11 && y>4 && strcmp(back[x+1][y-1],background)==0 && strcmp(back[x+2][y-2],white)==0 && strcmp(back[x+3][y-3],white)==0 && strcmp(back[x+4][y-4],white)==0)
				{
					strcpy(back[x+1][y-1],white);
					x++;
					y--;
					goto jump;
				}//왼쪽 아래 대각선
			}
		}//흰돌 1+3 끝

	///////////////////////////////////////////////////////방어//////////////////////////////////////////////////////////////////////////
 	for(x=0;x<15;x++)
 	    for(y=0;y<15;y++)
 	    {
            if(strcmp(back[x][y],black)==0) // 4개짜리 흑돌
 	        {
				if(strcmp(back[x+1][y],black)==0 && strcmp(back[x+2][y],black)==0 && strcmp(back[x+3][y],black)==0)
                {
	 				i=rand()%2;
	 	    
	 	            if(i==0)
                    {
			            if(x>1 && strcmp(back[x-1][y],background)==0)
       		            {
				            strcpy(back[x-1][y],white);
				            x--;
							goto jump;
                        }

			            else if(x<11 && strcmp(back[x+4][y],background)==0)
			            {
				            strcpy(back[x+4][y],white);
				            x+=4;
							goto jump;
	                    }
	                }

           			else
                    {
			            if(x<11 && strcmp(back[x+4][y],background)==0)
			            {
		             		strcpy(back[x+4][y],white);
				            x+=4;
							goto jump;
                        }
			            else if(x>1 && strcmp(back[x-1][y],background)==0)
			            {
		             		strcpy(back[x-1][y],white);
				            x--;
							goto jump;
                        }
                    }					
          		}//세로
		

	          	else if(strcmp(back[x][y+1],black)==0 && strcmp(back[x][y+2],black)==0 && strcmp(back[x][y+3],black)==0)
		        {
                   i=rand()%2;
	 	    
	 	           if(i==0)
	 	           {
				       if(y>1 && strcmp(back[x][y-1],background)==0)
       		           {
				            strcpy(back[x][y-1],white);
					        y--;
							goto jump;
                       }

			           else if(y<11 && strcmp(back[x][y+4],background)==0)
				       {
				         	strcpy(back[x][y+4],white);
					        y+=4;
							goto jump;
			           }
			       }

			       else
		       	   {
          		       if(y<11 && strcmp(back[x][y+4],background)==0)
				       {
						    strcpy(back[x][y+4],white);
			 				y+=4;
							goto jump;
                       }
					   else if(y>1 && strcmp(back[x][y-1],background)==0)
   	  				   {
							strcpy(back[x][y-1],white);
							y--;
							goto jump;
					   }
				   }
				}//가로					
			 
				else if(strcmp(back[x+1][y+1],black)==0 && strcmp(back[x+2][y+2],black)==0 && strcmp(back[x+3][y+3],black)==0)
				{
                    i=rand()%2;
                  
                    if(i==0)
                    {
                        if(x>1 && y>1 && strcmp(back[x-1][y-1],background)==0)
                        {
                             strcpy(back[x-1][y-1],white);
                             x--;
                             y--;
							 goto jump;
                        }
                        
                        else if(x<11 && y<11 && strcmp(back[x+4][y+4],background)==0)
                        {
                             strcpy(back[x+4][y+4],white);
                             x+=4;
                             y+=4;
							 goto jump;
                        }
                    }
                    
                    else
                    {
                        if(x<11 && y<11 && strcmp(back[x+4][y+4],background)==0)
                        {
                             strcpy(back[x+4][y+4],white);
                             x+=4;
                             y+=4;
							 goto jump;
                        }
                        
                        else if(x>1 && y>1 && strcmp(back[x-1][y-1],background)==0)
                        {
                             strcpy(back[x-1][y-1],white);
                             x--;
                             y--;
						  	 goto jump;
                        }    
                    }
                }//오른쪽 아래 대각선 
                
                else if(strcmp(back[x+1][y-1],black)==0 && strcmp(back[x+2][y-2],black)==0 && strcmp(back[x+3][y-3],black)==0)
                {
                     i=rand()%2;
                     
                     if(i==0)
                     {
                         if(x<1 && y<14 && strcmp(back[x-1][y+1],background)==0)
                         {
                             strcpy(back[x-1][y+1],white);
                             x--;
                             y++;
							 goto jump;
                         }
                         
                         else if(x<11 && y>4 && strcmp(back[x+4][y-4],background)==0)
                         {
                              strcpy(back[x+4][y-4],white);
                              x+=4;
                              y-=4;
							  goto jump;
                         }
                     }
                     
                     else
                     {
                         if(x<11 && y>4 && strcmp(back[x+4][y-4],background)==0)
                         {
                             strcpy(back[x+4][y-4],white);
                             x+=4;
                             y-=4;
							 goto jump;
                         }
                         
                         else if(x>1 && y<14 && strcmp(back[x-1][y+1],background)==0)
                         {
                              strcpy(back[x-1][y+1],white);
                              x--;
                              y++;
							  goto jump;
                         }
                     }//왼쪽 아래 대각선 
                }
			}
		}//흑돌 4개 끝


	for(x=0;x<15;x++)//흑돌 3+1
		for(y=0;y<15;y++)
		{
			if(strcmp(back[x][y],black)==0)
			{
				if(x<11 && strcmp(back[x+1][y],black)==0 && strcmp(back[x+2][y],black)==0 && strcmp(back[x+3][y],background)==0 && strcmp(back[x+4][y],black)==0)
				{
					strcpy(back[x+3][y],white);
					x+=3;
					goto jump;
				}//가로

				else if(y<11 && strcmp(back[x][y+1],black)==0 && strcmp(back[x][y+2],black)==0 && strcmp(back[x][y+3],background)==0 && strcmp(back[x][y+4],black)==0)
				{
					strcpy(back[x][y+3],white);
					y+=3;
					goto jump;
				}//세로
				
				else if(x<11 && y<11 && strcmp(back[x+1][y+1],black)==0 && strcmp(back[x+2][y+2],black)==0 && strcmp(back[x+3][y+3],background)==0 && strcmp(back[x+4][y+4],black)==0)
				{
					strcpy(back[x+3][y+3],white);
					x+=3;
					y+=3;
					goto jump;
				}//오른쪽 아래 대각선

				else if(x<11 && y>4 && strcmp(back[x+1][y-1],black)==0 && strcmp(back[x+2][y-2],black)==0 && strcmp(back[x+3][y-3],background)==0 && strcmp(back[x+4][y-4],black)==0)
				{
					strcpy(back[x+3][y-3],white);
					x+=3;
					y-=3;
					goto jump;
				}//왼쪽 아래 대각선
			}
		}//흑돌 3+1 끝

	for(x=0;x<15;x++)//흑돌 2+2
		for(y=0;y<15;y++)
		{
			if(strcmp(back[x][y],black)==0)
			{
				if(x>11 && strcmp(back[x+1][y],black)==0 && strcmp(back[x+2][y],background)==0 && strcmp(back[x+3][y],black)==0 && strcmp(back[x+4][y],black)==0)
				{
					strcpy(back[x+2][y],white);
					x+=2;
					goto jump;
				}//가로

				else if(y<11 && strcmp(back[x][y+1],black)==0 && strcmp(back[x][y+2],background)==0 && strcmp(back[x][y+3],black)==0 && strcmp(back[x][y+4],black)==0)
				{
					strcpy(back[x][y+2],white);
					y+=2;
					goto jump;
				}//세로
				
				else if(x<11 && y<11 && strcmp(back[x+1][y+1],black)==0 && strcmp(back[x+2][y+2],background)==0 && strcmp(back[x+3][y+3],black)==0 && strcmp(back[x+4][y+4],black)==0)
				{
					strcpy(back[x+2][y+2],white);
					x+=2;
					y+=2;
					goto jump;
				}//오른쪽 아래 대각선

				else if(x<11 && y>5 && strcmp(back[x+1][y-1],black)==0 && strcmp(back[x+2][y-2],background)==0 && strcmp(back[x+3][y-3],black)==0 && strcmp(back[x+4][y-4],black)==0)
				{
					strcpy(back[x+2][y-2],white);
					x+=2;
					y-=2;
					goto jump;
				}//왼쪽 아래 대각선
			}
		}//흑돌 2+2 끝

		
	for(x=0;x<15;x++)//흑돌 1+3
		for(y=0;y<15;y++)
		{
			if(strcmp(back[x][y],black)==0)
			{
				if(x<11 && strcmp(back[x+1][y],background)==0 && strcmp(back[x+2][y],black)==0 && strcmp(back[x+3][y],black)==0 && strcmp(back[x+4][y],black)==0)
				{
					strcpy(back[x+1][y],white);
					x++;
					goto jump;
				}//가로

				else if(y<11 && strcmp(back[x][y+1],background)==0 && strcmp(back[x][y+2],black)==0 && strcmp(back[x][y+3],black)==0 && strcmp(back[x][y+4],black)==0)
				{
					strcpy(back[x][y+1],white);
					y++;
					goto jump;
				}//세로
				
				else if(x<11 && y<11 && strcmp(back[x+1][y+1],background)==0 && strcmp(back[x+2][y+2],black)==0 && strcmp(back[x+3][y+3],black)==0 && strcmp(back[x+4][y+4],black)==0)
				{
					strcpy(back[x+1][y+1],white);
					x++;
					y++;
					goto jump;
				}//오른쪽 아래 대각선

				else if(x<11 && y>4 && strcmp(back[x+1][y-1],background)==0 && strcmp(back[x+2][y-2],black)==0 && strcmp(back[x+3][y-3],black)==0 && strcmp(back[x+4][y-4],black)==0)
				{
					strcpy(back[x+1][y-1],white);
					x++;
					y--;
					goto jump;
				}//왼쪽 아래 대각선
			}
		}//흑돌 1+3 끝

 	for(x=0;x<15;x++)
 	    for(y=0;y<15;y++)
 	    {
            if(strcmp(back[x][y],black)==0) // 3개짜리 흑돌
 	        {
				if(strcmp(back[x+1][y],black)==0 && strcmp(back[x+2][y],black)==0)
                {
	 				i=rand()%2;
	 	    
	 	            if(i==0)
                    {
			            if(x>1 && strcmp(back[x-1][y],background)==0)
       		            {
				            strcpy(back[x-1][y],white);
				            x--;
							goto jump;
                        }

			            else if(x<12 && strcmp(back[x+3][y],background)==0)
			            {
				            strcpy(back[x+3][y],white);
				            x+=3;
							goto jump;
	                    }
	                }

           			else
                    {
			            if(x<12 && strcmp(back[x+3][y],background)==0)
			            {
		             		strcpy(back[x+3][y],white);
				            x+=3;
							goto jump;
                        }
			            else if(x>1 && strcmp(back[x-1][y],background)==0)
			            {
		             		strcpy(back[x-1][y],white);
				            x--;
							goto jump;
                        }
                    }					
          		}//세로
		

	          	else if(strcmp(back[x][y+1],black)==0 && strcmp(back[x][y+2],black)==0)
		        {
                   i=rand()%2;
	 	    
	 	           if(i==0)
	 	           {
				       if(y>1 && strcmp(back[x][y-1],background)==0)
       		           {
				           strcpy(back[x][y-1],white);
					       y--;
						   goto jump;
                       }

			           else if(y<12 && strcmp(back[x][y+3],background)==0)
				       {
				         	strcpy(back[x][y+3],white);
					        y+=3;
							goto jump;
			           }
			       }

			       else
		       	   {
          		       if(y<12 && strcmp(back[x][y+3],background)==0)
				       {
                           strcpy(back[x][y+3],white);
			 		       y+=3;
						   goto jump;
                       }
					   else if(y>1 && strcmp(back[x][y-1],background)==0)
   	  				   {
							strcpy(back[x][y-1],white);
							y--;
							goto jump;
					   }
				   }
				}//가로					
			 
				else if(strcmp(back[x+1][y+1],black)==0 && strcmp(back[x+2][y+2],black)==0)
				{
                    i=rand()%2;
                  
                    if(i==0)
                    {
                        if(x>1 && y>1 && strcmp(back[x-1][y-1],background)==0)
                        {
                            strcpy(back[x-1][y-1],white);
                            x--;
                            y--;
							goto jump;
                        }
                        
                        else if(x<12 && y<12 && strcmp(back[x+3][y+3],background)==0)
                        {
                             strcpy(back[x+3][y+3],white);
                             x+=3;
                             y+=3;
							 goto jump;
                        }
                    }
                    
                    else
                    {
                        if(x<12 && y<12 && strcmp(back[x+3][y+3],background)==0)
                        {
                             strcpy(back[x+3][y+3],white);
                             x+=3;
                             y+=3;
							 goto jump;
                        }
                        
                        else if(x>1 && y>1 && strcmp(back[x-1][y-1],background)==0)
                        {
                            strcpy(back[x-1][y-1],white);
                            x--;
                            y--;
							goto jump;
                        }    
                    }
                }//오른쪽 아래 대각선 
                
                else if(strcmp(back[x+1][y-1],black)==0 && strcmp(back[x+2][y-2],black)==0)
                {
                     i=rand()%2;
                     
                     if(i==0)
                     {
                         if(x>1 && y<14 && strcmp(back[x-1][y+1],background)==0)
                         {
                             strcpy(back[x-1][y+1],white);
                             x--;
                             y++;
							 goto jump;
                         }
                         
                         else if(x<12 && y>3 && strcmp(back[x+3][y-3],background)==0)
                         {
                              strcpy(back[x+3][y-3],white);
                              x+=3;
                              y-=3;
							  goto jump;
                         }
                     }
                     
                     else
                     {
                         if(x<12 && y>3 && strcmp(back[x+3][y-3],background)==0)
                         {
                             strcpy(back[x+3][y-3],white);
                             x+=3;
                             y-=3;
							 goto jump;
                         }
                         
                         else if(x>1 && y<14 && strcmp(back[x-1][y+1],background)==0)
                         {
                              strcpy(back[x-1][y+1],white);
                              x--;
                              y++;
							  goto jump;
                         }
                     }//왼쪽 아래 대각선 
                }
			}
		}//흑돌 3개 끝

	for(x=0;x<15;x++)//흑돌 2+1
		for(y=0;y<15;y++)
		{
			if(strcmp(back[x][y],black)==0)
			{
				if(x<12 && strcmp(back[x+1][y],black)==0 && strcmp(back[x+2][y],background)==0 && strcmp(back[x+3][y],black)==0)
				{
					strcpy(back[x+2][y],white);
					x-=2;
					goto jump;
				}//세로

				else if(y<12 && strcmp(back[x][y+1],black)==0 && strcmp(back[x][y+2],background)==0 && strcmp(back[x][y+3],black)==0)
				{
					strcpy(back[x][y+2],white);
					y-=2;
					goto jump;
				}//가로

				else if(x<12 && y<12 && strcmp(back[x+1][y+1],black)==0 && strcmp(back[x+2][y+2],background)==0 && strcmp(back[x+3][y+3],black)==0)
				{
					strcpy(back[x+2][y+2],white);
					x+=2;
					y+=2;
					goto jump;
				}//오른쪽 아래 대각선

				else if(x<12 && y>3 && strcmp(back[x+1][y-1],black)==0 && strcmp(back[x+2][y-2],background)==0 && strcmp(back[x+3][y-3],black)==0)
				{
					strcpy(back[x+2][y-2],white);
					x+=2;
					y-=2;
					goto jump;
				}//오른쪽 아래 대각선
			}
		}//흑돌 1+2 끝

		
	for(x=0;x<15;x++)//흑돌 1+2
		for(y=0;y<15;y++)
		{
			if(strcmp(back[x][y],black)==0)
			{
				if(x<12 && strcmp(back[x+1][y],background)==0 && strcmp(back[x+2][y],black)==0 && strcmp(back[x+3][y],black)==0)
				{
					strcpy(back[x+1][y],white);
					x--;
					goto jump;
				}//세로

				else if(y<12 && strcmp(back[x][y+1],background)==0 && strcmp(back[x][y+2],black)==0 && strcmp(back[x][y+3],black)==0)
				{
					strcpy(back[x][y+1],white);
					y--;
					goto jump;
				}//가로

				else if(x<12 && y<12 && strcmp(back[x+1][y+1],background)==0 && strcmp(back[x+2][y+2],black)==0 && strcmp(back[x+3][y+3],black)==0)
				{
					strcpy(back[x+1][y+1],white);
					x++;
					y++;
					goto jump;
				}//오른쪽 아래 대각선

				else if(x<12 && y>3 && strcmp(back[x+1][y-1],background)==0 && strcmp(back[x+2][y-2],black)==0 && strcmp(back[x+3][y-3],black)==0)
				{
					strcpy(back[x+1][y-1],white);
					x++;
					y--;
					goto jump;
				}//오른쪽 아래 대각선
			}
		}//흑돌 1+2 끝

//////////////////////////////////////공격////////////////////////////////////////////////////

	for(x=0;x<15;x++)
		for(y=0;y<15;y++)
		{
			if(strcmp(back[x][y],white)==0)
			{
				if(strcmp(back[x+1][y],white)==0 && strcmp(back[x+2][y],white)==0 && strcmp(back[x+3][y],white)==0)
				{
					i=rand()%2;

					if(i==0)
					{
						if(x>1 && strcmp(back[x-1][y],background)==0)
						{
							strcpy(back[x-1][y],white);
							x--;
							goto jump;
						}

						else if(x<11 && strcmp(back[x+4][y],background)==0)
						{
							strcpy(back[x+4][y],white);
							x+=4;
							goto jump;
						}
					}

					else
					{
						if(x<11 && strcmp(back[x+4][y],background)==0)
						{
							strcpy(back[x+4][y],white);
							x+=4;
							goto jump;
						}

						else if(x>1 && strcmp(back[x-1][y],background)==0)
						{
							strcpy(back[x-1][y],white);
							x--;
							goto jump;
						}
					}
				}//세로

				else if(strcmp(back[x][y+1],white)==0 && strcmp(back[x][y+2],white)==0 && strcmp(back[x][y+3],white)==0)
				{
					i=rand()%2;

					if(i==0)
					{
						if(y>1 && strcmp(back[x][y-1],background)==0)
						{
							strcpy(back[x][y-1],white);
							y--;
							goto jump;
						}

						else if(y<11 && strcmp(back[x][y+4],background)==0)
						{
							strcpy(back[x][y+4],white);
							y+=4;
							goto jump;
						}
					}

					else
					{
						if(y<11 && strcmp(back[x][y+4],background)==0)
						{
							strcpy(back[x][y+4],white);
							y+=4;
							goto jump;
						}

						else if(y>1 && strcmp(back[x][y-1],background)==0)
						{
							strcpy(back[x][y-1],white);
							y--;
							goto jump;
						}
					}
				}//가로

				else if(strcmp(back[x+1][y+1],white)==0 && strcmp(back[x+2][y+2],white)==0 && strcmp(back[x+3][y+3],white)==0)
				{
					i=rand()%2;

					if(i==0)
					{
						if(x>1 && y>1 && strcmp(back[x-1][y-1],background)==0)
						{
							strcpy(back[x-1][y-1],white);
							x--;
							y--;
							goto jump;
						}

						else if(x<11 && y<11 && strcmp(back[x+4][y+4],background)==0)
						{
							strcpy(back[x+4][y+4],white);
							x+=4;
							y+=4;
							goto jump;
						}
					}

					else
					{
						if(x<11 && y<11 && strcmp(back[x+4][y+4],background)==0)
						{
							strcpy(back[x+4][y+4],white);
							x+=4;
							y+=4;
							goto jump;
						}

						else if(x>1 && y>1 && strcmp(back[x-1][y-1],background)==0)
						{
							strcpy(back[x-1][y-1],white);
							x--;
							y--;
							goto jump;
						}
					}
				}//오른쪽 아래 대각선

				else if(strcmp(back[x+1][y-1],white)==0 && strcmp(back[x+2][y-2],white)==0 && strcmp(back[x+3][y-3],white)==0)
				{
					i=rand()%2;

					if(i==0)
					{
						if(x>1 && y<14 && strcmp(back[x-1][y+1],background)==0)
						{
							strcpy(back[x-1][y+1],white);
							x--;
							y++;
							goto jump;
						}

						else if(x<11 && y>4 && strcmp(back[x+4][y-4],background)==0)
						{
							strcpy(back[x+4][y-4],white);
							x+=4;
							y-=4;
							goto jump;
						}
					}

					else
					{
						if(x<11 && y>4 && strcmp(back[x+4][y-4],background)==0)
						{
							strcpy(back[x+4][y-4],white);
							x+=4;
							y-=4;
							goto jump;
						}

						else if(x>1 && y<14 && strcmp(back[x-1][y+1],background)==0)
						{
							strcpy(back[x-1][y+1],white);
							x--;
							y++;
							goto jump;
						}
					}
				}//왼쪽 아래 대각선
			}
		}//횐돌 4개 끝
		
	for(x=0;x<15;x++)//흰돌 3+1
		for(y=0;y<15;y++)
		{
			if(strcmp(back[x][y],white)==0)
			{
				if(x<11 && strcmp(back[x+1][y],white)==0 && strcmp(back[x+2][y],white)==0 && strcmp(back[x+3][y],background)==0 && strcmp(back[x+4][y],white)==0)
				{
					strcpy(back[x+3][y],white);
					x+=3;
					goto jump;
				}//가로

				else if(y<11 && strcmp(back[x][y+1],white)==0 && strcmp(back[x][y+2],white)==0 && strcmp(back[x][y+3],background)==0 && strcmp(back[x][y+4],white)==0)
				{
					strcpy(back[x][y+3],white);
					y+=3;
					goto jump;
				}//세로
				
				else if(x<11 && y<11 && strcmp(back[x+1][y+1],white)==0 && strcmp(back[x+2][y+2],white)==0 && strcmp(back[x+3][y+3],background)==0 && strcmp(back[x+4][y+4],white)==0)
				{
					strcpy(back[x+3][y+3],white);
					x+=3;
					y+=3;
					goto jump;
				}//오른쪽 아래 대각선

				else if(x<11 && y>4 && strcmp(back[x+1][y-1],white)==0 && strcmp(back[x+2][y-2],white)==0 && strcmp(back[x+3][y-3],background)==0 && strcmp(back[x+4][y-4],white)==0)
				{
					strcpy(back[x+3][y-3],white);
					x+=3;
					y-=3;
					goto jump;
				}//왼쪽 아래 대각선
			}
		}//흰돌 3+1 끝

	for(x=0;x<15;x++)//흰돌 2+2
		for(y=0;y<15;y++)
		{
			if(strcmp(back[x][y],white)==0)
			{
				if(x<11 && strcmp(back[x+1][y],white)==0 && strcmp(back[x+2][y],background)==0 && strcmp(back[x+3][y],white)==0 && strcmp(back[x+4][y],white)==0)
				{
					strcpy(back[x+2][y],white);
					x+=2;
					goto jump;
				}//가로

				else if(y<11 && strcmp(back[x][y+1],white)==0 && strcmp(back[x][y+2],background)==0 && strcmp(back[x][y+3],white)==0 && strcmp(back[x][y+4],white)==0)
				{
					strcpy(back[x][y+2],white);
					y+=2;
					goto jump;
				}//세로
				
				else if(x<11 && y<11 && strcmp(back[x+1][y+1],white)==0 && strcmp(back[x+2][y+2],background)==0 && strcmp(back[x+3][y+3],white)==0 && strcmp(back[x+4][y+4],white)==0)
				{
					strcpy(back[x+2][y+2],white);
					x+=2;
					y+=2;
					goto jump;
				}//오른쪽 아래 대각선

				else if(x<11 && y>4 && strcmp(back[x+1][y-1],white)==0 && strcmp(back[x+2][y-2],background)==0 && strcmp(back[x+3][y-3],white)==0 && strcmp(back[x+4][y-4],white)==0)
				{
					strcpy(back[x+2][y-2],white);
					x+=2;
					y-=2;
					goto jump;
				}//왼쪽 아래 대각선
			}
		}//흰돌 2+2 끝

		
	for(x=0;x<15;x++)//흰돌 1+3
		for(y=0;y<15;y++)
		{
			if(strcmp(back[x][y],white)==0)
			{
				if(x<11 && strcmp(back[x+1][y],background)==0 && strcmp(back[x+2][y],white)==0 && strcmp(back[x+3][y],white)==0 && strcmp(back[x+4][y],white)==0)
				{
					strcpy(back[x+1][y],white);
					x++;
					goto jump;
				}//가로

				else if(y<11 && strcmp(back[x][y+1],background)==0 && strcmp(back[x][y+2],white)==0 && strcmp(back[x][y+3],white)==0 && strcmp(back[x][y+4],white)==0)
				{
					strcpy(back[x][y+1],white);
					y++;
					goto jump;
				}//세로
				
				else if(x<11 && y<11 && strcmp(back[x+1][y+1],background)==0 && strcmp(back[x+2][y+2],white)==0 && strcmp(back[x+3][y+3],white)==0 && strcmp(back[x+4][y+4],white)==0)
				{
					strcpy(back[x+1][y+1],white);
					x++;
					y++;
					goto jump;
				}//오른쪽 아래 대각선

				else if(x<11 && y>4 && strcmp(back[x+1][y-1],background)==0 && strcmp(back[x+2][y-2],white)==0 && strcmp(back[x+3][y-3],white)==0 && strcmp(back[x+4][y-4],white)==0)
				{
					strcpy(back[x+1][y-1],white);
					x++;
					y--;
					goto jump;
				}//왼쪽 아래 대각선
			}
		}//흰돌 1+3 끝

	
 	for(x=0;x<15;x++)
 	    for(y=0;y<15;y++)
 	    {
            if(strcmp(back[x][y],white)==0) // 3개짜리 흰돌
 	        {
				if(strcmp(back[x+1][y],white)==0 && strcmp(back[x+2][y],white)==0)
                {
	 				i=rand()%2;
	 	    
	 	            if(i==0)
                    {
			            if(x>1 && strcmp(back[x-1][y],background)==0)
       		            {
				            strcpy(back[x-1][y],white);
				            x--;
							goto jump;
                        }

			            else if(x<12 && strcmp(back[x+3][y],background)==0)
			            {
				            strcpy(back[x+3][y],white);
				            x+=3;
							goto jump;
	                    }
	                }

           			else

                    {
			            if(x<12 && strcmp(back[x+3][y],background)==0)
			            {
		             		strcpy(back[x+3][y],white);
				            x+=3;
							goto jump;
                        }
			            else if(x>1 && strcmp(back[x-1][y],background)==0)
			            {
		             		strcpy(back[x-1][y],white);
				            x--;
							goto jump;
                        }
                    }					
          		}//세로
		

	          	else if(strcmp(back[x][y+1],white)==0 && strcmp(back[x][y+2],white)==0)
		        {
                   i=rand()%2;
	 	    
	 	           if(i==0)
	 	           {
				       if(y>1 && strcmp(back[x][y-1],background)==0)
       		           {
				           strcpy(back[x][y-1],white);
					       y--;
						   goto jump;
                       }

			           else if(y<12 && strcmp(back[x][y+3],background)==0)
				       {
				         	strcpy(back[x][y+3],white);
					        y+=3;
							goto jump;
			           }
			       }

			       else
		       	   {
          		       if(y<12 && strcmp(back[x][y+3],background)==0)
				       {
                           strcpy(back[x][y+3],white);
			 		       y+=3;
						   goto jump;
                       }
					   else if(y>1 && strcmp(back[x][y-1],background)==0)
   	  				   {
							strcpy(back[x][y-1],white);
							y--;
							goto jump;
					   }
				   }
				}//가로					
			 
				else if(strcmp(back[x+1][y+1],white)==0 && strcmp(back[x+2][y+2],white)==0)
				{
                    i=rand()%2;
                  
                    if(i==0)
                    {
                        if(x>1 && y>1 && strcmp(back[x-1][y-1],background)==0)
                        {
                            strcpy(back[x-1][y-1],white);
                            x--;
                            y--;
							goto jump;
                        }
                        
                        else if(x<12 && y<12 && strcmp(back[x+3][y+3],background)==0)
                        {
                             strcpy(back[x+3][y+3],white);
                             x+=3;
                             y+=3;
							 goto jump;
                        }
                    }
                    
                    else
                    {
                        if(x<12 && y<12 && strcmp(back[x+3][y+3],background)==0)
                        {
                             strcpy(back[x+3][y+3],white);
                             x+=3;
                             y+=3;
							 goto jump;
                        }
                        
                        else if(x>1 && y>1 && strcmp(back[x-1][y-1],background)==0)
                        {
                            strcpy(back[x-1][y-1],white);
                            x--;
                            y--;
							goto jump;
                        }    
                    }
                }//오른쪽 아래 대각선 
                
                else if(strcmp(back[x+1][y-1],white)==0 && strcmp(back[x+2][y-2],white)==0)
                {
                     i=rand()%2;
                     
                     if(i==0)
                     {
                         if(x>1 && y<14 && strcmp(back[x-1][y+1],background)==0)
                         {
                             strcpy(back[x-1][y+1],white);
                             x--;
                             y++;
							 goto jump;
                         }
                         
                         else if(x<12 && y>3 && strcmp(back[x+3][y-3],background)==0)
                         {
                              strcpy(back[x+3][y-3],white);
                              x+=3;
                              y-=3;
							  goto jump;
                         }
                     }
                     
                     else
                     {
                         if(x<12 && y>3 && strcmp(back[x+3][y-3],background)==0)
                         {
                             strcpy(back[x+3][y-3],white);
                             x+=3;
                             y-=3;
							 goto jump;
                         }
                         
                         else if(x>1 && y<14 && strcmp(back[x-1][y+1],background)==0)
                         {
                              strcpy(back[x-1][y+1],white);
                              x--;
                              y++;
							  goto jump;
                         }
                     }//왼쪽 아래 대각선 
                }
			}
		}//흰돌 3개 끝

	for(x=0;x<15;x++)//흰돌 2+1
		for(y=0;y<15;y++)
		{
			if(strcmp(back[x][y],white)==0)
			{
				if(x<12 && strcmp(back[x+1][y],white)==0 && strcmp(back[x+2][y],background)==0 && strcmp(back[x+3][y],white)==0)
				{
					strcpy(back[x+2][y],white);
					x-=2;
					goto jump;
				}//세로

				else if(y<12 && strcmp(back[x][y+1],white)==0 && strcmp(back[x][y+2],background)==0 && strcmp(back[x][y+3],white)==0)
				{
					strcpy(back[x][y+2],white);
					y-=2;
					goto jump;
				}//가로

				else if(x<12 && y<12 && strcmp(back[x+1][y+1],white)==0 && strcmp(back[x+2][y+2],background)==0 && strcmp(back[x+3][y+3],white)==0)
				{
					strcpy(back[x+2][y+2],white);
					x+=2;
					y+=2;
					goto jump;
				}//오른쪽 아래 대각선

				else if(x<12 && y>3 && strcmp(back[x+1][y-1],white)==0 && strcmp(back[x+2][y-2],background)==0 && strcmp(back[x+3][y-3],white)==0)
				{
					strcpy(back[x+2][y-2],white);
					x+=2;
					y-=2;
					goto jump;
				}//오른쪽 아래 대각선
			}
		}//흰돌 1+2 끝

		
	for(x=0;x<15;x++)//흰돌 1+2
		for(y=0;y<15;y++)
		{
			if(strcmp(back[x][y],white)==0)
			{
				if(x<12 && strcmp(back[x+1][y],background)==0 && strcmp(back[x+2][y],white)==0 && strcmp(back[x+3][y],white)==0)
				{
					strcpy(back[x+1][y],white);
					x--;
					goto jump;
				}//세로

				else if(y<12 && strcmp(back[x][y+1],background)==0 && strcmp(back[x][y+2],white)==0 && strcmp(back[x][y+3],white)==0)
				{
					strcpy(back[x][y+1],white);
					y--;
					goto jump;
				}//가로

				else if(x<12 && y<12 && strcmp(back[x+1][y+1],background)==0 && strcmp(back[x+2][y+2],white)==0 && strcmp(back[x+3][y+3],white)==0)
				{
					strcpy(back[x+1][y+1],white);
					x++;
					y++;
					goto jump;
				}//오른쪽 아래 대각선

				else if(x<12 && y>3 && strcmp(back[x+1][y-1],background)==0 && strcmp(back[x+2][y-2],white)==0 && strcmp(back[x+3][y-3],white)==0)
				{
					strcpy(back[x+1][y-1],white);
					x++;
					y--;
					goto jump;
				}//오른쪽 아래 대각선
			}
		}//흰돌 1+2 끝

	for(x=0;x<15;x++)//흰돌 2개
		for(y=0;y<15;y++)
		{
			if(strcmp(back[x][y],white)==0)
			{
				if(strcmp(back[x+1][y],white)==0)
				{
					i=rand()%2;

					if(i==0)
					{
						if(x>1 && strcmp(back[x-1][y],background)==0)
						{
							strcpy(back[x-1][y],white);
							x--;
							goto jump;
						}
						
						else if(x<13 && strcmp(back[x+2][y],background)==0)
						{
							strcpy(back[x+2][y],white);
							x+=2;
							goto jump;
						}
					}

					else
					{
						if(x<13 && strcmp(back[x+2][y],background)==0)
						{
							strcpy(back[x+2][y],white);
							x+=2;
							goto jump;
						}

						else if(x>1 && strcmp(back[x-1][y],background)==0)
						{
							strcpy(back[x-1][y],white);
							x--;
							goto jump;
						}
					}
				}//세로

				else if(strcmp(back[x][y+1],white)==0)
				{
					i=rand()%2;
					
					if(i==0)
					{
						if(y>1 && strcmp(back[x][y-1],background)==0)
						{
							strcpy(back[x][y-1],white);
							y--;
							goto jump;
						}

						else if(y<13 && strcmp(back[x][y+2],background)==0)
						{
							strcpy(back[x][y+2],white);
							y+=2;
							goto jump;
						}
					}

					else
					{
						if(y<13 && strcmp(back[x][y+2],background)==0)
						{
							strcpy(back[x][y+2],white);
							y+=2;
							goto jump;
						}

						else if(y>1 && strcmp(back[x][y-1],background)==0)
						{
							strcpy(back[x][y-1],white);
							y--;
							goto jump;
						}
					}
				}//가로

				else if(strcmp(back[x+1][y+1],white)==0)
				{
					i=rand()%2;

					if(i==0)
					{
						if(x>1 && y>1 && strcmp(back[x-1][y-1],background)==0)
						{
							strcpy(back[x-1][y-1],white);
							x--;
							y--;
							goto jump;
						}

						else if(x<13 && y<13 && strcmp(back[x+2][y+2],background)==0)
						{
							strcpy(back[x+2][y+2],white);
							x+=2;
							y+=2;
							goto jump;
						}
					}
					
					else 
					{
						if(x<13 && y<13 && strcmp(back[x+2][y+2],background)==0)
						{
							strcpy(back[x+2][y+2],white);
							x+=2;
							y+=2;
							goto jump;
						}

						else if(x>1 && y>1 && strcmp(back[x-1][y-1],background)==0)
						{
							strcpy(back[x-1][y-1],white);
							x--;
							y--;
							goto jump;
						}
					}
				}//오른쪽 아래 대각선

				else if(strcmp(back[x+1][y-1],white)==0)
				{
					i=rand()%2;

					if(i==0)
					{
						if(x>1 && y<14 && strcmp(back[x-1][y+1],background)==0)
						{
							strcpy(back[x-1][y+1],white);
							x--;
							y++;
							goto jump;
						}

						else if(x<13 && y>2 && strcmp(back[x+2][y-2],background)==0)
						{
							strcpy(back[x+2][y-2],white);
							x+=2;
							y-=2;
							goto jump;
						}
					}

					else
					{
						if(x<13 && y>2 && strcmp(back[x+2][y-2],background)==0)
						{
							strcpy(back[x+2][y-2],white);
							x+=2;
							y-=2;
							goto jump;
						}

						else if(x>1 && y<14 && strcmp(back[x-1][y+1],background)==0)
						{
							strcpy(back[x-1][y+1],white);
							x--;
							y++;
							goto jump;
						}
					}
				}//왼쪽 아래 대각선
			}
		}//백돌 2개 끝

	for(x=0;x<15;x++)
		for(y=0;y<15;y++)
		{
			if(strcmp(back[x][y],white)==0)
			{
				while(1)
				{
					m=rand()%3-1;
					n=rand()%3-1;

					if(x>1 && x<14 && y>1 && y<14 && !strcmp(back[x-1][y],background) && !strcmp(back[x-1][y+1],background) && !strcmp(back[x][y+1],background) && !strcmp(back[x+1][y+1],background) && !strcmp(back[x+1][y],background) && !strcmp(back[x+1][y-1],background) && !strcmp(back[x][y-1],background) && !strcmp(back[x-1][y-1],background))
						break;

					else if(x>m && x<15-m && y>n && y<15-n && strcmp(back[x+m][y+n],background)==0)
					{
						strcpy(back[x+m][y+n],white);
						x+=m;
						y+=n;
						goto jump;
					}
				}
			}
		}//백돌 1개

	x=y=8;
	fy=9;
	fx=18;
	if(strcmp(back[x][y],background)==0)
		strcpy(back[x][y],white);

	else
		strcpy(back[x][y-1],white);

jump:;

	count_white++;
	a=x;
	b=y;
	fy=x+1;
	fx=2+y*2;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void judge_black()
{
	int x,y,m,n;
	char end[3];
	FILE* fp;
	fp=fopen("data.txt","a");

	strcpy(end, "★");
	
	for(x=0;x<15;x++)
		for(y=0;y<15;y++)
		{
			if(strcmp(back[x][y],black)==0)
			{
				if(strcmp(back[x][y+1],black)==0 && strcmp(back[x][y+2],black)==0 && strcmp(back[x][y+3],black)==0 && strcmp(back[x][y+4],black)==0)
				{
					for(n=0;n<5;n++)
						strcpy(back[x][y+n],end);
					fprintf(fp,"%s: %d",p1,count_black);
					
					judge=1;
				}//가로 판별

				else if(strcmp(back[x+1][y+1],black)==0 && strcmp(back[x+2][y+2],black)==0 && strcmp(back[x+3][y+3],black)==0 && strcmp(back[x+4][y+4],black)==0)
				{
					for(m=0,n=0;m<5;m++,n++)
						strcpy(back[x+m][y+n],end);
					fprintf(fp,"%s: %d",p1,count_black);
					judge=1;
				}//오른쪽 아래 대각선

				else if(strcmp(back[x+1][y],black)==0 && strcmp(back[x+2][y],black)==0 && strcmp(back[x+3][y],black)==0 && strcmp(back[x+4][y],black)==0)
				{
					for(m=0;m<5;m++)
						strcpy(back[x+m][y],end);
					fprintf(fp,"%s: %d",p1,count_black);
					judge=1;
				}//세로

				else if(strcmp(back[x+1][y-1],black)==0 && strcmp(back[x+2][y-2],black)==0 && strcmp(back[x+3][y-3],black)==0 && strcmp(back[x+4][y-4],black)==0)
				{
					for(m=0,n=0;m<5;m++,n++)
						strcpy(back[x+m][y-n],end);
					fprintf(fp,"%s: %d",p1,count_black);
					judge=1;
				}//왼쪽 아래 대각선
			}
		}

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void judge_white()
{
	int x,y,m,n;
	char end[3];
	
	strcpy(end, "☆");
	
	for(x=0;x<15;x++)
		for(y=0;y<15;y++)
		{
			if(strcmp(back[x][y],white)==0)
			{
				if(strcmp(back[x][y+1],white)==0 && strcmp(back[x][y+2],white)==0 && strcmp(back[x][y+3],white)==0 && strcmp(back[x][y+4],white)==0)
				{
					for(n=0;n<5;n++)
						strcpy(back[x][y+n],end);
					judge=1;
				}//가로 판별

				else if(strcmp(back[x+1][y+1],white)==0 && strcmp(back[x+2][y+2],white)==0 && strcmp(back[x+3][y+3],white)==0 && strcmp(back[x+4][y+4],white)==0)
				{
					for(m=0,n=0;m<5;m++,n++)
						strcpy(back[x+m][y+n],end);

					judge=1;
				}//오른쪽 아래 대각선

				else if(strcmp(back[x+1][y],white)==0 && strcmp(back[x+2][y],white)==0 && strcmp(back[x+3][y],white)==0 && strcmp(back[x+4][y],white)==0)
				{
					for(m=0;m<5;m++)
						strcpy(back[x+m][y],end);

					judge=1;
				}//세로

				else if(strcmp(back[x+1][y-1],white)==0 && strcmp(back[x+2][y-2],white)==0 && strcmp(back[x+3][y-3],white)==0 && strcmp(back[x+4][y-4],white)==0)
				{
					for(m=0,n=0;m<5;m++,n++)
						strcpy(back[x+m][y-n],end);

					judge=1;
				}//왼쪽 아래 대각선
			}
		}

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*void three_three()
{
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*void save_p1()//검은색
{
	Player *p=NULL;
	Player *save=NULL;
	Player *head=NULL;

	p=(Player *)malloc(sizeof(Player));
	head=p;

	while(p!=NULL)
		p=p->next;

	strcpy(p->name,p1);
	p->get=count_black;

	save->next=p;
	p->next=NULL;
*/