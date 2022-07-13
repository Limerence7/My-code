// 图案文字头文件

#include "Game.h"
extern char ch;
extern MOUSEMSG m_msg;
SYSTEMTIME ti;
long long on_time, start_time;
// 加载初始界面图片
void CBuild::beginMode()
{
	IMAGE img;
	loadimage(&img, TEXT("image/ground.jpg"), 960, 720);
	putimage(0, 0, &img);							 // 加载并打印背景图片
}
// 加载按钮
bool CBuild::button(int a, int b, wchar_t str[])
{
	static int x, y;

	setfillcolor(RGB(244, 164, 96));
	solidrectangle(a - 25, b, a + 19 * wcslen(str) + 25, b + 60); // 绘制边框

	x = m_msg.x;
	y = m_msg.y;								// 获取鼠标坐标
	if (x > a - 25 && (size_t)x < a + 19 * wcslen(str) + 25 && y > b && y < b + 60)
	{
		// 鼠标移动到该区域绘制浅边框
		setfillcolor(RGB(255, 200, 150));
		solidrectangle(a - 25, b, a + 19 * wcslen(str) + 25, b + 60);
		if (m_msg.uMsg == WM_LBUTTONUP)
		{
			m_msg.uMsg = WM_MOUSEMOVE;

			return 1;
		}
	}											// 判断是否点击
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 40;
	f.lfWidth = 20;
	f.lfQuality = ANTIALIASED_QUALITY;
	wcscpy_s(f.lfFaceName, L"黑体");
	settextstyle(&f);
	settextcolor(WHITE);
	outtextxy(a - 40, b + 10, str);				// 调整字体并输出文字

	return 0;
}
// 帮助和制作团队界面 
void CBuild::putSpa(int mode, wchar_t str[], int row, wchar_t* tex[])
{
	while (1)
	{
		while (MouseHit())
			m_msg = GetMouseMsg();

		beginMode();						  // 清除界面，只留初始背景图片

		IMAGE img;
		if (!mode)
			loadimage(&img, TEXT("image/shuai.png"), 760, 570);
		else
			loadimage(&img, TEXT("image/jiang.png"), 760, 570);
		putimage(100, 35, &img);							// 加载背景图片
		// 制作标题
		for (int i = 0; i <= 3; i++)
		{
			settextcolor(RGB(200, 200, 200));
			settextstyle(70, 0, TEXT("行楷"));
			outtextxy(280 + i, 20 + i, str);
		}
		settextcolor(WHITE);
		outtextxy(280 + 4, 20 + 4, str);
		// 正文内容
		LOGFONT f;
		gettextstyle(&f);
		f.lfHeight = 36;
		f.lfWidth = 20;
		wcscpy_s(f.lfFaceName, L"黑体");
		f.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&f);
		for (int i = 0; i < row; i++)
		{
			outtextxy(100 + 20, 120 + i * 70, tex[i]);
		}

		if (button(400, 540, (wchar_t*)L"  返回主页  "))
			break;

		FlushBatchDraw();
	}
}
// 点击按钮后出现两个选项
bool CBuild::putMsg(IMAGE& ig, wchar_t str[], wchar_t str1[], wchar_t str2[])
{
	putimage(0, 0, &ig);						// 输出指定图片
	while (1)
	{
		while (MouseHit())
			m_msg = GetMouseMsg();
		// 打印标题内容
		LOGFONT f;
		gettextstyle(&f);
		f.lfHeight = 80;
		f.lfWidth = 26;
		wcscpy_s(f.lfFaceName, L"华文行楷");
		f.lfQuality = ANTIALIASED_QUALITY;
		settextcolor(WHITE);
		settextstyle(&f);
		outtextxy(100, 40, str);
		// 出现两个选项
		if (button(150, 540, str1))
			return 1;
		if (button(690, 540, str2))
			return 0;

		FlushBatchDraw();
	}
	return 0;
}
// 打印时间
void CBuild::aboutTime()
{
	wchar_t clock[30], pass[30];			 // 游戏时间和此刻时间数组
	//获取时间
	GetLocalTime(&ti);
	on_time = int(time(NULL));
	int ots = on_time - start_time;
	// 游戏时间
	swprintf_s(pass, L" %02d 分 %02d 秒 ", ots / 60, ots % 60);
	// 此刻时间
	swprintf_s(clock, L" %02d : %02d : %02d ", ti.wHour, ti.wMinute, ti.wSecond);
	// 调整字体
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 30;
	f.lfWidth = 15;
	f.lfQuality = ANTIALIASED_QUALITY;
	wcscpy_s(f.lfFaceName, L"黑体");
	settextstyle(&f);
	settextcolor(WHITE);
	// 输出相应数组
	outtextxy(760, 130, L"游戏总时长为: ");
	outtextxy(770, 170, pass);
	outtextxy(770, 235, L" 当前时间为: ");
	outtextxy(750, 275, clock);
}