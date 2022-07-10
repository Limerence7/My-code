// 主界面头文件
#include "Game.h"

char ch;							// 键盘信息
MOUSEMSG m_msg;						// 鼠标信息
// 主导游戏界面
void CPlay::Game()
{
	CBuild* bui = new CBuild();		// 定义CBuild指针
	
	setbkmode(TRANSPARENT);			// 设置背景模式

	BeginBatchDraw();

	while (1)
	{
		if (_kbhit())
		{
			ch = _getch();			// 获取键盘信息
			if (ch == 27)
				break;				// ESC退出
		}
		while (MouseHit())
			m_msg = GetMouseMsg();	// 获取鼠标信息

		bui->beginMode();			// 绘制初始背景

		for (int i = 0; i <= 3; i++)
		{
			settextcolor(RGB(255, 200, 90));
			settextstyle(70, 0, TEXT("行楷"));
			outtextxy(360 + i, 20 + i, TEXT("中国象棋"));
		}
		settextcolor(RGB(210, 105, 30));
		outtextxy(360 + 4, 20 + 4, TEXT("中国象棋"));		// 制作标题

		if (bui->button(20, 480, (wchar_t*)L"  开始游戏  ")) // 开始游戏
		{
			CChess* che = new CChess();					    // 构造函数
			che->reSet();									//	初始化
			che->chesStart();

			delete che;
			che = NULL;
		}

		if (bui->button(20, 560, (wchar_t*)L"  背景音乐  "))	// 背景音乐
		{
			CMusic* msc = new CMusic();
			msc->musicPlay();

			delete msc;
			msc = NULL;
		}

		if (bui->button(780, 480, (wchar_t*)L"   帮  助    "))
		{
			wchar_t* str1[5];
			str1[0] = (wchar_t*)L"此象棋游戏是由C++编写";
			str1[1] = (wchar_t*)L"通过EasyX的图形库完成";
			str1[2] = (wchar_t*)L"点击开始按钮即可开始游戏";
			str1[3] = (wchar_t*)L"也可挑选背景音乐";
			str1[4] = (wchar_t*)L"通过鼠标实现棋子的移动";
			bui->putSpa(1, (wchar_t*)L"   帮  助   ", 5, str1);		//打印文字
		}

		if (bui->button(780, 560, (wchar_t*)L"  制作团队  "))
		{
			wchar_t* str2[3];
			str2[0] = (wchar_t*)L"计算机科学与技术  216班";
			str2[1] = (wchar_t*)L"阮 思 凯 ";
			str2[2] = (wchar_t*)L"熊 炜 铭 ";
			bui->putSpa(0, (wchar_t*)L"  制作团队  ", 3, str2);		// 打印文字
		}

		LOGFONT f;
		gettextstyle(&f);
		f.lfHeight = 40;
		f.lfWidth = 20;
		f.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&f);
		setcolor(RGB(244, 164, 96));						// 调节字体

		outtextxy(360, 560, TEXT("按ESC退出游戏"));
		outtextxy(640, 70, TEXT("Version: 1.0"));				// 其他文字

		FlushBatchDraw();
		Sleep(5);
	}

	EndBatchDraw();									// 结束绘制

	delete bui;
	bui = NULL;										// 删除指针
}