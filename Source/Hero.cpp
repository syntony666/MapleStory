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

	int Hero::GetAttack()
	{
		return attack;
	}

	void Hero::SetAttack(int Attack)
	{
		attack = Attack;
	}

	int Hero::GetHP()
	{
		return hP;
	}

	void Hero::SetHP(int Health)
	{
		hP = Health;
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
		hP = 100;
		attack = 50;
		rising = false;
		floor = FLOOR;
		initial_velocity = INITIAL_VELOCITY;
	}

	void Hero::LoadBitmap()
	{
		int frogLeft[] = { IDB_FROG_GO_LEFT1,IDB_FROG_GO_LEFT2, IDB_FROG_STAND_LEFT};
		int frogRight[] = { IDB_FROG_GO_RIGHT1,IDB_FROG_GO_RIGHT2, IDB_FROG_STAND_RIGHT };
		goRight = CAnimation(3);
		goLeft = CAnimation(3);
		for (int i = 0; i < 3; i++) {
			goLeft.AddBitmap(frogLeft[i], RGB(255, 255, 255));
			goRight.AddBitmap(frogRight[i], RGB(255, 255, 255));
		}

		int frogAttackRight[] = { IDB_FROG_ATTACK_RIGHT1, IDB_FROG_ATTACK_RIGHT2, IDB_FROG_ATTACK_RIGHT3,
								  IDB_FROG_ATTACK_RIGHT4, IDB_FROG_ATTACK_RIGHT5, IDB_FROG_ATTACK_RIGHT6 };
		int frogAttackLeft[] = { IDB_FROG_ATTACK_LEFT1, IDB_FROG_ATTACK_LEFT2, IDB_FROG_ATTACK_LEFT3,
								 IDB_FROG_ATTACK_LEFT4, IDB_FROG_ATTACK_LEFT5, IDB_FROG_ATTACK_LEFT6 };
		attackRight = CAnimation(1);
		attackLeft = CAnimation(1);
		for (int i = 0; i < 6; i++) {
			attackLeft.AddBitmap(frogAttackLeft[i], RGB(255, 255, 255));
			attackRight.AddBitmap(frogAttackRight[i], RGB(255, 255, 255));
		}

		stand.AddBitmap(IDB_FROG_STAND_RIGHT, RGB(255, 255, 255));
		standLeft.AddBitmap(IDB_FROG_STAND_LEFT, RGB(255, 255, 255));
		downRight.AddBitmap(IDB_FROG_DOWN_RIGHT, RGB(255, 255, 255));
		downLeft.AddBitmap(IDB_FROG_DOWN_LEFT, RGB(255, 255, 255));
		jumpRight.AddBitmap(IDB_FROG_JUMP_RIGHT, RGB(255, 255, 255));
		jumpLeft.AddBitmap(IDB_FROG_JUMP_LEFT, RGB(255, 255, 255));
	}

	void Hero::OnMove()
	{

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
		// 向右看的貼圖
		if (facing == 1) {
			stand.SetTopLeft(pos_x, pos_y);
			if (isAttacking) {
				attackRight.SetTopLeft(stand.Left(), stand.Top() - 12);
				attackRight.OnShow();
				attackRight.OnMove();
			}
			else if (isMovingDown) {
				downRight.SetTopLeft(stand.Left(), stand.Top() + 78);
				downRight.OnShow();
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
				}
				else {
					goRight.OnShow();
					goRight.OnMove();
				}
			}
			else {
				stand.OnShow();
			}
		}

		// 向左看的貼圖
		if (facing == 2) {
			standLeft.SetTopLeft(pos_x, pos_y);
			if (isAttacking) {
				attackLeft.SetTopLeft(standLeft.Left() - 35, standLeft.Top() - 12);
				attackLeft.OnShow();
				attackLeft.OnMove();
			}
			else if (isMovingDown) {
				downLeft.SetTopLeft(standLeft.Left() - 40, standLeft.Top() + 78);
				downLeft.OnShow();
			}
			else if (isMovingLeft) {
				goLeft.SetTopLeft(standLeft.Left(), standLeft.Top());
				if (pos_y < floor) {
					jumpLeft.SetTopLeft(standLeft.Left(), standLeft.Top());
					jumpLeft.OnShow();
					jumpLeft.OnMove();
				}
				else {
					goLeft.OnShow();
					goLeft.OnMove();
				}
			}
			else if (isMovingRight) {
				goRight.SetTopLeft(standLeft.Left(), standLeft.Top());
				if (pos_y < floor) {
					jumpRight.SetTopLeft(standLeft.Left(), standLeft.Top());
					jumpRight.OnShow();
					jumpRight.OnMove();
				}
				else {
					goRight.OnShow();
					goRight.OnMove();
				}
			}
			else {
				standLeft.OnShow();
			}
		}
	}
}