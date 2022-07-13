// 游戏头文件
#pragma once

#include "Chess.h"					// 引用Chess头文件

// 图案类
class CBuild
{
public:
	CBuild() {}
	~CBuild() {}
	void beginMode();							// 绘制初始面板背景
	bool button(int a, int b, wchar_t str[]);	// 绘制按钮
	void putSpa(int mode, wchar_t str[], int row, wchar_t* tex[]); // 打印文字
	// 点击按钮后出现两个选项
	bool putMsg(IMAGE& ig, wchar_t str[], wchar_t str1[], wchar_t str2[]);
	void aboutTime();							// 打印时间
};
// 界面类
class CPlay
{
public:
	CPlay() {}
	~CPlay() {}
	void Game();			// 主导游戏界面
};
// 音频类
class CMusic
{
public:
	CMusic() {}
	~CMusic() {}
	void musicPlay();		// 主导背景音乐的播放
};
// 游戏棋盘类
class CChess
{
public:
	CChess();						// 加载图形
	~CChess() {}
	void reSet();					// 数据初始化
	void chesStart();				// 游戏核心
	void chesBoard();				// 棋盘绘制
	void moveDone();				// 棋子选取
	bool choSen(int x, int y);		// 判断是否选中
	void showPos();					// 找到所有可到达的路径
	bool whoWin();					// 判断游戏是否结束
	void pieceRetract();			// 悔棋
private:
	int click = 0, slect = 0, turn = 0; // 是否选取，选择的棋子，红黑方
	IMAGE img[15];						// 共计14个棋子
	struct pos
	{
		int x, y, to;
		bool u;
	}p[33];								// 棋子坐标，指向图案以及是否存在
	struct retract
	{
		int x1, y1, s1;
		int x2, y2, s2;
	}tra[1000];							// 悔棋的棋子的坐标和编号
	int w[9][10], ltos[40][2];			// 坐标代表的棋子(空地), 可达路径记录
	int has[2][2];						// 悔棋的双方的坐标
};