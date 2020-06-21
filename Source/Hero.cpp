#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "hero.h"
#include "position.h"

namespace game_framework {

	Hero::Hero() {
		counter.push_back(new Counter(300));	//slash
		counter.push_back(new Counter(600));	//heal
		Initialize();
	}
	Hero::~Hero() {
	}
	void Hero::Initialize()
	{
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		isAttacking = isSlashing = isHitLeft = isHitRight = isDead =isHealing = false;
		rising = false;
		floor = 570;
		initial_velocity = 14;
		exp = 0;
		level = 1;
		counter[slash]->stop();
		counter[heal]->stop();
		skill_time =26;
		heal_time =72;
		level_animation = 0;
	}

	void Hero::OnMove()
	{
		STEP_SIZE = 8;			//移動速度

		if (isMovingDown  && pos_y >= floor || isAttacking && pos_y >= floor || isSlashing)
			STEP_SIZE = 0;		//趴下靜止

		if (isMovingLeft && !isHitLeft && !isHitRight)
			pos_x -= STEP_SIZE;

		if (isMovingRight && !isHitLeft && !isHitRight)
			pos_x += STEP_SIZE;

		if (isMovingUp && pos_y == floor && !isHitLeft && !isHitRight) {
			rising = true;
			velocity = initial_velocity;
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
				pos_x -= STEP_SIZE * 2;
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
				pos_x += STEP_SIZE * 2;
			}
			hit_time--;
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
				if (velocity < 7) 
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
		// 施放技能時的貼圖
		if (isSlashing) {
			if (skill_time == 0) {
				skill_time = 26;
				isSlashing = false;
			}
			else {
				a.slashAnimation.SetTopLeft(pos_x - 370, pos_y - 240);
				a.slashAnimation.OnShow();
				a.slashAnimation.OnMove();
				skill_time--;
			}
		}
		else {
			if (isHealing) {
				if (heal_time == 0) {
					heal_time = 72;
					isHealing = false;
				}
				else {
					a.healAnimation.SetTopLeft(pos_x - 320, pos_y - 240);
					a.healAnimation.OnShow();
					a.healAnimation.OnMove();
					heal_time--;
				}
			}
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
		}
		hp_OnShow();

		if (level_animation > 0) {
			a.lv_up.SetTopLeft(pos_x - 500, pos_y - 650);
			a.lv_up.OnShow();
			a.lv_up.OnMove();
			level_animation--;
		}

		//10 = Lv, 11 = HP, 12 = ATK
		// UI 介面
		number_OnShow(10, 10, 10);
		number_OnShow(12, 10, 45);
		number_OnShow(11, 10, 80);

		// LV 顯示
		if(level < 10)
			number_OnShow(level, 165, 10);
		else {
			number_OnShow(level / 10, 165, 10);
			number_OnShow(level % 10, 165+d, 10);
		}

		// ATK 顯示
		if (attack < 100) {
			number_OnShow(attack / 10, 133, 45);
			number_OnShow(attack % 10, 133 + d, 45);
		}
		if (attack < 1000) {
			number_OnShow(attack / 100, 133, 45);
			number_OnShow(attack / 10 % 10, 133 + d, 45);
			number_OnShow(attack % 10, 133 + d * 2, 45);
		}
		else {
			number_OnShow(attack / 1000, 133, 45);
			number_OnShow(attack / 100 % 10, 133 + d, 45);
			number_OnShow(attack / 10 % 10, 133 + d * 2, 45);
			number_OnShow(attack % 10, 133 + d * 3, 45);
		}

		// HP 顯示
		if (HP > 0) {
			if (HP < 10) {
				number_OnShow(HP, 133, 80);
			}
			else if (HP < 100) {
				number_OnShow(HP / 10, 133, 80);
				number_OnShow(HP % 10, 133 + d, 80);
			}
			else if (HP < 1000) {
				number_OnShow(HP / 100, 133, 80);
				number_OnShow(HP / 10 % 10, 133 + d, 80);
				number_OnShow(HP % 10, 133 + d * 2, 80);
			}
			else if (HP < 10000) {
				number_OnShow(HP / 1000, 133, 80);
				number_OnShow(HP / 100 % 10, 133 + d, 80);
				number_OnShow(HP / 10 % 10, 133 + d * 2, 80);
				number_OnShow(HP % 10, 133 + d * 3, 80);
			}
			else if (HP < 100000) {
				number_OnShow(HP / 10000, 133, 80);
				number_OnShow(HP / 1000 % 10, 133 + d, 80);
				number_OnShow(HP / 100 % 10, 133 + d * 2, 80);
				number_OnShow(HP / 10 % 10, 133 + d * 3, 80);
				number_OnShow(HP % 10, 133 + d * 4, 80);
			}
		}
	}

	void Hero::attacking(Character *monster) {
		if(isSlashing == true)
			monster->setHP(monster->getHP() - attack * 2);
		if(isAttacking == true)
			monster->setHP(monster->getHP() - attack);
		if (facing == 2)
			monster->setHitLeft();
		else if (facing == 1)
			monster->setHitRight();
	}
}