//头文件
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//常量
#define SNAKE_LEN_MAX 100	//蛇身最大长度
#define MAPWIDTH 80		//地图宽度	
#define MAPHEIGHT 24	//地图高度
#define ADDWIDTH 20
#define ADDHEIGHT 2

//食物的坐标
struct Food
{
	int x;
	int y;
}food;
//蛇的相关属性
struct Snake
{
	int speed;		//蛇的速度
	int len;		//蛇的长度
	int x[SNAKE_LEN_MAX];	//每个点的横坐标
	int y[SNAKE_LEN_MAX];	//每个点的纵坐标
}snake;

//调整光标的位置
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//绘制地图
void drawMap();
//调整光标的位置
void gotoxy(int x, int y);
//按键操作
void keyDown();
//蛇的状态
bool snakeStatus();
//随机生成食物
void createFood();

int key = 72;	//蛇当前移动的方向
int changeFlag = 0;	//判断蛇是否已经吃掉了食物
int scores = 0;		//记录目前的分数

int i;

void drawMap()
{
	//打印上下边框
	for (i = ADDWIDTH; i <=  ADDWIDTH + MAPWIDTH; i += 2)
	{
		gotoxy(i, ADDHEIGHT);
		printf("▆");
		gotoxy(i, MAPHEIGHT + ADDHEIGHT);
		printf("▆");
	}
	//打印左右边框
	for (i = ADDHEIGHT; i < MAPHEIGHT + ADDHEIGHT; i++)
	{
		gotoxy(ADDWIDTH, i);
		printf("▆");
		gotoxy(MAPWIDTH + ADDWIDTH, i);
		printf("▆");
	}
	//隐藏光标
	CONSOLE_CURSOR_INFO cinfo;
	cinfo.bVisible = 0;
	cinfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cinfo);
	//绘制果实
	while (1)
	{
		srand((unsigned)time(NULL));
		food.x = rand() % MAPWIDTH + ADDWIDTH + 2;
		food.y = rand() % MAPHEIGHT + ADDHEIGHT + 1;
		if (food.x % 2 == 0)
			break;
	}
	gotoxy(food.x, food.y);
	printf("￥");
	//对蛇进行初始化
	snake.len = 1;
	snake.speed = 50;
	snake.x[0] = MAPWIDTH / 2 + ADDWIDTH;
	snake.y[0] = MAPHEIGHT / 2 + ADDHEIGHT;
	gotoxy(snake.x[0], snake.y[0]);
	printf("▆");
	for (i = 1; i < snake.len; i++)
	{
		snake.x[i] = snake.x[i - 1] + 2;
		snake.y[i] = snake.y[i - 1];
		gotoxy(snake.x[i], snake.y[i]);
		printf("▆");
	}
	return;
}

//控制蛇的移动
void keyDown()
{
	//记录原来的方向
	int pre_key = key;
	if (_kbhit())
	{
		//清空缓存区
		fflush(stdin);
		//需要两次才能输入key
		key = _getch();
		key = _getch();
	}
	//如果没有吃到果实，就到蛇尾擦除最后一节
	if (!changeFlag)
	{
		gotoxy(snake.x[snake.len - 1], snake.y[snake.len - 1]);
		printf("  ");
	}
	//把所有点往前移一位
	for (i = snake.len - 1; i > 0; i--)
	{
		snake.x[i] = snake.x[i - 1];
		snake.y[i] = snake.y[i - 1];
	}
	//判断接下来蛇移动的方向，不能和原来的方向冲突
	if (key == 72 && pre_key == 80)
		key = 80;
	if (key == 80 && pre_key == 72)
		key = 72;
	if (key == 75 && pre_key == 77)
		key = 77;
	if (key == 77 && pre_key == 75)
		key = 75;

	//调整前进的方向
	switch(key)
	{
		case 75: //往左		
		     snake.x[0] -= 2;
		     break;
		case 77: //往右		
		     snake.x[0] += 2;
		     break;
		case 72: //往上		
		     snake.y[0]--;
		     break;
		case 80: //往下		
		     snake.y[0]++;
		     break; 
	}
	//补充蛇尾
	gotoxy(snake.x[0], snake.y[0]);
	printf("▆");
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

//判断是否吃掉食物
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
		//绘制新的果实
		gotoxy(food.x, food.y);
		printf("￥");

		//更新分数
		changeFlag = 1;
		scores += 10;
		snake.len++;
		snake.speed --;
	}
}

//主函数
int main()
{
	//加载初始界面
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
	//开始绘制地图，对果实和蛇进行初始化
	drawMap();
	while(1)
	{
		keyDown();
		//如果撞墙或碰到自己的身体就结束游戏
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