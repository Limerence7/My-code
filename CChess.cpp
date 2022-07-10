// ��Ϸ������
#include "Game.h"				����ͷ�ļ�
// ���и������ڵ��������ĵ�����
int dx[9] = { 6, 88, 176, 264, 352, 440, 528, 615, 700 };
int dy[10] = { 642, 572, 502, 429, 359, 282, 212, 141, 68, 0 };
// ���������ƶ�������
int one[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
int shi[4][2] = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
int ma[8][2] = { {1, 2}, {-1, 2}, {1, -2}, {-1, -2}, {2, 1}, {2, -1}, {-2, 1}, {-2, -1} };
extern MOUSEMSG m_msg;					// �����Ϣ
extern char ch;							// ������Ϣ
extern long long start_time;			// ��Ϸ��ʼʱ��
int ct = 0, turn_on = 0;				// �����������Ƿ�ڹ���
IMAGE bac, all, n1, n2, re, bl, pu, mu, pu2, show;	// ����ͼ��
// ����ͼ��
CChess::CChess()
{
	loadimage(&img[1], TEXT("image/rshuai.png"), 80, 80);
	loadimage(&img[2], TEXT("image/rshi.png"), 80, 80);
	loadimage(&img[3], TEXT("image/rxiang.png"), 80, 80);
	loadimage(&img[4], TEXT("image/rma.png"), 80, 80);
	loadimage(&img[5], TEXT("image/rche.png"), 80, 80);
	loadimage(&img[6], TEXT("image/rpao.png"), 80, 80);
	loadimage(&img[7], TEXT("image/rbing.png"), 80, 80);
	loadimage(&img[8], TEXT("image/bjiang.png"), 80, 80);
	loadimage(&img[9], TEXT("image/bshi.png"), 80, 80);
	loadimage(&img[10], TEXT("image/bxiang.png"), 80, 80);
	loadimage(&img[11], TEXT("image/bma.png"), 80, 80);
	loadimage(&img[12], TEXT("image/bche.png"), 80, 80);
	loadimage(&img[13], TEXT("image/bpao.png"), 80, 80);
	loadimage(&img[14], TEXT("image/bbing.png"), 80, 80);
	loadimage(&all, TEXT("image/all.png"), 80, 80);
	loadimage(&bac, TEXT("image/board.jpg"), 960, 720);
	loadimage(&n1, TEXT("image/prew.png"), 40, 40);
	loadimage(&n2, TEXT("image/preb.png"), 40, 40);
	loadimage(&re, TEXT("image/red.png"), 40, 40);
	loadimage(&bl, TEXT("image/black.png"), 40, 40);
	loadimage(&pu, TEXT("image/pure.png"), 40, 40);
	loadimage(&mu, TEXT("image/music.png"), 80, 80);
	loadimage(&pu2, TEXT("image/pure.png"), 80, 80);
	loadimage(&show, TEXT("image/return.jpg"), 960, 720);
}
// ���ݳ�ʼ��
void CChess::reSet()
{
	// ���������ָ���ͼƬ����32�����ӣ�14������ͼƬ��ָ��
	p[1].x = 4; p[1].y = 0; p[1].to = 1; p[2].x = 3; p[2].y = 0; p[2].to = 2;
	p[3].x = 5; p[3].y = 0; p[3].to = 2; p[4].x = 2; p[4].y = 0; p[4].to = 3;
	p[5].x = 6; p[5].y = 0; p[5].to = 3; p[6].x = 1; p[6].y = 0; p[6].to = 4;
	p[7].x = 7; p[7].y = 0; p[7].to = 4; p[8].x = 0; p[8].y = 0; p[8].to = 5;
	p[9].x = 8; p[9].y = 0; p[9].to = 5; p[10].x = 1; p[10].y = 2; p[10].to = 6;
	p[11].x = 7; p[11].y = 2; p[11].to = 6;
	for (int i = 12; i <= 16; i++)
	{
		p[i].x = (i - 12) * 2;
		p[i].y = 3; p[i].to = 7;
	}
	for (int i = 17; i <= 32; i++)
	{
		p[i].x = p[i - 16].x;
		p[i].y = 9 - p[i - 16].y;
		p[i].to = p[i - 16].to + 7;
	}
	// ��ʼ״̬�������Ӿ�����
	for (int i = 1; i <= 32; i++)
		p[i].u = 1;
	// w��ָ��յ�
	memset(w, 0, sizeof(w));
	// ����w����ָ������
	for (int i = 1; i <= 32; i++)
		w[p[i].x][p[i].y] = i;
	// δ�����δѡ�У��췽�غϣ���Ϸ�Ӵ˿̿�ʼ
	click = 0; slect = 0; turn = 0;
	start_time = int(time(NULL));
}
// ��Ϸ����
void CChess::chesStart()
{
	setbkmode(TRANSPARENT);
	CBuild* bui = new CBuild();

	while (1)
	{
		if (_kbhit())
			ch = _getch();
		while (MouseHit())
			m_msg = GetMouseMsg();

		chesBoard();		// ��������
		// ������ҳ�Լ�������ѡ��
		if (bui->button(820, 600, (wchar_t*)L" ������ҳ "))
		{
			if (bui->putMsg(show, (wchar_t*)L" ȷ��Ҫ������ҳ���� ",
				(wchar_t*)L" �� ", (wchar_t*)L" �� "))
				break;
		}
		// �����Լ�����ѡ��
		if (bui->button(820, 500, (wchar_t*)L"   ���� ") && ct > 0)
		{
			if (bui->putMsg(show, (wchar_t*)L" ȷ��Ҫ������ ",
				(wchar_t*)L" �� ", (wchar_t*)L" �� "))
				pieceRetract();
		}
		// ���ʱ��
		bui->aboutTime();
		// �������ͼ�����ѡ�񱳾�����
		if (choSen(860, 75))
		{
			CMusic* cmu = new CMusic();
			cmu->musicPlay();

			delete cmu;
			cmu = NULL;
		}
		// �����ƶ�
		moveDone();
		// �ж�ʤ��
		if (whoWin())
			break;

		FlushBatchDraw();
		Sleep(5);
	}
	delete bui;
	bui = NULL;
}
// ���̻���/
void CChess::chesBoard()
{
	putimage(0, 0, &bac);
	// ����δ���Ե������
	for (int i = 1; i <= 32; i++)
	{
		if (!p[i].u) continue;			
		putimage(dx[p[i].x], dy[p[i].y], &all, SRCAND);
		putimage(dx[p[i].x], dy[p[i].y], &img[p[i].to], SRCPAINT);
	}
	// ���ѡ������������������ܴﵽ�ĵ�
	for (int i = 1; i <= ltos[0][0]; i++)
	{
		putimage(dx[ltos[i][0]] + 20, dy[ltos[i][1]] + 20, &n1, SRCAND);
		putimage(dx[ltos[i][0]] + 20, dy[ltos[i][1]] + 20, &n2, SRCPAINT);
	}
	// ����ͼ��
	putimage(820, 35, &pu2, SRCAND);
	putimage(820, 35, &mu, SRCPAINT);
	putimage(840, 335, &pu, SRCAND);
	// ��ʾ�췽���Ǻڷ��Ļغ�
	if (turn == 0)
		putimage(840, 335, &re, SRCPAINT);
	else
		putimage(840, 335, &bl, SRCPAINT);
	// ����ոջ��壬��ʾ���������ط������˻���
	if (turn_on)
	{
		putimage(dx[has[0][0]] + 20, dy[has[0][1]] + 20, &n1, SRCAND);
		putimage(dx[has[0][0]] + 20, dy[has[0][1]] + 20, &n2, SRCPAINT);
		putimage(dx[has[1][0]] + 20, dy[has[1][1]] + 20, &n1, SRCAND);
		putimage(dx[has[1][0]] + 20, dy[has[1][1]] + 20, &n2, SRCPAINT);
	}
}
// ����ѡȡ
void CChess::moveDone()
{
	int l;
	// �췽����1~16�� �ڷ�����17~32
	if (turn == 0)
		l = 1;
	else
		l = 17;
	// �˿�û�����ӱ�ѡ��
	if (!click)
	{
		for (int i = l; i <= l + 15; i++)
		{
			if (!p[i].u)
				continue;
			// ������������λ�ã��鿴ѡ�����ĸ�
			if (choSen(dx[p[i].x] + 40, dy[p[i].y] + 40))
			{
				turn_on = 0;		// ���ѡ�������������ʧ
				slect = i;			// slect��ʾѡ�����ӵı��
				click = 1;			// ��ʾ��ѡ��
				showPos();			// �жϸ����ӿɴ�ĵط�
				break;
			}
		}
	}
	else
	{
		for (int i = 1; i <= ltos[0][0]; i++)
		{
			// �����ܵ���ĵط�
			if (choSen(dx[ltos[i][0]] + 40, dy[ltos[i][1]] + 40))
			{
				// ��Ǹò����ӱ䶯��ct++
				int lx = ltos[i][0], ly = ltos[i][1];
				tra[++ct].x1 = p[slect].x; tra[ct].y1 = p[slect].y;
				tra[ct].s1 = slect; tra[ct].x2 = lx;
				tra[ct].y2 = ly; tra[ct].s2 = w[lx][ly];
				// ����������򱻳Ե�
				if (w[lx][ly] > 0)
					p[w[lx][ly]].u = 0;
				// ��������ĸ���
				w[lx][ly] = slect;					// ��ͼ�ı�
				w[p[slect].x][p[slect].y] = 0;		// ��ͼ�ı�
				p[slect].x = lx; p[slect].y = ly;	// �ñ�����Ӹı�
				// �켣���㣬δ�����δѡ�У�����
				ltos[0][0] = 0; click = 0; slect = 0; turn = 1 - turn;
				break;
			}
		}
		// ������������һ�еط���ѡ��״̬��Ϊδѡ��״̬
		if (click == 1 && m_msg.uMsg == WM_LBUTTONUP)
		{
			m_msg.uMsg = WM_MOUSEMOVE;				// ��ֹ���ε��
			click = 0; slect = 0; ltos[0][0] = 0;
		}
	}
}
// �ж��Ƿ�ѡ��
bool CChess::choSen(int x, int y)
{
	static int Mx, My;
	Mx = m_msg.x;
	My = m_msg.y;
	// �����������Բ��
	if ((Mx - x) * (Mx - x) + (My - y) * (My - y) < 1600)
	{
		if (m_msg.uMsg == WM_LBUTTONUP)		// ��������˵��
		{
			m_msg.uMsg = WM_MOUSEMOVE;
			return 1;
		}
	}
	return 0;
}
// �ҵ����пɵ����·��
void CChess::showPos()
{
	ltos[0][0] = 0;
	int i;
	// ��˧
	if (p[slect].to == 1 || p[slect].to == 8)
	{
		for (i = 0; i < 4; i++)
		{
			int px = p[slect].x + one[i][0];
			int py = p[slect].y + one[i][1];
			if (px < 3 || px > 5 || py < 0 || py > 9)
				continue;
			if (p[slect].to == 1 && py > 2) continue;
			if (p[slect].to == 8 && py < 7) continue;
			if (w[px][py] && ((slect <= 16 && w[px][py] <= 16) ||
				(slect > 16 && w[px][py] > 16))) continue;
			ltos[++ltos[0][0]][0] = px;
			ltos[ltos[0][0]][1] = py;
		}
		return;
	}
	// ʿ
	if (p[slect].to == 2 || p[slect].to == 9)
	{
		for (i = 0; i < 4; i++)
		{
			int px = p[slect].x + shi[i][0];
			int py = p[slect].y + shi[i][1];
			if (px < 3 || px > 5 || py < 0 || py > 9)
				continue;
			if (p[slect].to == 2 && py > 2) continue;
			if (p[slect].to == 9 && py < 7) continue;
			if (w[px][py] && ((slect <= 16 && w[px][py] <= 16) ||
				(slect > 16 && w[px][py] > 16))) continue;
			ltos[++ltos[0][0]][0] = px;
			ltos[ltos[0][0]][1] = py;
		}
		return;
	}
	// ��
	if (p[slect].to == 3 || p[slect].to == 10)
	{
		for (i = 0; i < 4; i++)
		{
			int px = p[slect].x + 2 * shi[i][0];
			int py = p[slect].y + 2 * shi[i][1];
			if (px < 0 || px > 8 || py < 0 || py > 9)
				continue;
			if (p[slect].to == 3 && py > 4) continue;
			if (p[slect].to == 10 && py < 5) continue;
			if (w[p[slect].x + shi[i][0]][p[slect].y + shi[i][1]] > 0) continue;
			if (w[px][py] && ((slect <= 16 && w[px][py] <= 16) ||
				(slect > 16 && w[px][py] > 16))) continue;
			ltos[++ltos[0][0]][0] = px;
			ltos[ltos[0][0]][1] = py;
		}
		return;
	}
	// ��
	if (p[slect].to == 4 || p[slect].to == 11)
	{
		for (i = 0; i < 8; i++)
		{
			int px = p[slect].x + ma[i][0];
			int py = p[slect].y + ma[i][1];
			if (px < 0 || px > 8 || py < 0 || py > 9)
				continue;
			if (w[p[slect].x + one[i / 2][0]][p[slect].y + one[i / 2][1]] > 0) 
				continue;
			if (w[px][py] && ((slect <= 16 && w[px][py] <= 16) ||
				(slect > 16 && w[px][py] > 16))) continue;
			ltos[++ltos[0][0]][0] = px;
			ltos[ltos[0][0]][1] = py;
		}
		return;
	}
	// ��
	if (p[slect].to == 5 || p[slect].to == 12)
	{
		for (i = 0; i < 4; i++)
		{
			int px = p[slect].x + one[i][0];
			int py = p[slect].y + one[i][1];
			while (px >= 0 && px <= 8 && py >= 0 && py <= 9)
			{
				if (w[px][py] > 0)
				{
					if ((slect <= 16 && w[px][py] <= 16) || (slect > 16 && w[px][py] > 16))
						break;
					else
					{
						ltos[++ltos[0][0]][0] = px;
						ltos[ltos[0][0]][1] = py;
						break;
					}
				}
				ltos[++ltos[0][0]][0] = px;
				ltos[ltos[0][0]][1] = py;
				px += one[i][0];
				py += one[i][1];
			}
		}
		return;
	}
	// ��
	if (p[slect].to == 6 || p[slect].to == 13)
	{
		for (i = 0; i < 4; i++)
		{
			int px = p[slect].x + one[i][0];
			int py = p[slect].y + one[i][1];
			while (px >= 0 && px <= 8 && py >= 0 && py <= 9)
			{
				if (w[px][py] > 0)
				{
					px += one[i][0];
					py += one[i][1];
					while (px >= 0 && px <= 8 && py >= 0 && py <= 9)
					{
						if (w[px][py] && ((slect <= 16 && w[px][py] > 16) ||
							(slect > 16 && w[px][py] <= 16)))
						{
							ltos[++ltos[0][0]][0] = px;
							ltos[ltos[0][0]][1] = py;
							break;
						}
						px += one[i][0];
						py += one[i][1];
					}
					break;
				}
				ltos[++ltos[0][0]][0] = px;
				ltos[ltos[0][0]][1] = py;
				px += one[i][0];
				py += one[i][1];
			}
		}
		return;
	}
	// ��
	if (p[slect].to == 7 || p[slect].to == 14)
	{
		int ee = 2;
		if (p[slect].to == 7 && p[slect].y > 4) ee = 4;
		if (p[slect].to == 14 && p[slect].y < 5) ee = 4;
		for (i = 0; i < ee; i++)
		{
			int px = p[slect].x + one[i][0];
			int py = p[slect].y + one[i][1];
			if (px < 0 || px > 8 || py < 0 || py > 9)
				continue;
			if (p[slect].to == 7 && i == 1) continue;
			if (p[slect].to == 14 && i == 0) continue;
			if (w[px][py] && ((slect <= 16 && w[px][py] <= 16) ||
				(slect > 16 && w[px][py] > 16))) continue;
			ltos[++ltos[0][0]][0] = px;
			ltos[ltos[0][0]][1] = py;
		}
		return;
	}
}
// �ж���Ϸ�Ƿ����
bool CChess::whoWin()
{
	CBuild* bui = new CBuild();
	bool check;
	if (p[1].u == 0 || p[17].u == 0)
	{
		// ��ʤ
		if (p[1].u == 0)
		{
			check = bui->putMsg(show, (wchar_t*)L" �ڷ������ʤ�� ",
				(wchar_t*)L" ����һ�� ", (wchar_t*)L" ������ҳ��  ");
		}
		// ��ʤ
		else
		{
			check = bui->putMsg(show, (wchar_t*)L" �췽�����ʤ�� ",
				(wchar_t*)L" ����һ�� ", (wchar_t*)L" ������ҳ��  ");
		}
		// ����ؿ�������reSet��������
		if (check)
		{
			reSet();
			return 0;
		}
		// ����������˵���ֱ�ӷ��أ�������ָ��ʱ�Զ�����
		else
		{
			slect = 0; click = 0; turn = 0;
			return 1;
		}
	}
	return 0;

	delete bui;
	bui = NULL;
}
// ����
void CChess::pieceRetract()
{
	turn_on = 1;						// ����������ǻ���˫��
	// �޸�˫�����Ӳ���
	has[0][0] = tra[ct].x1; has[0][1] = tra[ct].y1;
	has[1][0] = tra[ct].x2; has[1][1] = tra[ct].y2;
	p[tra[ct].s1].x = tra[ct].x1; p[tra[ct].s1].y = tra[ct].y1; 
	w[tra[ct].x1][tra[ct].y1] = tra[ct].s1;
	// ����߹���λ���ǿյأ����±�ǿյؾͺ�
	if (tra[ct].s2 == 0)
		w[tra[ct].x2][tra[ct].y2] = 0;
	// ������������޸����Ӳ��������Ϊδ���Ե�
	else
	{
		p[tra[ct].s2].x = tra[ct].x2; p[tra[ct].s2].y = tra[ct].y2;
		w[tra[ct].x2][tra[ct].y2] = tra[ct].s2;
		p[tra[ct].s2].u = 1;
	}
	//���ݸı�
	ct--; ltos[0][0] = 0;
	click = 0; turn = 1 - turn; slect = 0;
}