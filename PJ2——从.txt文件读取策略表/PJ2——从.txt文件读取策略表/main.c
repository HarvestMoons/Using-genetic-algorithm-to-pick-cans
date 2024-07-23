#include<stdio.h>
#include <stdlib.h>
#include<sys/timeb.h>
#include <windows.h>
#include<time.h>
#include<conio.h>
#define SPACE 0
#define POT 1
#define WALL 2
#define YELLOW 3
#define ROW 12
#define COL 12
char strategy[243];
void read()
{ 
	FILE* fp= fopen("test.txt", "r") ;          
	if ((fp == NULL))
	{
		return -1;
	}
	for(int i=0;i<243;i++)
	{
		strategy[i] = fgetc(fp);
	}
	return 0;
}
int board[ROW][COL] = { 0 };
int score = 0;
int x = 1, y = 1;//С�Ƶ�����Ϊ��x��y��
int n = 0;//n��¼��С����һ����Ŀ�ĵ����ǹ�ͷ���ǿյ�
void ShowBoard()//��ͼ��ʼ������
{
	system("cls");
	for (int row = 0; row < ROW; row++)
	{
		int random_number;
		srand((unsigned)time(NULL) + rand());
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
void DrawBoard()//��ͼ���ƺ���
{
	system("cls");
	for (int j = 0; j < ROW; j++)
	{
		for (int i = 0; i < COL; i++)
		{
			if (board[i][j] == 0)
				printf("  ");
			else if (board[i][j] == 1)
				printf(" @");
			else if (board[i][j] == 2)
				printf(" #");
			else if (board[i][j] == 3)
				printf(" !");
		}
		printf("\n");
	}
}

void IfPick(int n)//ʰȡ�жϺ���
{
	board[x][y] = n;
}

void Movement(char move_number)//�ƶ�����
{
menu:
		if (move_number == '0')//����ƶ�
		{
			srand((unsigned)time(NULL) + (unsigned)rand());
			move_number = rand() % 5 + 50;
			goto menu;
		}
		else if (move_number == '1')//����
		{
			if (y == 1)
			{
				score = score - 5;
				DrawBoard();
			}
			else
			{
				IfPick(n);
				n = board[x][y - 1];
				y = y - 1;
				board[x][y] = 3;
				DrawBoard();
			}
			printf("      �������� \n");
		}
		else if (move_number == '2')//����
		{

			if (y == ROW - 2)
			{
				score = score - 5;
				DrawBoard();
			}
			else
			{
				IfPick(n);
				n = board[x][y + 1];
				y = y + 1;
				board[x][y] = 3;
				DrawBoard();
			}
			printf("      �������� \n");
		}
		else if (move_number == '3')//����
		{
			if (x == 1)
			{
				score = score - 5;
				DrawBoard();
			}
			else
			{
				IfPick(n);
				n = board[x - 1][y];
				x = x - 1;
				board[x][y] = 3;
				DrawBoard();
			}
			printf("      �������� \n");
		}
		else if (move_number == '4')//����
		{
			if (x == COL - 2)
			{
				score = score - 5;
				DrawBoard();
			}
			else
			{
				IfPick(n);
				n = board[x + 1][y];
				x = x + 1;
				board[x][y] = 3;
				DrawBoard();
			}
			printf("      �������� \n");
		}
		else if (move_number == '5')//����
		{
			DrawBoard();
			printf("      û���ƶ� \n");
		}
		else if (move_number == '6')//���ͷ
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
			printf("      ���Լ��ͷ \n");
		}
		printf("    ���ĵ÷�Ϊ��%d", score);
	
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
void Game()//��Ϸ����
{
	ShowBoard();
	DrawBoard();
	for (int i = 0; i < 200; i++)
	{		
		int a=Location();
		Movement(a);
		Sleep(1000);
	}
}

int main()
{
	read();
	Game();
	printf("�������յ÷�Ϊ��%d", score);
	return 0;
}