#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
//��������
void gotoxy(int x, int y) //����������(x,y)��λ��
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}
void HideCursor()	  //���ع��
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

//ȫ�ֱ����Ķ���
//��Ϸ�����С
int high;
int width;
//С�������
int bird_x;
int bird_y;
//�ϰ�����������	
int bar1_y;
int bar1_xTop;
int bar1_xDown;
int score;

void startup() //���ݳ�ʼ��
{
	//��Ϸ�����С 
	high = 15;	
	width = 25;
	//С��ĳ�ʼλ�� 
	bird_x = high / 2;
	bird_y = width / 4;
	//�ϰ���ĳ�ʼλ��
	bar1_y = width - 1;	
	bar1_xTop = high / 4;
	bar1_xDown = high / 2;
	//�÷� 
	score = 0;
}

void show()  //��ʾ����
{
	gotoxy(0, 0);	//����������(0,0)��λ��
	int i, j;
	for (i = 0; i < high; i++)
	{
		for (j = 0; j < width; j++)
		{
			if ((i == bird_x) && (j == bird_y))	//���С��
			{
				printf("@");
			}
			else if ((j == bar1_y) && ((i < bar1_xTop) || (i > bar1_xDown)))	//����ϰ���	
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
	printf("�÷֣�%d\n", score);
}

int updateWithoutInput()//���û��޹صĸ���
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
			printf("��Ϸʧ�ܣ�����");
			return -1;
		}
	}
	else
	{
		if (bird_x > high)
		{
			printf("��Ϸʧ�ܣ�����");
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
 
void updateWithInput()//���û������йصĸ���
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
	startup();	//��ʼ������ 
	while (1)
	{
		show(); //��ʾ����
		int ret = updateWithoutInput();//���û��޹صĸ���
		if (ret == -1)
		{
			system("CLS");
			printf("1.���¿�ʼ\n0.�˳�\n��ѡ��");
			int input = 0;
			scanf("%d", &input);
			if (input)
			{
				goto again;
			}
			else
				return 0;
		}
		updateWithInput();//���û������йصĸ���
	}
	return 0;
}