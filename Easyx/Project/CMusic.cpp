// 音频类
#include "Game.h"

extern char ch;
extern MOUSEMSG m_msg;
// 主导背景音乐的播放
void CMusic::musicPlay()
{
	CBuild* cbui = new CBuild();
	while (1)
	{
		while (MouseHit())
			m_msg = GetMouseMsg();
		cbui->beginMode();								// 背景图片

		for (int i = 0; i <= 3; i++)
		{
			settextcolor(RGB(200, 200, 200));
			settextstyle(70, 0, TEXT("行楷"));
			outtextxy(280 + i, 20 + i, L"  背景音乐  ");
		}

		settextcolor(WHITE);
		outtextxy(280 + 4, 20 + 4, L"  背景音乐  ");      // 背景音乐
		// 所有音乐选项
		if (cbui->button(150, 100, (wchar_t*)L"     1.轨迹     "))
		{
			PlaySound(TEXT("music/轨迹.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}

		if (cbui->button(530, 100, (wchar_t*)L"  2.Love Story"))
		{
			PlaySound(TEXT("music/LoveStory.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}

		if (cbui->button(150, 250, (wchar_t*)L" 3.最伟大的作品     "))
		{
			PlaySound(TEXT("music/最伟大的作品.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}

		if (cbui->button(530, 250, (wchar_t*)L"     4.透明     "))
		{
			PlaySound(TEXT("music/透明.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}

		if (cbui->button(150, 400, (wchar_t*)L"   5.手写的从前    "))
		{
			PlaySound(TEXT("music/手写的从前.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}

		if (cbui->button(530, 400, (wchar_t*)L"     6.Baby   "))
		{
			PlaySound(TEXT("music/Baby.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}
		// 返回
		if (cbui->button(400, 540, (wchar_t*)L"   返回  "))
			break;

		FlushBatchDraw();
	}
	delete cbui;
	cbui = NULL;						// 删除指针
}