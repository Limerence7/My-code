// ͼ������ͷ�ļ�

#include "Game.h"
extern char ch;
extern MOUSEMSG m_msg;
SYSTEMTIME ti;
long long on_time, start_time;
// ���س�ʼ����ͼƬ
void CBuild::beginMode()
{
	IMAGE img;
	loadimage(&img, TEXT("image/ground.jpg"), 960, 720);
	putimage(0, 0, &img);							 // ���ز���ӡ����ͼƬ
}
// ���ذ�ť
bool CBuild::button(int a, int b, wchar_t str[])
{
	static int x, y;

	setfillcolor(RGB(244, 164, 96));
	solidrectangle(a - 25, b, a + 19 * wcslen(str) + 25, b + 60); // ���Ʊ߿�

	x = m_msg.x;
	y = m_msg.y;								// ��ȡ�������
	if (x > a - 25 && (size_t)x < a + 19 * wcslen(str) + 25 && y > b && y < b + 60)
	{
		// ����ƶ������������ǳ�߿�
		setfillcolor(RGB(255, 200, 150));
		solidrectangle(a - 25, b, a + 19 * wcslen(str) + 25, b + 60);
		if (m_msg.uMsg == WM_LBUTTONUP)
		{
			m_msg.uMsg = WM_MOUSEMOVE;

			return 1;
		}
	}											// �ж��Ƿ���
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 40;
	f.lfWidth = 20;
	f.lfQuality = ANTIALIASED_QUALITY;
	wcscpy_s(f.lfFaceName, L"����");
	settextstyle(&f);
	settextcolor(WHITE);
	outtextxy(a - 40, b + 10, str);				// �������岢�������

	return 0;
}
// �����������Ŷӽ��� 
void CBuild::putSpa(int mode, wchar_t str[], int row, wchar_t* tex[])
{
	while (1)
	{
		while (MouseHit())
			m_msg = GetMouseMsg();

		beginMode();						  // ������棬ֻ����ʼ����ͼƬ

		IMAGE img;
		if (!mode)
			loadimage(&img, TEXT("image/shuai.png"), 760, 570);
		else
			loadimage(&img, TEXT("image/jiang.png"), 760, 570);
		putimage(100, 35, &img);							// ���ر���ͼƬ
		// ��������
		for (int i = 0; i <= 3; i++)
		{
			settextcolor(RGB(200, 200, 200));
			settextstyle(70, 0, TEXT("�п�"));
			outtextxy(280 + i, 20 + i, str);
		}
		settextcolor(WHITE);
		outtextxy(280 + 4, 20 + 4, str);
		// ��������
		LOGFONT f;
		gettextstyle(&f);
		f.lfHeight = 36;
		f.lfWidth = 20;
		wcscpy_s(f.lfFaceName, L"����");
		f.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&f);
		for (int i = 0; i < row; i++)
		{
			outtextxy(100 + 20, 120 + i * 70, tex[i]);
		}

		if (button(400, 540, (wchar_t*)L"  ������ҳ  "))
			break;

		FlushBatchDraw();
	}
}
// �����ť���������ѡ��
bool CBuild::putMsg(IMAGE& ig, wchar_t str[], wchar_t str1[], wchar_t str2[])
{
	putimage(0, 0, &ig);						// ���ָ��ͼƬ
	while (1)
	{
		while (MouseHit())
			m_msg = GetMouseMsg();
		// ��ӡ��������
		LOGFONT f;
		gettextstyle(&f);
		f.lfHeight = 80;
		f.lfWidth = 26;
		wcscpy_s(f.lfFaceName, L"�����п�");
		f.lfQuality = ANTIALIASED_QUALITY;
		settextcolor(WHITE);
		settextstyle(&f);
		outtextxy(100, 40, str);
		// ��������ѡ��
		if (button(150, 540, str1))
			return 1;
		if (button(690, 540, str2))
			return 0;

		FlushBatchDraw();
	}
	return 0;
}
// ��ӡʱ��
void CBuild::aboutTime()
{
	wchar_t clock[30], pass[30];			 // ��Ϸʱ��ʹ˿�ʱ������
	//��ȡʱ��
	GetLocalTime(&ti);
	on_time = int(time(NULL));
	int ots = on_time - start_time;
	// ��Ϸʱ��
	swprintf_s(pass, L" %02d �� %02d �� ", ots / 60, ots % 60);
	// �˿�ʱ��
	swprintf_s(clock, L" %02d : %02d : %02d ", ti.wHour, ti.wMinute, ti.wSecond);
	// ��������
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 30;
	f.lfWidth = 15;
	f.lfQuality = ANTIALIASED_QUALITY;
	wcscpy_s(f.lfFaceName, L"����");
	settextstyle(&f);
	settextcolor(WHITE);
	// �����Ӧ����
	outtextxy(760, 130, L"��Ϸ��ʱ��Ϊ: ");
	outtextxy(770, 170, pass);
	outtextxy(770, 235, L" ��ǰʱ��Ϊ: ");
	outtextxy(750, 275, clock);
}