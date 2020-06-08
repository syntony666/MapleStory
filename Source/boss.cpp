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
		a.normal.SetDelayCount(2);
		isMovingRight = isMovingLeft = false;
		pos_x = 1550;
		pos_y = 220;
		HP = maxHP;
	}

	void Boss::OnMove()
	{
		if (isDead)
			return;

		a.normal.OnMove();

		if (isMovingRight) {
			pos_x -= HERO_STEP;
		}
		else if (isMovingLeft) {
			pos_x += HERO_STEP;
		}

		if (isHit) {
			if (hit_time == 0) {
				hit_time = 18;
				isHit = false;
			}
			hit_time--;
		}
	}

	void Boss::OnShow()
	{
		if (!isDead) {
			a.normal.SetTopLeft(pos_x, pos_y);
			a.normal.OnShow();
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
	void Boss::addBitmap() {
		hpIcon.LoadBitmap(IDB_BOSS_ICON, RGB(255, 255, 255));
		int boss_stand_bitmaps[] = { IDB_BOSS_STAND1, IDB_BOSS_STAND2, IDB_BOSS_STAND3, IDB_BOSS_STAND4, IDB_BOSS_STAND5, IDB_BOSS_STAND6, IDB_BOSS_STAND7, IDB_BOSS_STAND8 };
		for (int i = 0; i < 8; i++)
			a.normal.AddBitmap(boss_stand_bitmaps[i], RGB(255, 255, 255));

	}
	void Boss::showHPBar()
	{
		int percent = HP * 100 / maxHP;
		const int bar_width = SIZE_X - 300;
		const int bar_height = 15;
		const int x1 = SIZE_X - bar_width;
		const int y1 = bar_height + 20;
		const int y2 = y1 + bar_height;
		const int x2 = x1 + (percent * bar_width / 100);

		CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
		CPen *pp, p(PS_NULL, 0, RGB(0, 0, 0));		// 清除pen
		pp = pDC->SelectObject(&p);

		CBrush b2(RGB(255, 0, 0));					// 血條
		pDC->SelectObject(&b2);
		pDC->Rectangle(x1, y1, x2, y2);

		pDC->SelectObject(pp);						// 釋放 pen
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
		hpIcon.SetTopLeft(250, 5);
		hpIcon.ShowBitmap(0.3);
	}

	void Boss::setHit() {
		isHit = true;
	}
	void Boss::setHit(bool flag) {
		isHit = flag;
	}

	bool Boss::ifHit() {
		return isHit;
	}
	int Boss::getAttack() {
		return attack;
	}
	int Boss::getHP() {
		return HP;
	}
	int Boss::getMaxHP() {
		return maxHP;
	}
	void Boss::setHP(int Health) {
		HP = Health;
	}
}