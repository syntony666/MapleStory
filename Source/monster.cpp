#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "monster.h"
#include "hero.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Monster: class
	/////////////////////////////////////////////////////////////////////////////

	Monster::Monster()
	{
		Initialize();
	}

	int Monster::GetX1()
	{
		return x;
	}

	int Monster::GetY1()
	{
		return y;
	}

	int Monster::GetX2()
	{
		return x + monsterRight.Width();
	}

	int Monster::GetY2()
	{
		return y + monsterRight.Height();
	}

	void Monster::Initialize()
	{
		const int X_POS = 500;
		const int Y_POS = 570;
		x = X_POS;
		y = Y_POS;
		STEP_SIZE = 3;
		const int FLOOR = 570;
		floor = FLOOR;
	}

	void Monster::LoadBitmap()
	{
		monsterRight.AddBitmap(IDB_MONSTER_STAND_RIGHT, RGB(255, 255, 255));
		monsterLeft.AddBitmap(IDB_MONSTER_STAND_LEFT, RGB(255, 255, 255));
	}

	void Monster::OnMove()
	{
		monsterRight.OnMove();
		if (x >= 700) {	//若碰壁就動地圖直到地圖的邊緣
			STEP_SIZE = -3;
			x += STEP_SIZE;
		}
		if (x <= 400) {		//若碰壁就動地圖直到地圖的邊緣
			STEP_SIZE = 3;
			x += STEP_SIZE;
		}
		else {
			x += STEP_SIZE;
		}
	}


	void Monster::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void Monster::OnShow()
	{
		monsterRight.SetTopLeft(x, y);
		monsterLeft.SetTopLeft(x, y);
		if (STEP_SIZE >= 0) {
			monsterRight.OnShow();
		}
		else monsterLeft.OnShow();
	}
}