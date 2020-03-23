#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "monster.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Hero: Eraser class
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
		return x + stand.Width();
	}

	int Monster::GetY2()
	{
		return y + stand.Height();
	}

	void Monster::Initialize()
	{
		const int X_POS = 100;
		const int Y_POS = 570;
		x = X_POS;
		y = Y_POS;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		const int INITIAL_VELOCITY = 14;
		const int FLOOR = 570;
		rising = false;
		floor = FLOOR;
		initial_velocity = INITIAL_VELOCITY;
	}

	void Monster::LoadBitmap()
	{
		stand.AddBitmap(IDB_FROG_STAND, RGB(255, 255, 255));
		down.AddBitmap(IDB_FROG_DOWN, RGB(255, 255, 255));
	}

	void Monster::OnMove()
	{
		stand.OnMove();
		int STEP_SIZE;

		if (isMovingDown && y >= floor) { //移動速度、趴下靜止
			STEP_SIZE = 0;
		}
		else {
			STEP_SIZE = 8;
		}

		if (isMovingLeft && x >= 100)
			x -= STEP_SIZE;

		if (isMovingRight && x <= 1166)
			x += STEP_SIZE;

		if (isMovingUp  && y == floor) {
			rising = true;
			velocity = initial_velocity;
		}

		if (rising) {			// 上升狀態
			if (velocity > 0) {
				y -= velocity * 2;	// 當速度 > 0時，y軸上升(移動velocity個點，velocity的單位為 點/次)
				velocity--;		// 受重力影響，下次的上升速度降低
			}
			else {
				rising = false; // 當速度 <= 0，上升終止，下次改為下降
				velocity = 1;	// 下降的初速(velocity)為1
			}
		}
		else {				// 下降狀態
			if (y < floor) {  // 當y座標還沒碰到地板
				y += velocity * 2;	// y軸下降(移動velocity個點，velocity的單位為 點/次)
				velocity++;		// 受重力影響，下次的下降速度增加
			}
			else {
				y = floor;  // 當y座標低於地板，更正為地板上
			}
		}
	}

	void Monster::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}

	void Monster::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}

	void Monster::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}

	void Monster::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}

	void Monster::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void Monster::OnShow()
	{
		stand.SetTopLeft(x, y);
		if (isMovingDown) {
			down.SetTopLeft(stand.Left(), stand.Top() + 78);
			down.OnShow();
		}
		else {
			stand.OnShow();
		}
	}
}