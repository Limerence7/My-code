// 程序开端文件

#include "Game.h"			// 包含游戏头文件

//主函数
int main()
{
	srand((unsigned int)time(NULL));		//随机种子

	initgraph(960, 720);					//初始化游戏窗口

	CPlay* First = new CPlay();
	First->Game();							// 开始游戏

	delete First;
	First = NULL;							// 删除指针

	_getch();
	closegraph();
	return 0;								//关闭游戏窗口
}