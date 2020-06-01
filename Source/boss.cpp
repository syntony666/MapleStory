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
		const int FLOOR = 570;
		floor = FLOOR;
		pos_x = 1700;
		pos_y = -30;
	}

	void Boss::OnMove()
	{
		if (isDead)
			return;

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
}