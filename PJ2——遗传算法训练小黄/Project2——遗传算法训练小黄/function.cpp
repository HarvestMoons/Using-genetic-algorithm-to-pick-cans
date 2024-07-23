#include"function.h"
int n = 0;//n记录了小黄下一步的目的地上是罐头还是空地，并把目前所在地的信息传入Location函数
int x = 1, y = 1;//小黄的坐标为（x，y）
int p1, p2;//抽取亲本
int board[ROW][COL] = {0};

void JudgeValue()//把数组Judge赋值为{1,2,2,3,3,3.......PICK}
{
	for (int i = 1; i <= PICK; i++)
	{
		int k = i;
		while (k > 0)
		{
			for (int j = 0; j < (1 + PICK) * PICK / 2; j++)
			{
				if (0==judge[j] )
				{
					judge[j] = i;
					k--;
				}
				if (0==k)break;
			}
		}
	}
}
void ShowBoard()//地图初始化函数
{
	x = 1, y = 1;//重置全局变量x，y
	for (int row = 0; row < ROW; row++)
	{
		int random_number;
		if (0==row  || ROW - 1==row)
		{
			for (int col = 0; col < COL; col++)			
				board[row][col] = WALL;		
		}
		else
		{
			for (int col = 0; col < COL; col++)
			{
				if (0==col)				
					board[row][col] = WALL;				
				else if (col == COL - 1)				
					board[row][col] = WALL;				
				else if (1==col  && 1==row )				
					board[row][col] = YELLOW;			
				else
				{
					random_number = rand() % 2;
					if (random_number == 1)				
						board[row][col] = SPACE;					
					else					
						board[row][col] = POT;					
				}
			}
		}
	}
}
void Movement(int move_number)//移动函数
{	
menu:
	if (move_number == 0)//随机移动
	{
		move_number = rand() % 6 + 1;
		goto menu;
	}
	else if (move_number == 1)//上移
	{
		if (y == 1)		
			score = score - 5;	
		else
		{
			board[x][y] = n;
			n = board[x][y - 1];
			y = y - 1;
			board[x][y] = 3;
		}
	}
	else if (move_number == 2)//下移
	{
		if (y == ROW - 2)		
			score = score - 5;		
		else
		{
			board[x][y] = n;
			n = board[x][y + 1];
			y = y + 1;
			board[x][y] = 3;
		}
	}
	else if (move_number == 3)//左移
	{
		if (x == 1)		
			score = score - 5;		
		else
		{
			board[x][y] = n;
			n = board[x - 1][y];
			x = x - 1;
			board[x][y] = 3;
		}
	}
	else if (move_number ==4)//右移
	{
		if (x == COL - 2)		
			score = score - 5;		
		else
		{
			board[x][y] = n;
			n = board[x + 1][y];
			x = x + 1;
			board[x][y] = 3;
		}

	}
	else if (move_number == 5)//不移	
		score = score;	
	else if (move_number == 6)//捡罐头
	{
		if (n == 1)
		{
			score = score + 10;
			board[x][y] = 3;
			n = 0;//把n更新为0
		}
		else if (n == 0)		
			score = score - 2;		
	}
}
void gen_0_Choice(int gen)
{
	for (int j = 0; j < 200; j++) 
	{
		for (int i = 0; i < 243; i++)
		{
			strategy[gen][j][i] = rand() % 7;//把数组中的243个元素赋值为0-6的随机数
		}
	}
}
int Location(int gen, int num)
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
	return strategy[gen][num][t];
}
void Parents()//亲本挑选函数
{
	int a = rand() % (1 + PICK) * PICK / 2;
	int b = rand() % (1 + PICK) * PICK / 2;//a，b是0-(1 + PICK) * PICK / 2 (1829)间的随机数
	p1 = rank[PICK - judge[a]];
	p2 = rank[PICK - judge[b]];//(p1,p2范围是1-PICK)	
}
void gen_x_Choice(int gen,int*pzero)//子代策略
{
	if (*pzero >= 195)
	{
		gen_0_Choice(gen);
	}
	else{
		for (int num = 0; num < 200; num = num + 2)
		{
			if (num < 10)
			{
				for (int j = 0; j < 243; j++)
				{
					strategy[gen][num][j] = strategy[gen - 1][rank[num] - 1][j];
					strategy[gen][num + 1][j] = strategy[gen - 1][rank[num + 1] - 1][j];
				}
			}
			else
			{
				Parents();
				for (int j = 0; j < 243; j++)//每一步策略
				{
					int random_number = rand() % 400;//变异	
					if (random_number != 1) {
						if (j < 60 || (j >= 120 && j < 180))
						{
							strategy[gen][num][j] = strategy[gen - 1][p1 - 1][j];
							strategy[gen][num + 1][j] = strategy[gen - 1][p2 - 1][j];
						}
						else
						{
							strategy[gen][num][j] = strategy[gen - 1][p2 - 1][j];
							strategy[gen][num + 1][j] = strategy[gen - 1][p1 - 1][j];
						}
					}
					else
					{
						strategy[gen][num][j] = rand() % 7;
						strategy[gen][num + 1][j] = rand() % 7;
					}
				}
			}
		}
	}
}
void BubbleSort(int a[], int n, int position[])
{
	int tmp = 0;
	for (int i = 0; i < n - 1; ++i)
	{
		for (int j = 1; j < n - i; ++j)
		{
			if (a[j] > a[j - 1])//从大到小排序，把较小的交换到后面来 
			{
				tmp = a[j - 1];
				a[j - 1] = a[j];
				a[j] = tmp;
				tmp = position[j - 1];
				position[j - 1] = position[j];
				position[j] = tmp;
			}
		}
	}
}
