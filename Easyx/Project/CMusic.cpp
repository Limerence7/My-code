// ��Ƶ��
#include "Game.h"

extern char ch;
extern MOUSEMSG m_msg;
// �����������ֵĲ���
void CMusic::musicPlay()
{
	CBuild* cbui = new CBuild();
	while (1)
	{
		while (MouseHit())
			m_msg = GetMouseMsg();
		cbui->beginMode();								// ����ͼƬ

		for (int i = 0; i <= 3; i++)
		{
			settextcolor(RGB(200, 200, 200));
			settextstyle(70, 0, TEXT("�п�"));
			outtextxy(280 + i, 20 + i, L"  ��������  ");
		}

		settextcolor(WHITE);
		outtextxy(280 + 4, 20 + 4, L"  ��������  ");      // ��������
		// ��������ѡ��
		if (cbui->button(150, 100, (wchar_t*)L"     1.�켣     "))
		{
			PlaySound(TEXT("music/�켣.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}

		if (cbui->button(530, 100, (wchar_t*)L"  2.Love Story"))
		{
			PlaySound(TEXT("music/LoveStory.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}

		if (cbui->button(150, 250, (wchar_t*)L" 3.��ΰ�����Ʒ     "))
		{
			PlaySound(TEXT("music/��ΰ�����Ʒ.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}

		if (cbui->button(530, 250, (wchar_t*)L"     4.͸��     "))
		{
			PlaySound(TEXT("music/͸��.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}

		if (cbui->button(150, 400, (wchar_t*)L"   5.��д�Ĵ�ǰ    "))
		{
			PlaySound(TEXT("music/��д�Ĵ�ǰ.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}

		if (cbui->button(530, 400, (wchar_t*)L"     6.Baby   "))
		{
			PlaySound(TEXT("music/Baby.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}
		// ����
		if (cbui->button(400, 540, (wchar_t*)L"   ����  "))
			break;

		FlushBatchDraw();
	}
	delete cbui;
	cbui = NULL;						// ɾ��ָ��
}