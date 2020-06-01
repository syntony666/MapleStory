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
		int boss_stand_bitmaps[] = { IDB_BOSS_STAND1, IDB_BOSS_STAND2, IDB_BOSS_STAND3, IDB_BOSS_STAND4, IDB_BOSS_STAND5, IDB_BOSS_STAND6, IDB_BOSS_STAND7, IDB_BOSS_STAND8 };
		for (int i = 0; i < 8; i++)
			bossStand.AddBitmap(boss_stand_bitmaps[i], RGB(255, 255, 255));
		bossStand.SetDelayCount(2);
		isMovingRight = isMovingLeft = false;
		pos_x = 1550;
		pos_y = 220;
	}

	void Boss::OnMove()
	{
		if (isDead)
			return;

		bossStand.OnMove();

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
			bossStand.OnShow();
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
}