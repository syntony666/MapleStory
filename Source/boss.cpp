#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "boss.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Boss: class
	/////////////////////////////////////////////////////////////////////////////

	Boss::~Boss() {
	}

	void Boss::Initialize()
	{
		bossStand.LoadBitmap(IDB_BOSS_STAND, RGB(50, 100, 100));
		isMovingRight = isMovingLeft = false;
		pos_x = 1700;
		pos_y = -30;
	}

	void Boss::OnMove()
	{
		if (isDead)
			return;

		//bossStand.OnMove();
		if (isMovingRight) {
			pos_x -= HERO_STEP;
		}
		else if (isMovingLeft) {
			pos_x += HERO_STEP;
		}
	}

	void Boss::OnShow()
	{
		if (!isDead) {
			bossStand.SetTopLeft(pos_x, pos_y);
			bossStand.ShowBitmap();
		}
	}

	void Boss::setMovingLeft(bool flag) {
		isMovingLeft = flag;
	}
	void Boss::setMovingRight(bool flag) {
		isMovingRight = flag;
	}

	void Boss::setXY(int nx, int ny)
	{
		pos_x = nx; pos_y = ny;
	}
	void Boss::showHPBar(int percent)
	{
		const int bar_width = SIZE_X - 100;
		const int bar_height = 15;
		const int x1 = SIZE_X - bar_width;
		const int x2 = x1 + bar_width;
		const int y1 = bar_height + 3;
		const int y2 = y1 + bar_height;
		const int pen_width = bar_height / 8;
		const int progress_x1 = x1 + pen_width;
		const int progress_x2 = progress_x1 + percent * (bar_width - 2 * pen_width) / 100;
		const int progress_x2_end = x2 - pen_width;
		const int progress_y1 = y1 + pen_width;
		const int progress_y2 = y2 - pen_width;
		//
		// 以下為CDC的用法
		//
		CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
		CPen *pp, p(PS_NULL, 0, RGB(0, 0, 0));		// 清除pen
		pp = pDC->SelectObject(&p);

		CBrush *pb, b(RGB(0, 255, 0));				// 畫綠色 progress框
		pb = pDC->SelectObject(&b);
		pDC->Rectangle(x1, y1, x2, y2);

		CBrush b1(DEFAULT_BG_COLOR);				// 畫黑色 progrss中心
		pDC->SelectObject(&b1);
		pDC->Rectangle(progress_x1, progress_y1, progress_x2_end, progress_y2);

		CBrush b2(RGB(255, 255, 0));					// 畫黃色 progrss進度
		pDC->SelectObject(&b2);
		pDC->Rectangle(progress_x1, progress_y1, progress_x2, progress_y2);

		pDC->SelectObject(pp);						// 釋放 pen
		pDC->SelectObject(pb);						// 釋放 brush
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
		//
		// 如果是別的地方用到CDC的話，不要抄以下這行，否則螢幕會閃爍
		//
		CDDraw::BltBackToPrimary();					// 將 Back Plain 貼到螢幕
	}
}