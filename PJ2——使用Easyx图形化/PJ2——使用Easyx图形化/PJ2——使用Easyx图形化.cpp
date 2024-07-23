#include<stdio.h>
#include <stdlib.h>
#include<sys/timeb.h>
#include <windows.h>
#include<time.h>
#include<easyx.h>
#define SPACE 0
#define POT 1
#define WALL 2
#define YELLOW 3
#define ROW 12
#define COL 12
char strategy[243];
IMAGE wall;
IMAGE yellow;
IMAGE pot;
IMAGE wallMask;
IMAGE yellowMask;
IMAGE potMask;
int board[ROW][COL] = { 0 };
int score = 0;
int x = 1, y = 1;//小黄的坐标为（x，y）
int n = 0;//n记录了小黄下一步的目的地上是罐头还是空地
FILE* read()
{
	FILE* fp = fopen("data.txt", "r");
	if ((fp == NULL))
	{
		return NULL;
	}
	for (int i = 0; i < 243; i++)
	{
		strategy[i] = fgetc(fp);
	}
	return fp;
}
void putTransparentImage(int x, int y, const IMAGE* mask, const IMAGE* img)
{
	putimage(x, y, mask, SRCAND);
	putimage(x, y, img, SRCPAINT);
}
void ShowBoard()//地图初始化函数
{
	system("cls");
	for (int row = 0; row < ROW; row++)
	{
		int random_number;
		if (row == 0 || row == ROW - 1)
		{
			for (int col = 0; col < COL; col++)
			{
				board[row][col] = WALL;
			}
		}
		else
		{
			for (int col = 0; col < COL; col++)
			{
				if (col == 0)
				{
					board[row][col] = WALL;
				}
				else if (col == COL - 1)
				{
					board[row][col] = WALL;
				}
				else if (col == 1 && row == 1)
				{
					board[row][col] = YELLOW;
				}
				else
				{
					random_number = rand() % 2;
					if (random_number == 1)
					{
						board[row][col] = SPACE;
					}
					else
					{
						board[row][col] = POT;
					}
				}
			}
		}
	}
	board[x][y] = 0;
	board[x][y] = 3;
}
void image()
{	
	loadimage(&wall, "bwall.png",50,50);
	loadimage(&pot, "bpot2.png", 50, 50);
	loadimage(&yellow, "byellow.png", 40, 40);
	loadimage(&wallMask, "wallMask.png", 50, 50);
	loadimage(&potMask, "pot2Mask.png", 50, 50);
	loadimage(&yellowMask, "yellowMask.png", 40, 40);
}
void DrawBoard()//地图绘制函数
{
	cleardevice();
	for (int j = 0; j < COL; j++)
	{
		int n1 = j*50;
		for (int i = 0; i < ROW; i++)
		{
			int n2 = i*50;
			if (board[i][j] == POT)
				putTransparentImage(n2, n1, &potMask, &pot);
			else if (board[i][j] == WALL)
				putTransparentImage(n2, n1, &wallMask, &wall);
			else if (board[i][j] == YELLOW)
				putTransparentImage(n2, n1, &yellowMask, &yellow);
		}
	}
}
void Movement(char move_number)//移动函数
{
menu:
	if (move_number == '0')//随机移动
	{
		move_number = rand() % 5 + 50;
		goto menu;
	}
	else if (move_number == '1')//上移
	{
		if (y == 1)
		{
			score = score - 5;
			DrawBoard();
		}
		else
		{
			board[x][y] = n;
			n = board[x][y - 1];
			y = y - 1;
			board[x][y] = 3;
			DrawBoard();
		}
	}
	else if (move_number == '2')//下移
	{

		if (y == ROW - 2)
		{
			score = score - 5;
			DrawBoard();
		}
		else
		{
			board[x][y] = n;
			n = board[x][y + 1];
			y = y + 1;
			board[x][y] = 3;
			DrawBoard();
		}
	}
	else if (move_number == '3')//左移
	{
		if (x == 1)
		{
			score = score - 5;
			DrawBoard();
		}
		else
		{
			board[x][y] = n;
			n = board[x - 1][y];
			x = x - 1;
			board[x][y] = 3;
			DrawBoard();
		}
	}
	else if (move_number == '4')//右移
	{
		if (x == COL - 2)
		{
			score = score - 5;
			DrawBoard();
		}
		else
		{
			board[x][y] = n;
			n = board[x + 1][y];
			x = x + 1;
			board[x][y] = 3;
			DrawBoard();
		}
	}
	else if (move_number == '5')//不移
	{
		DrawBoard();
	}
	else if (move_number == '6')//捡罐头
	{
		if (n == 1)
		{
			score = score + 10;
			board[x][y] = 3;
			DrawBoard();
			n = 0;
		}
		else if (n == 0)
		{
			score = score - 2;
			DrawBoard();
		}
	}
}
int Location()
{
	int t = 0;
	if (n == 0)
	{
		t = 81 * board[x][y - 1] + 27 * board[x - 1][y] + 3 * board[x + 1][y] + board[x][y + 1];
	}
	else if (n == 1)
	{
		t = 81 * board[x][y - 1] + 27 * board[x - 1][y] + 9 * 1 + 3 * board[x + 1][y] + board[x][y + 1];
	}
	return strategy[t];
}
void Game(FILE* pf)//游戏函数
{
	srand(time(0));
	initgraph(600, 600);
	setbkcolor(RGB(250, 250, 210));
	cleardevice();
	ShowBoard();
	DrawBoard();
	for (int i = 0; i < 200; i++)
	{
		int a = Location();
		Movement(a);
		Sleep(1000);
	}
	getchar();
	closegraph();
	fclose(pf);
}
int main(int argc, char* argv[])
{
	image();
	FILE* pf=read();
	if (pf == NULL) 
	{
		printf("文件读取失败！\n");
		return 0;
	}
	Game(pf);
	printf("小黄的最终得分为：%d\n",score);
	return 0;
}
