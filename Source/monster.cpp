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
		range_X = X_POS;
		isMovingLeft = isMovingRight = false;
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
		if (range_X >= 700) {	//若碰壁就動地圖直到地圖的邊緣
			STEP_SIZE = -3;
			x += STEP_SIZE;
			range_X += STEP_SIZE;
		}
		else if (range_X <= 400) {		//若碰壁就動地圖直到地圖的邊緣
			STEP_SIZE = 3;
			x += STEP_SIZE;
			range_X += STEP_SIZE;
		}
		else if (isMovingRight) {
			x += (STEP_SIZE - HERO_STEP);
			range_X += STEP_SIZE;
		}
		else if (isMovingLeft) {
			x += (STEP_SIZE + HERO_STEP);
			range_X += STEP_SIZE;
		}
		else {
			x += STEP_SIZE;
			range_X += STEP_SIZE;
		}
	}

	void Monster::SetMovingLeft(bool flag) {	// 設定是否正在往左移動
		isMovingLeft = flag;
	}
	void Monster::SetMovingRight(bool flag) {	// 設定是否正在往右移動
		isMovingRight = flag;
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