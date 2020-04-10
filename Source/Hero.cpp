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
		return pos_x;
	}

	int Hero::GetY1()
	{
		return pos_y;
	}

	int Hero::GetX2()
	{
		return pos_rx + stand.Width();
	}

	int Hero::GetY2()
	{
		return pos_ry + stand.Height();
	}

	//bool Hero::ifMovingLeft()
	//{
	//	return isMovingLeft;
	//}

	//bool Hero::ifMovingRight()
	//{
	//	return isMovingRight;
	//}

	void Hero::Initialize()
	{
		const int X_POS = 100;
		const int Y_POS = 570;
		pos_x = X_POS;
		pos_y = Y_POS;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		const int INITIAL_VELOCITY = 14;
		const int FLOOR = 570;
		rising = false;
		floor = FLOOR;
		initial_velocity = INITIAL_VELOCITY;
	}

	void Hero::LoadBitmap()
	{
		int frogLeft[] = { IDB_FROG_GO_LEFT1,IDB_FROG_GO_LEFT2, IDB_FROG_STAND_LEFT};
		int frogRight[] = { IDB_FROG_GO_RIGHT1,IDB_FROG_GO_RIGHT2, IDB_FROG_STAND_RIGHT };
		goRight = CAnimation(5);
		goLeft = CAnimation(5);
		for (int i = 0; i < 3; i++) {
			goLeft.AddBitmap(frogLeft[i], RGB(255, 255, 255));
			goRight.AddBitmap(frogRight[i], RGB(255, 255, 255));
		}
		stand.AddBitmap(IDB_FROG_STAND_RIGHT, RGB(255, 255, 255));
		standLeft.AddBitmap(IDB_FROG_GO_LEFT, RGB(255, 255, 255));
		down.AddBitmap(IDB_FROG_DOWN, RGB(255, 255, 255));
		jumpRight.AddBitmap(IDB_FROG_JUMP_RIGHT, RGB(255, 255, 255));
		jumpLeft.AddBitmap(IDB_FROG_JUMP_LEFT, RGB(255, 255, 255));
	}

	void Hero::OnMove()
	{
		stand.OnMove();
		int STEP_SIZE;

		if (isMovingDown && pos_y >= floor) { //移動速度、趴下靜止
			STEP_SIZE = 0;
		}
		else {
			STEP_SIZE = 8;
		}

		if (isMovingLeft && pos_x >= 100 ) 
			pos_x -= STEP_SIZE;

		if (isMovingRight && pos_x <= 1164 )
			pos_x += STEP_SIZE;

		if (isMovingUp && pos_y == floor) {
			rising = true;
			velocity = initial_velocity;
		}

		if (rising) {			// 上升狀態
			if (velocity > 0) {
				pos_y -= velocity*2;	// 當速度 > 0時，y軸上升(移動velocity個點，velocity的單位為 點/次)
				velocity--;		// 受重力影響，下次的上升速度降低
			}
			else {
				rising = false; // 當速度 <= 0，上升終止，下次改為下降
				velocity = 1;	// 下降的初速(velocity)為1
			}
		}
		else {				// 下降狀態
			if (pos_y < floor) {  // 當y座標還沒碰到地板
				pos_y += velocity*2;	// y軸下降(移動velocity個點，velocity的單位為 點/次)
				velocity++;		// 受重力影響，下次的下降速度增加
			}
			else {
				pos_y = floor;  // 當y座標低於地板，更正為地板上
			}
		}
	}

	//void Hero::SetMovingDown(bool flag)
	//{
	//	isMovingDown = flag;
	//}

	//void Hero::SetMovingLeft(bool flag)
	//{
	//	isMovingLeft = flag;
	//}

	//void Hero::SetMovingRight(bool flag)
	//{
	//	isMovingRight = flag;
	//}

	//void Hero::SetMovingUp(bool flag)
	//{
	//	isMovingUp = flag;
	//}

	void Hero::SetXY(int nx, int ny)
	{
		pos_x = nx; pos_y = ny;
	}

	void Hero::OnShow()
	{
		stand.SetTopLeft(pos_x, pos_y);
		if (isMovingDown) {
			down.SetTopLeft(stand.Left(), stand.Top() + 78);
			down.OnShow();
		}
		else if (isMovingLeft) {
			goLeft.SetTopLeft(stand.Left(), stand.Top());
			if (pos_y < floor) {
				jumpLeft.SetTopLeft(stand.Left(), stand.Top());
				jumpLeft.OnShow();
				jumpLeft.OnMove();
			}
			else {
				goLeft.OnShow();
				goLeft.OnMove();
			}
		}
		else if (isMovingRight) {
			goRight.SetTopLeft(stand.Left(), stand.Top());
			if (pos_y < floor) {
				jumpRight.SetTopLeft(stand.Left(), stand.Top());
				jumpRight.OnShow();
				jumpRight.OnMove();
			}else{
				goRight.OnShow();
				goRight.OnMove();
			}
		} 
		else {
			stand.OnShow();
		}
	}
}