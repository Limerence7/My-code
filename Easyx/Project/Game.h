// ��Ϸͷ�ļ�
#pragma once

#include "Chess.h"					// ����Chessͷ�ļ�

// ͼ����
class CBuild
{
public:
	CBuild() {}
	~CBuild() {}
	void beginMode();							// ���Ƴ�ʼ��屳��
	bool button(int a, int b, wchar_t str[]);	// ���ư�ť
	void putSpa(int mode, wchar_t str[], int row, wchar_t* tex[]); // ��ӡ����
	// �����ť���������ѡ��
	bool putMsg(IMAGE& ig, wchar_t str[], wchar_t str1[], wchar_t str2[]);
	void aboutTime();							// ��ӡʱ��
};
// ������
class CPlay
{
public:
	CPlay() {}
	~CPlay() {}
	void Game();			// ������Ϸ����
};
// ��Ƶ��
class CMusic
{
public:
	CMusic() {}
	~CMusic() {}
	void musicPlay();		// �����������ֵĲ���
};
// ��Ϸ������
class CChess
{
public:
	CChess();						// ����ͼ��
	~CChess() {}
	void reSet();					// ���ݳ�ʼ��
	void chesStart();				// ��Ϸ����
	void chesBoard();				// ���̻���
	void moveDone();				// ����ѡȡ
	bool choSen(int x, int y);		// �ж��Ƿ�ѡ��
	void showPos();					// �ҵ����пɵ����·��
	bool whoWin();					// �ж���Ϸ�Ƿ����
	void pieceRetract();			// ����
private:
	int click = 0, slect = 0, turn = 0; // �Ƿ�ѡȡ��ѡ������ӣ���ڷ�
	IMAGE img[15];						// ����14������
	struct pos
	{
		int x, y, to;
		bool u;
	}p[33];								// �������ָ꣬��ͼ���Լ��Ƿ����
	struct retract
	{
		int x1, y1, s1;
		int x2, y2, s2;
	}tra[1000];							// ��������ӵ�����ͱ��
	int w[9][10], ltos[40][2];			// ������������(�յ�), �ɴ�·����¼
	int has[2][2];						// �����˫��������
};