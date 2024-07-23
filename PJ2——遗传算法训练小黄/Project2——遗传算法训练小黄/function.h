#pragma once
#include<stdio.h>
#include <stdlib.h>
#include<sys/timeb.h>
#include <windows.h>
#include<time.h>
#include<conio.h>
#include<easyx.h>
#define SPACE 0
#define POT 1
#define WALL 2
#define YELLOW 3
#define ROW 12
#define COL 12
#define PICK 200
extern int strategy[999][200][243];
extern int average[999] ;
extern int score;
extern int rank[200];
extern int judge[(1 + PICK) * PICK / 2] ;
void JudgeValue();
void ShowBoard();
void Movement(int a);
void gen_0_Choice(int gen);
int Location(int gen, int num);
void Parents();
void gen_x_Choice(int gen,int*pzero);
void BubbleSort(int a[], int n, int position[]);