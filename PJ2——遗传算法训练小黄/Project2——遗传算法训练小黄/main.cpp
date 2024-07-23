#include"function.h"
int strategy[999][200][243] = { 0 };
int score = 0;
int rank[200] = { 0 };//临时数组rank中依次存储得分最高的小黄的序号（共200个）
int judge[(1 + PICK) * PICK / 2] = { 0 };
int main()
{
	int gen = 0;
	FILE*pf=fopen("strategy.txt","w");
	srand(time(0));
	int average[999] = { 0 };	
	int zero=0;
	JudgeValue();
	gen_0_Choice(gen);//亲本策略生成(亲本gen=0)

	for (; gen < 999; gen++)//999代小黄
	{
		if (0!=gen  )
			gen_x_Choice(gen,&zero);
		zero = 0;
		int everyYellowScore[200] = { 0 };//每一代，everyYellowScore要重置为0
		for (int num = 0; num < 200; num++)//200个小黄
		{			
			for (int j = 0; j < 100; j++)//100个棋盘
			{
				ShowBoard();
				for (int i = 0; i < 200; i++)//走200步
				{
					Movement(Location(gen, num));
				}
				everyYellowScore[num] += score;				
				score = 0;
			}
			if (0==everyYellowScore[num]) 
				zero++;//对0分计数
			average[gen] = average[gen] + everyYellowScore[num];
		}

		for (int i = 0; i < 200; i++)//在内部反复定义rank
			rank[i] = i + 1;//rank={1,2,3,4...200}
		
		BubbleSort(everyYellowScore, 200, rank);//为小黄的得分排序，并记录得分由高到低的序号于rank数组中
		printf("gen%d_average=%f\n", gen, (float)(average[gen])/ 20000);
		fprintf(pf, "%f\n", (float)(average[gen]) / 20000);
	}

	if (NULL == pf) 
		printf("文件打开失败！\n");
	else for (int i = 0; i < 243; i++)
	{
		fprintf(pf,"%d", strategy[998][rank[0]][i]);
	}
	fclose(pf);
	return 0;
}


