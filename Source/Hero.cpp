#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "hero.h"
#include "position.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Hero: Eraser class
	/////////////////////////////////////////////////////////////////////////////

	Hero::Hero()
	{
		Initialize();
	}

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
		a.goRight = CAnimation(3);
		a.goLeft = CAnimation(3);
		for (int i = 0; i < 3; i++) {
			a.goLeft.AddBitmap(frogLeft[i], RGB(255, 255, 255));
			a.goRight.AddBitmap(frogRight[i], RGB(255, 255, 255));
		}

		int frogAttackRight[] = { IDB_FROG_ATTACK_RIGHT1, IDB_FROG_ATTACK_RIGHT2, IDB_FROG_ATTACK_RIGHT3,
								  IDB_FROG_ATTACK_RIGHT4, IDB_FROG_ATTACK_RIGHT5, IDB_FROG_ATTACK_RIGHT6 };
		int frogAttackLeft[] = { IDB_FROG_ATTACK_LEFT1, IDB_FROG_ATTACK_LEFT2, IDB_FROG_ATTACK_LEFT3,
								 IDB_FROG_ATTACK_LEFT4, IDB_FROG_ATTACK_LEFT5, IDB_FROG_ATTACK_LEFT6 };
		a.attackRight = CAnimation(1);
		a.attackLeft = CAnimation(1);
		for (int i = 0; i < 6; i++) {
			a.attackLeft.AddBitmap(frogAttackLeft[i], RGB(255, 255, 255));
			a.attackRight.AddBitmap(frogAttackRight[i], RGB(255, 255, 255));
		}

		a.standRight.AddBitmap(IDB_FROG_STAND_RIGHT, RGB(255, 255, 255));
		a.standLeft.AddBitmap(IDB_FROG_STAND_LEFT, RGB(255, 255, 255));
		a.downRight.AddBitmap(IDB_FROG_DOWN_RIGHT, RGB(255, 255, 255));
		a.downLeft.AddBitmap(IDB_FROG_DOWN_LEFT, RGB(255, 255, 255));
		a.jumpRight.AddBitmap(IDB_FROG_JUMP_RIGHT, RGB(255, 255, 255));
		a.jumpLeft.AddBitmap(IDB_FROG_JUMP_LEFT, RGB(255, 255, 255));
		hp_addBitmaps();
	}

	void Hero::OnMove()
	{
		TRACE("---------------%d\n", floor);

		if (isMovingDown  && pos_y >= floor || isAttacking && pos_y >= floor) { //移動速度、趴下靜止
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
				if (velocity <= 14) 
					velocity++;
			}
			else {
				pos_y = floor;  // 當y座標低於地板，更正為地板上
				velocity = 0;
			}
		}
	}



	void Hero::OnShow()
	{	
		// 向右看的貼圖
		if (facing == 1) {
			a.standRight.SetTopLeft(pos_x, pos_y);
			if (isAttacking) {
				a.attackRight.SetTopLeft(a.standRight.Left(), a.standRight.Top() - 12);
				a.attackRight.OnShow();
				a.attackRight.OnMove();
			}
			else if (isMovingDown) {
				a.downRight.SetTopLeft(a.standRight.Left(), a.standRight.Top() + 78);
				a.downRight.OnShow();
			}
			else if (isMovingLeft) {
				a.goLeft.SetTopLeft(a.standRight.Left(), a.standRight.Top());
				if (pos_y < floor) {
					a.jumpLeft.SetTopLeft(a.standRight.Left(), a.standRight.Top());
					a.jumpLeft.OnShow();
					a.jumpLeft.OnMove();
				}
				else {
					a.goLeft.OnShow();
					a.goLeft.OnMove();
				}
			}
			else if (isMovingRight) {
				a.goRight.SetTopLeft(a.standRight.Left(), a.standRight.Top());
				if (pos_y < floor) {
					a.jumpRight.SetTopLeft(a.standRight.Left(), a.standRight.Top());
					a.jumpRight.OnShow();
					a.jumpRight.OnMove();
				}
				else {
					a.goRight.OnShow();
					a.goRight.OnMove();
				}
			}
			else {
				a.standRight.OnShow();
			}
		}

		// 向左看的貼圖
		if (facing == 2) {
			a.standLeft.SetTopLeft(pos_x, pos_y);
			if (isAttacking) {
				a.attackLeft.SetTopLeft(a.standLeft.Left() - 35, a.standLeft.Top() - 12);
				a.attackLeft.OnShow();
				a.attackLeft.OnMove();
			}
			else if (isMovingDown) {
				a.downLeft.SetTopLeft(a.standLeft.Left() - 40, a.standLeft.Top() + 78);
				a.downLeft.OnShow();
			}
			else if (isMovingLeft) {
				a.goLeft.SetTopLeft(a.standLeft.Left(), a.standLeft.Top());
				if (pos_y < floor) {
					a.jumpLeft.SetTopLeft(a.standLeft.Left(), a.standLeft.Top());
					a.jumpLeft.OnShow();
					a.jumpLeft.OnMove();
				}
				else {
					a.goLeft.OnShow();
					a.goLeft.OnMove();
				}
			}
			else if (isMovingRight) {
				a.goRight.SetTopLeft(a.standLeft.Left(), a.standLeft.Top());
				if (pos_y < floor) {
					a.jumpRight.SetTopLeft(a.standLeft.Left(), a.standLeft.Top());
					a.jumpRight.OnShow();
					a.jumpRight.OnMove();
				}
				else {
					a.goRight.OnShow();
					a.goRight.OnMove();
				}
			}
			else {
				a.standLeft.OnShow();
			}
		}
		hp_OnShow();
	}
}