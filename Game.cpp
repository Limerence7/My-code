// ���򿪶��ļ�

#include "Game.h"			// ������Ϸͷ�ļ�

//������
int main()
{
	srand((unsigned int)time(NULL));		//�������

	initgraph(960, 720);					//��ʼ����Ϸ����

	CPlay* First = new CPlay();				
	First->Game();							// ��ʼ��Ϸ

	delete First;
	First = NULL;							// ɾ��ָ��

	_getch();
	closegraph();							
	return 0;								//�ر���Ϸ����
}