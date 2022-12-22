#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
//辅助函数
void gotoxy(int x, int y) //将光标调整到(x,y)的位置
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}
void HideCursor()	  //隐藏光标
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

//全局变量的定义
//游戏画面大小
int high;
int width;
//小鸟的坐标
int bird_x;
int bird_y;
//障碍物的相关坐标	
int bar1_y;
int bar1_xTop;
int bar1_xDown;
int score;

void startup() //数据初始化
{
	//游戏界面大小 
	high = 15;	
	width = 25;
	//小鸟的初始位置 
	bird_x = high / 2;
	bird_y = width / 4;
	//障碍物的初始位置
	bar1_y = width - 1;	
	bar1_xTop = high / 4;
	bar1_xDown = high / 2;
	//得分 
	score = 0;
}

void show()  //显示画面
{
	gotoxy(0, 0);	//将光标调整到(0,0)的位置
	int i, j;
	for (i = 0; i < high; i++)
	{
		for (j = 0; j < width; j++)
		{
			if ((i == bird_x) && (j == bird_y))	//输出小鸟
			{
				printf("@");
			}
			else if ((j == bar1_y) && ((i < bar1_xTop) || (i > bar1_xDown)))	//输出障碍物	
			{
				printf("*");
			}
			else
			{
				printf(" ");
			}
		}
		printf("\n");
	}
	printf("得分：%d\n", score);
}

int updateWithoutInput()//与用户无关的更新
{
	bird_x++;	
	bar1_y--;
	if (bird_y == bar1_y)
	{
		if ((bird_x >= bar1_xTop) && (bird_x <= bar1_xDown))	
		{
			score++;
		}
		else
		{
			printf("游戏失败！！！");
			return -1;
		}
	}
	else
	{
		if (bird_x > high)
		{
			printf("游戏失败！！！");
			return -1;
		}
	}
	if (bar1_y <= 0)
	{
		bar1_y = width - 1;
		int upside = rand() % (int)(high * 0.6) + 1;
		bar1_xTop = upside;
		int opening = rand() % (int)(high * 0.2) + 2;
		while ((bar1_xDown = bar1_xTop + opening) > high - 2)
		{
			opening = rand() % (int)(high * 0.2) + 2;
		}
	}
	Sleep(150);
	return 0;
 }
 
void updateWithInput()//与用户输入有关的更新
{
	char input;
	if (_kbhit())
	{
		input = _getch();
		if (input == ' ' && bird_x > 0)
		{
			bird_x = bird_x - 2;
		}
	}
}
int main()
{
	srand((unsigned)time(NULL));
	HideCursor();
again:
	startup();	//初始化变量 
	while (1)
	{
		show(); //显示画面
		int ret = updateWithoutInput();//与用户无关的更新
		if (ret == -1)
		{
			system("CLS");
			printf("1.重新开始\n0.退出\n请选择：");
			int input = 0;
			scanf("%d", &input);
			if (input)
			{
				goto again;
			}
			else
				return 0;
		}
		updateWithInput();//与用户输入有关的更新
	}
	return 0;
}