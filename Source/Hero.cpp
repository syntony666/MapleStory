#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Hero.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Hero: Eraser class
	/////////////////////////////////////////////////////////////////////////////

	Hero::Hero()
	{
		Initialize();
	}

	int Hero::GetX1()
	{
		return x;
	}

	int Hero::GetY1()
	{
		return y;
	}

	int Hero::GetX2()
	{
		return x + animation.Width();
	}

	int Hero::GetY2()
	{
		return y + animation.Height();
	}

	void Hero::Initialize()
	{
		const int X_POS = 100;
		const int Y_POS = 570;
		x = X_POS;
		y = Y_POS;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		const int INITIAL_VELOCITY = 20;
		const int FLOOR = 570;
		rising = false;
		floor = FLOOR;
		initial_velocity = INITIAL_VELOCITY;
	}

	void Hero::LoadBitmap()
	{
		//預定走路動畫
		animation.AddBitmap(IDB_FROG_STAND, RGB(255, 255, 255));
		// animation.AddBitmap(IDB_ERASER2, RGB(255, 255, 255));
		// animation.AddBitmap(IDB_ERASER3, RGB(255, 255, 255));
		// animation.AddBitmap(IDB_ERASER2, RGB(255, 255, 255));
	}

	void Hero::OnMove()
	{
		const int STEP_SIZE = 8;		//移動速度
		animation.OnMove();
		if (isMovingLeft&&x>=100) {
			x -= STEP_SIZE;
		}

		if (isMovingRight&&x<=1166)
			x += STEP_SIZE;
		if (isMovingUp  && y == floor) {
			rising = true;
			velocity = initial_velocity;
		}
		//if (isMovingDown)

		if (rising) {			// 上升狀態
			if (velocity > 0) {
				y -= velocity;	// 當速度 > 0時，y軸上升(移動velocity個點，velocity的單位為 點/次)
				velocity--;		// 受重力影響，下次的上升速度降低
			}
			else {
				rising = false; // 當速度 <= 0，上升終止，下次改為下降
				velocity = 1;	// 下降的初速(velocity)為1
			}
		}
		else {				// 下降狀態
			if (y < floor) {  // 當y座標還沒碰到地板
				y += velocity;	// y軸下降(移動velocity個點，velocity的單位為 點/次)
				velocity++;		// 受重力影響，下次的下降速度增加
			}
			else {
				y = floor;  // 當y座標低於地板，更正為地板上
			}
		}
	}

	void Hero::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}

	void Hero::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}

	void Hero::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}

	void Hero::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}

	void Hero::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void Hero::OnShow()
	{
		animation.SetTopLeft(x, y);
		animation.OnShow();
	}
}