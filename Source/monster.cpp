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

	Monster::Monster(int nx, int ny, int nxp)
	{
		exp = nxp;
		initX = nx;
		initY = ny;
	}

	Monster::~Monster() {
	}

	void Monster::Initialize()
	{
		isMovingLeft = isMovingRight = false;
		isAttacking = isHitLeft = isHitRight = isDead = false;
		STEP_SIZE = 3;
		const int FLOOR = 570;
		floor = FLOOR;
		const int INITIAL_VELOCITY = 14;
		rising = true;
		initial_velocity = INITIAL_VELOCITY;
		setXY(initX, initY);
	}

	void Monster::OnMove()
	{
		if (isDead)
			return;
		if (is_Monster_Go_Left) {	//若碰壁就動地圖直到地圖的邊緣
			STEP_SIZE = -3;
			pos_x += STEP_SIZE;
		}
		else if (is_Monster_Go_Right) {		//若碰壁就動地圖直到地圖的邊緣
			STEP_SIZE = 3;
			pos_x += STEP_SIZE;
		}
		if (isMovingRight) {
			pos_x -= HERO_STEP;
		}
		else if (isMovingLeft) {
			pos_x += HERO_STEP;
		}

		if (isHitLeft) {
			if (hit_time == 0) {
				hit_time = 18;
				isHitLeft = false;
			}
			else if (hit_time >= 17) {
				rising = true;
				velocity = initial_velocity - 7;
			}
			else if (hit_time > 0)
			{
				pos_x -= HERO_STEP * 2;
			}
			hit_time--;
		}
		if (isHitRight) {
			if (hit_time == 0) {
				hit_time = 18;
				isHitRight = false;
			}
			else if (hit_time >= 17) {
				rising = true;
				velocity = initial_velocity - 7;
			}
			else if (hit_time > 0)
			{
				pos_x += HERO_STEP * 2;
			}
			hit_time--;
		}

		if (rising) {			// 上升狀態
			if (velocity > 0) {
				pos_y -= velocity * 2;	// 當速度 > 0時，y軸上升(移動velocity個點，velocity的單位為 點/次)
				velocity--;		// 受重力影響，下次的上升速度降低
			}
			else {
				rising = false; // 當速度 <= 0，上升終止，下次改為下降
				velocity = 1;	// 下降的初速(velocity)為1
			}
		}
		else {				// 下降狀態
			if (pos_y < floor) {  // 當y座標還沒碰到地板
				pos_y += velocity * 2;	// y軸下降(移動velocity個點，velocity的單位為 點/次)
				if (velocity < 7)
					velocity++;
			}
			else {
				pos_y = floor;  // 當y座標低於地板，更正為地板上
				velocity = 0;
			}
		}

		if (isAttacking) {
			if (attack_time == 0) {
				attack_time = 15;
				isAttacking = false;
			}
			attack_time--;
		}
	}



	void Monster::OnShow()
	{
		if (!isDead) {

			a.standRight.SetTopLeft(pos_x, pos_y);
			a.standLeft.SetTopLeft(pos_x, pos_y);

			if (STEP_SIZE >= 0) {
				if (isAttacking) {
					a.attackRight.SetTopLeft(a.standRight.Left(), a.standRight.Top());
					a.attackRight.OnShow();
					a.attackRight.OnMove();
				}
				else {
					a.standRight.OnShow();
					a.standRight.OnMove();
				}
			}
			else {
				if (isAttacking) {
					a.attackLeft.SetTopLeft(a.standLeft.Left(), a.standLeft.Top());
					a.attackLeft.OnShow();
					a.attackLeft.OnMove();
				}
				else {
					a.standLeft.OnShow();
					a.standLeft.OnMove();
				}
			}
			hp_OnShow();
		}
	}
}