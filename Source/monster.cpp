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
		attack = 1;
		hP = 10;
		maxHP = 10;
		const int FLOOR = 570;
		floor = FLOOR;
	}

	void Monster::LoadBitmap()
	{
		monsterRight.AddBitmap(IDB_MONSTER_STAND_RIGHT, RGB(255, 255, 255));
		monsterLeft.AddBitmap(IDB_MONSTER_STAND_LEFT, RGB(255, 255, 255));
		hP_0.AddBitmap(IDB_HP_0);
		hP_10.AddBitmap(IDB_HP_10);
		hP_20.AddBitmap(IDB_HP_20);
		hP_30.AddBitmap(IDB_HP_30);
		hP_40.AddBitmap(IDB_HP_40);
		hP_50.AddBitmap(IDB_HP_50);
		hP_60.AddBitmap(IDB_HP_60);
		hP_70.AddBitmap(IDB_HP_70);
		hP_80.AddBitmap(IDB_HP_80);
		hP_90.AddBitmap(IDB_HP_90);
		hP_100.AddBitmap(IDB_HP_100);
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
		if (isMovingRight) {
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

	void Monster::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

#define HP_PERCENT 100*hP/maxHP

	void Monster::OnShow()
	{
		monsterRight.SetTopLeft(x, y);
		monsterLeft.SetTopLeft(x, y);
		if (STEP_SIZE >= 0) {
			monsterRight.OnShow();
		}
		else monsterLeft.OnShow();
		if (HP_PERCENT > 90) {
			hP_100.SetTopLeft(x, y-20);
			hP_100.OnShow();
		}
		else if (HP_PERCENT > 80 && HP_PERCENT <= 90) {
			hP_90.SetTopLeft(x, y - 20);
			hP_90.OnShow();
		}
		else if (HP_PERCENT > 70 && HP_PERCENT <= 80) {
			hP_80.SetTopLeft(x, y - 20);
			hP_80.OnShow();
		}
		else if (HP_PERCENT > 60 && HP_PERCENT <= 70) {
			hP_70.SetTopLeft(x, y - 20);
			hP_70.OnShow();
		}
		else if (HP_PERCENT > 50 && HP_PERCENT <= 60) {
			hP_60.SetTopLeft(x, y - 20);
			hP_60.OnShow();
		}
		else if (HP_PERCENT > 40 && HP_PERCENT <= 50) {
			hP_50.SetTopLeft(x, y - 20);
			hP_50.OnShow();
		}
		else if (HP_PERCENT > 30 && HP_PERCENT <= 40) {
			hP_40.SetTopLeft(x, y - 20);
			hP_40.OnShow();
		}
		else if (HP_PERCENT > 20 && HP_PERCENT <= 30) {
			hP_30.SetTopLeft(x, y - 20);
			hP_30.OnShow();
		}
		else if (HP_PERCENT > 10 && HP_PERCENT <= 20) {
			hP_20.SetTopLeft(x, y - 20);
			hP_20.OnShow();
		}
		else if (HP_PERCENT > 0 && HP_PERCENT <= 10) {
			hP_10.SetTopLeft(x, y - 20);
			hP_10.OnShow();
		}
	}
}