//ͷ�ļ�
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//����
#define SNAKE_LEN_MAX 100	//������󳤶�
#define MAPWIDTH 80		//��ͼ���	
#define MAPHEIGHT 24	//��ͼ�߶�
#define ADDWIDTH 20
#define ADDHEIGHT 2

//ʳ�������
struct Food
{
	int x;
	int y;
}food;
//�ߵ��������
struct Snake
{
	int speed;		//�ߵ��ٶ�
	int len;		//�ߵĳ���
	int x[SNAKE_LEN_MAX];	//ÿ����ĺ�����
	int y[SNAKE_LEN_MAX];	//ÿ�����������
}snake;

//��������λ��
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//���Ƶ�ͼ
void drawMap();
//��������λ��
void gotoxy(int x, int y);
//��������
void keyDown();
//�ߵ�״̬
bool snakeStatus();
//�������ʳ��
void createFood();

int key = 72;	//�ߵ�ǰ�ƶ��ķ���
int changeFlag = 0;	//�ж����Ƿ��Ѿ��Ե���ʳ��
int scores = 0;		//��¼Ŀǰ�ķ���

int i;

void drawMap()
{
	//��ӡ���±߿�
	for (i = ADDWIDTH; i <=  ADDWIDTH + MAPWIDTH; i += 2)
	{
		gotoxy(i, ADDHEIGHT);
		printf("�}");
		gotoxy(i, MAPHEIGHT + ADDHEIGHT);
		printf("�}");
	}
	//��ӡ���ұ߿�
	for (i = ADDHEIGHT; i < MAPHEIGHT + ADDHEIGHT; i++)
	{
		gotoxy(ADDWIDTH, i);
		printf("�}");
		gotoxy(MAPWIDTH + ADDWIDTH, i);
		printf("�}");
	}
	//���ع��
	CONSOLE_CURSOR_INFO cinfo;
	cinfo.bVisible = 0;
	cinfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cinfo);
	//���ƹ�ʵ
	while (1)
	{
		srand((unsigned)time(NULL));
		food.x = rand() % MAPWIDTH + ADDWIDTH + 2;
		food.y = rand() % MAPHEIGHT + ADDHEIGHT + 1;
		if (food.x % 2 == 0)
			break;
	}
	gotoxy(food.x, food.y);
	printf("��");
	//���߽��г�ʼ��
	snake.len = 1;
	snake.speed = 50;
	snake.x[0] = MAPWIDTH / 2 + ADDWIDTH;
	snake.y[0] = MAPHEIGHT / 2 + ADDHEIGHT;
	gotoxy(snake.x[0], snake.y[0]);
	printf("�}");
	for (i = 1; i < snake.len; i++)
	{
		snake.x[i] = snake.x[i - 1] + 2;
		snake.y[i] = snake.y[i - 1];
		gotoxy(snake.x[i], snake.y[i]);
		printf("�}");
	}
	return;
}

//�����ߵ��ƶ�
void keyDown()
{
	//��¼ԭ���ķ���
	int pre_key = key;
	if (_kbhit())
	{
		//��ջ�����
		fflush(stdin);
		//��Ҫ���β�������key
		key = _getch();
		key = _getch();
	}
	//���û�гԵ���ʵ���͵���β�������һ��
	if (!changeFlag)
	{
		gotoxy(snake.x[snake.len - 1], snake.y[snake.len - 1]);
		printf("  ");
	}
	//�����е���ǰ��һλ
	for (i = snake.len - 1; i > 0; i--)
	{
		snake.x[i] = snake.x[i - 1];
		snake.y[i] = snake.y[i - 1];
	}
	//�жϽ��������ƶ��ķ��򣬲��ܺ�ԭ���ķ����ͻ
	if (key == 72 && pre_key == 80)
		key = 80;
	if (key == 80 && pre_key == 72)
		key = 72;
	if (key == 75 && pre_key == 77)
		key = 77;
	if (key == 77 && pre_key == 75)
		key = 75;

	//����ǰ���ķ���
	switch(key)
	{
		case 75: //����		
		     snake.x[0] -= 2;
		     break;
		case 77: //����		
		     snake.x[0] += 2;
		     break;
		case 72: //����		
		     snake.y[0]--;
		     break;
		case 80: //����		
		     snake.y[0]++;
		     break; 
	}
	//������β
	gotoxy(snake.x[0], snake.y[0]);
	printf("�}");
	changeFlag = 0;
	return;
}

bool snakeStatus()
{
	if (snake.x[0] == ADDWIDTH)
		return false;
	if (snake.x[0] == ADDWIDTH + MAPWIDTH)
		return false;
	if (snake.y[0] == ADDHEIGHT)
		return false;
	if (snake.y[0] == ADDHEIGHT + MAPHEIGHT)
		return false;
	for (i = 1; i < snake.len; i++)
		if (snake.x[0] == snake.x[i] && snake.y[0] == snake.y[i])
			return false;
	return true;
}

//�ж��Ƿ�Ե�ʳ��
void createFood()
{
	if (food.x == snake.x[0] && food.y == snake.y[0])
	{
		while (1)
		{
			int flag = 1;
			srand((unsigned int)time(NULL));
			food.x = rand() % (MAPWIDTH - 2) + ADDWIDTH;
			food.y = rand() % (MAPHEIGHT - 1) + ADDHEIGHT;
			for (i = 0; i < snake.len; i++)
				if (snake.x[i] == food.x && snake.y[i] == food.y)
				{
					flag = 0;
					break;
				}
			if (flag && food.x % 2 == 0)
				break;
		}
		//�����µĹ�ʵ
		gotoxy(food.x, food.y);
		printf("��");

		//���·���
		changeFlag = 1;
		scores += 10;
		snake.len++;
		snake.speed --;
	}
}

//������
int main()
{
	//���س�ʼ����
	char ch;
	gotoxy(39, 8);
	printf("Welcome to our game!!!");
	gotoxy(39, 10);
	printf("Please enter q to quit and else to start:\n");
	gotoxy(39, 12);
	ch = getchar();
	gotoxy(39, 14);
	if (ch == 'q')
	{
		printf("Bye~\n");
		return 0;
	}
	printf("Let's start!\n");
	system("CLS");
	//��ʼ���Ƶ�ͼ���Թ�ʵ���߽��г�ʼ��
	drawMap();
	while(1)
	{
		keyDown();
		//���ײǽ�������Լ�������ͽ�����Ϸ
		if (!snakeStatus())
			break;
		createFood();
		Sleep(snake.speed);
	}

	gotoxy(39, 8);
	printf("Game over!!!");
	gotoxy(39, 10);
	printf("Your total score is:%d", scores);
	gotoxy(39, 12);
	printf("See you next time~~~");

	return 0;
}