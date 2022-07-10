// ������ͷ�ļ�
#include "Game.h"

char ch;							// ������Ϣ
MOUSEMSG m_msg;						// �����Ϣ
// ������Ϸ����
void CPlay::Game()
{
	CBuild* bui = new CBuild();		// ����CBuildָ��
	
	setbkmode(TRANSPARENT);			// ���ñ���ģʽ

	BeginBatchDraw();

	while (1)
	{
		if (_kbhit())
		{
			ch = _getch();			// ��ȡ������Ϣ
			if (ch == 27)
				break;				// ESC�˳�
		}
		while (MouseHit())
			m_msg = GetMouseMsg();	// ��ȡ�����Ϣ

		bui->beginMode();			// ���Ƴ�ʼ����

		for (int i = 0; i <= 3; i++)
		{
			settextcolor(RGB(255, 200, 90));
			settextstyle(70, 0, TEXT("�п�"));
			outtextxy(360 + i, 20 + i, TEXT("�й�����"));
		}
		settextcolor(RGB(210, 105, 30));
		outtextxy(360 + 4, 20 + 4, TEXT("�й�����"));		// ��������

		if (bui->button(20, 480, (wchar_t*)L"  ��ʼ��Ϸ  ")) // ��ʼ��Ϸ
		{
			CChess* che = new CChess();					    // ���캯��
			che->reSet();									//	��ʼ��
			che->chesStart();

			delete che;
			che = NULL;
		}

		if (bui->button(20, 560, (wchar_t*)L"  ��������  "))	// ��������
		{
			CMusic* msc = new CMusic();
			msc->musicPlay();

			delete msc;
			msc = NULL;
		}

		if (bui->button(780, 480, (wchar_t*)L"   ��  ��    "))
		{
			wchar_t* str1[5];
			str1[0] = (wchar_t*)L"��������Ϸ����C++��д";
			str1[1] = (wchar_t*)L"ͨ��EasyX��ͼ�ο����";
			str1[2] = (wchar_t*)L"�����ʼ��ť���ɿ�ʼ��Ϸ";
			str1[3] = (wchar_t*)L"Ҳ����ѡ��������";
			str1[4] = (wchar_t*)L"ͨ�����ʵ�����ӵ��ƶ�";
			bui->putSpa(1, (wchar_t*)L"   ��  ��   ", 5, str1);		//��ӡ����
		}

		if (bui->button(780, 560, (wchar_t*)L"  �����Ŷ�  "))
		{
			wchar_t* str2[3];
			str2[0] = (wchar_t*)L"�������ѧ�뼼��  216��";
			str2[1] = (wchar_t*)L"�� ˼ �� ";
			str2[2] = (wchar_t*)L"�� � �� ";
			bui->putSpa(0, (wchar_t*)L"  �����Ŷ�  ", 3, str2);		// ��ӡ����
		}

		LOGFONT f;
		gettextstyle(&f);
		f.lfHeight = 40;
		f.lfWidth = 20;
		f.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&f);
		setcolor(RGB(244, 164, 96));						// ��������

		outtextxy(360, 560, TEXT("��ESC�˳���Ϸ"));
		outtextxy(640, 70, TEXT("Version: 1.0"));				// ��������

		FlushBatchDraw();
		Sleep(5);
	}

	EndBatchDraw();									// ��������

	delete bui;
	bui = NULL;										// ɾ��ָ��
}