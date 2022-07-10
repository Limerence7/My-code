// 游戏棋盘类
#include "Game.h"				包含头文件
// 各行各列所在的棋盘中心点坐标
int dx[9] = { 6, 88, 176, 264, 352, 440, 528, 615, 700 };
int dy[10] = { 642, 572, 502, 429, 359, 282, 212, 141, 68, 0 };
// 各个棋子移动的数组
int one[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
int shi[4][2] = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
int ma[8][2] = { {1, 2}, {-1, 2}, {1, -2}, {-1, -2}, {2, 1}, {2, -1}, {-2, 1}, {-2, -1} };
extern MOUSEMSG m_msg;					// 鼠标信息
extern char ch;							// 键盘信息
extern long long start_time;			// 游戏开始时间
int ct = 0, turn_on = 0;				// 步数数量、是否悔过棋
IMAGE bac, all, n1, n2, re, bl, pu, mu, pu2, show;	// 其他图标
// 加载图形
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
// 数据初始化
void CChess::reSet()
{
	// 棋子坐标和指向的图片，共32个棋子，14个棋子图片的指向
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
	// 初始状态所有棋子均存在
	for (int i = 1; i <= 32; i++)
		p[i].u = 1;
	// w均指向空地
	memset(w, 0, sizeof(w));
	// 部分w数组指向棋子
	for (int i = 1; i <= 32; i++)
		w[p[i].x][p[i].y] = i;
	// 未点击，未选中，红方回合，游戏从此刻开始
	click = 0; slect = 0; turn = 0;
	start_time = int(time(NULL));
}
// 游戏核心
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

		chesBoard();		// 绘制棋盘
		// 返回主页以及点击后的选项
		if (bui->button(820, 600, (wchar_t*)L" 返回主页 "))
		{
			if (bui->putMsg(show, (wchar_t*)L" 确定要返回主页面吗 ",
				(wchar_t*)L" 是 ", (wchar_t*)L" 否 "))
				break;
		}
		// 悔棋以及两个选项
		if (bui->button(820, 500, (wchar_t*)L"   悔棋 ") && ct > 0)
		{
			if (bui->putMsg(show, (wchar_t*)L" 确定要悔棋吗 ",
				(wchar_t*)L" 是 ", (wchar_t*)L" 否 "))
				pieceRetract();
		}
		// 输出时间
		bui->aboutTime();
		// 点击音乐图标则可选择背景音乐
		if (choSen(860, 75))
		{
			CMusic* cmu = new CMusic();
			cmu->musicPlay();

			delete cmu;
			cmu = NULL;
		}
		// 棋子移动
		moveDone();
		// 判断胜负
		if (whoWin())
			break;

		FlushBatchDraw();
		Sleep(5);
	}
	delete bui;
	bui = NULL;
}
// 棋盘绘制/
void CChess::chesBoard()
{
	putimage(0, 0, &bac);
	// 棋子未被吃掉则绘制
	for (int i = 1; i <= 32; i++)
	{
		if (!p[i].u) continue;			
		putimage(dx[p[i].x], dy[p[i].y], &all, SRCAND);
		putimage(dx[p[i].x], dy[p[i].y], &img[p[i].to], SRCPAINT);
	}
	// 如果选择了棋子则绘制它可能达到的点
	for (int i = 1; i <= ltos[0][0]; i++)
	{
		putimage(dx[ltos[i][0]] + 20, dy[ltos[i][1]] + 20, &n1, SRCAND);
		putimage(dx[ltos[i][0]] + 20, dy[ltos[i][1]] + 20, &n2, SRCPAINT);
	}
	// 音乐图标
	putimage(820, 35, &pu2, SRCAND);
	putimage(820, 35, &mu, SRCPAINT);
	putimage(840, 335, &pu, SRCAND);
	// 显示红方还是黑方的回合
	if (turn == 0)
		putimage(840, 335, &re, SRCPAINT);
	else
		putimage(840, 335, &bl, SRCPAINT);
	// 如果刚刚悔棋，显示是哪两个地方发生了悔棋
	if (turn_on)
	{
		putimage(dx[has[0][0]] + 20, dy[has[0][1]] + 20, &n1, SRCAND);
		putimage(dx[has[0][0]] + 20, dy[has[0][1]] + 20, &n2, SRCPAINT);
		putimage(dx[has[1][0]] + 20, dy[has[1][1]] + 20, &n1, SRCAND);
		putimage(dx[has[1][0]] + 20, dy[has[1][1]] + 20, &n2, SRCPAINT);
	}
}
// 棋子选取
void CChess::moveDone()
{
	int l;
	// 红方棋子1~16， 黑方棋子17~32
	if (turn == 0)
		l = 1;
	else
		l = 17;
	// 此刻没有棋子被选中
	if (!click)
	{
		for (int i = l; i <= l + 15; i++)
		{
			if (!p[i].u)
				continue;
			// 遍历所有棋子位置，查看选择是哪个
			if (choSen(dx[p[i].x] + 40, dy[p[i].y] + 40))
			{
				turn_on = 0;		// 如果选中了则悔棋标记消失
				slect = i;			// slect表示选中棋子的编号
				click = 1;			// 表示已选中
				showPos();			// 判断该棋子可达的地方
				break;
			}
		}
	}
	else
	{
		for (int i = 1; i <= ltos[0][0]; i++)
		{
			// 找它能到达的地方
			if (choSen(dx[ltos[i][0]] + 40, dy[ltos[i][1]] + 40))
			{
				// 标记该步棋子变动，ct++
				int lx = ltos[i][0], ly = ltos[i][1];
				tra[++ct].x1 = p[slect].x; tra[ct].y1 = p[slect].y;
				tra[ct].s1 = slect; tra[ct].x2 = lx;
				tra[ct].y2 = ly; tra[ct].s2 = w[lx][ly];
				// 如果是棋子则被吃掉
				if (w[lx][ly] > 0)
					p[w[lx][ly]].u = 0;
				// 进行数组的更改
				w[lx][ly] = slect;					// 地图改变
				w[p[slect].x][p[slect].y] = 0;		// 地图改变
				p[slect].x = lx; p[slect].y = ly;	// 该编号棋子改变
				// 轨迹归零，未点击，未选中，换方
				ltos[0][0] = 0; click = 0; slect = 0; turn = 1 - turn;
				break;
			}
		}
		// 如果点击轨道外的一切地方则将选中状态改为未选中状态
		if (click == 1 && m_msg.uMsg == WM_LBUTTONUP)
		{
			m_msg.uMsg = WM_MOUSEMOVE;				// 防止二次点击
			click = 0; slect = 0; ltos[0][0] = 0;
		}
	}
}
// 判断是否选中
bool CChess::choSen(int x, int y)
{
	static int Mx, My;
	Mx = m_msg.x;
	My = m_msg.y;
	// 在中心坐标的圆上
	if ((Mx - x) * (Mx - x) + (My - y) * (My - y) < 1600)
	{
		if (m_msg.uMsg == WM_LBUTTONUP)		// 如果发生了点击
		{
			m_msg.uMsg = WM_MOUSEMOVE;
			return 1;
		}
	}
	return 0;
}
// 找到所有可到达的路径
void CChess::showPos()
{
	ltos[0][0] = 0;
	int i;
	// 将帅
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
	// 士
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
	// 相
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
	// 马
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
	// 车
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
	// 炮
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
	// 兵
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
// 判断游戏是否结束
bool CChess::whoWin()
{
	CBuild* bui = new CBuild();
	bool check;
	if (p[1].u == 0 || p[17].u == 0)
	{
		// 黑胜
		if (p[1].u == 0)
		{
			check = bui->putMsg(show, (wchar_t*)L" 黑方获得了胜利 ",
				(wchar_t*)L" 再来一局 ", (wchar_t*)L" 返回主页面  ");
		}
		// 红胜
		else
		{
			check = bui->putMsg(show, (wchar_t*)L" 红方获得了胜利 ",
				(wchar_t*)L" 再来一局 ", (wchar_t*)L" 返回主页面  ");
		}
		// 如果重开，则用reSet重置数据
		if (check)
		{
			reSet();
			return 0;
		}
		// 如果返回主菜单，直接返回，创建新指针时自动重置
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
// 悔棋
void CChess::pieceRetract()
{
	turn_on = 1;						// 待会用来标记悔棋双方
	// 修改双方棋子参数
	has[0][0] = tra[ct].x1; has[0][1] = tra[ct].y1;
	has[1][0] = tra[ct].x2; has[1][1] = tra[ct].y2;
	p[tra[ct].s1].x = tra[ct].x1; p[tra[ct].s1].y = tra[ct].y1; 
	w[tra[ct].x1][tra[ct].y1] = tra[ct].s1;
	// 如果走过的位置是空地，重新标记空地就好
	if (tra[ct].s2 == 0)
		w[tra[ct].x2][tra[ct].y2] = 0;
	// 如果是棋子则修改棋子参数，标记为未被吃掉
	else
	{
		p[tra[ct].s2].x = tra[ct].x2; p[tra[ct].s2].y = tra[ct].y2;
		w[tra[ct].x2][tra[ct].y2] = tra[ct].s2;
		p[tra[ct].s2].u = 1;
	}
	//数据改变
	ct--; ltos[0][0] = 0;
	click = 0; turn = 1 - turn; slect = 0;
}