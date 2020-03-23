#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "monster.h"

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
		return x + monster.Width();
	}

	int Monster::GetY2()
	{
		return y + monster.Height();
	}

	void Monster::Initialize()
	{
		const int X_POS = 500;
		const int Y_POS = 570;
		x = X_POS;
		y = Y_POS;
		tempX = x;
		tempY = y;
		STEP_SIZE = 3;
		const int FLOOR = 570;
		floor = FLOOR;
	}

	void Monster::LoadBitmap()
	{
		monster.AddBitmap(IDB_FROG_STAND_RIGHT, RGB(255, 255, 255));
	}

	void Monster::OnMove()
	{
		x += STEP_SIZE;
		monster.OnMove();
	}


	void Monster::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void Monster::OnShow()
	{
		monster.SetTopLeft(x, y);
		monster.OnShow();
	}
}