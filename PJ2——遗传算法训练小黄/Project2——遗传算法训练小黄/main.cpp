#include"function.h"
int strategy[999][200][243] = { 0 };
int score = 0;
int rank[200] = { 0 };//��ʱ����rank�����δ洢�÷���ߵ�С�Ƶ���ţ���200����
int judge[(1 + PICK) * PICK / 2] = { 0 };
int main()
{
	int gen = 0;
	FILE*pf=fopen("strategy.txt","w");
	srand(time(0));
	int average[999] = { 0 };	
	int zero=0;
	JudgeValue();
	gen_0_Choice(gen);//�ױ���������(�ױ�gen=0)

	for (; gen < 999; gen++)//999��С��
	{
		if (0!=gen  )
			gen_x_Choice(gen,&zero);
		zero = 0;
		int everyYellowScore[200] = { 0 };//ÿһ����everyYellowScoreҪ����Ϊ0
		for (int num = 0; num < 200; num++)//200��С��
		{			
			for (int j = 0; j < 100; j++)//100������
			{
				ShowBoard();
				for (int i = 0; i < 200; i++)//��200��
				{
					Movement(Location(gen, num));
				}
				everyYellowScore[num] += score;				
				score = 0;
			}
			if (0==everyYellowScore[num]) 
				zero++;//��0�ּ���
			average[gen] = average[gen] + everyYellowScore[num];
		}

		for (int i = 0; i < 200; i++)//���ڲ���������rank
			rank[i] = i + 1;//rank={1,2,3,4...200}
		
		BubbleSort(everyYellowScore, 200, rank);//ΪС�Ƶĵ÷����򣬲���¼�÷��ɸߵ��͵������rank������
		printf("gen%d_average=%f\n", gen, (float)(average[gen])/ 20000);
		fprintf(pf, "%f\n", (float)(average[gen]) / 20000);
	}

	if (NULL == pf) 
		printf("�ļ���ʧ�ܣ�\n");
	else for (int i = 0; i < 243; i++)
	{
		fprintf(pf,"%d", strategy[998][rank[0]][i]);
	}
	fclose(pf);
	return 0;
}


