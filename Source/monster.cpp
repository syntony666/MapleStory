#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "monster.h"
#include "hero.h"
#include "mygame.h"

namespace game_framework
{

	Monster::Monster(int nx, int ny, int nxp)
	{
		exp = nxp;							 // 怪物經驗值
		initX = nx;							 // 初始 x 座標
		initY = ny;							 // 初始 y 座標
		counter.push_back(new Counter(180)); // mage skill
		counter.push_back(new Counter(40));	 // is_poison
		counter.push_back(new Counter(80));	 // poison_delay
	}

	Monster::~Monster()
	{
	}

	void Monster::Initialize()				// 初始化 Monster
	{
		isMovingLeft = isMovingRight = false;
		isAttacking = isHitLeft = isHitRight = isDead = false;
		STEP_SIZE = 3;
		floor = 570;
		rising = true;
		initial_velocity = 14;
		attack_time = 15;
		setXY(initX, initY);
	}

	void Monster::OnMove()
	{
		if (isDead)
			return;
		if (is_Monster_Go_Left)				// 若怪物往左移動
		{ 
			STEP_SIZE = -3;
			pos_x += STEP_SIZE;
		}
		else if (is_Monster_Go_Right)		// 若怪物往右移動
		{
			STEP_SIZE = 3;
			pos_x += STEP_SIZE;
		}
		if (isMovingRight)					// 若玩家移動視角則怪物對應移動
		{
			pos_x -= HERO_STEP;
		}
		else if (isMovingLeft)				// 若玩家移動視角則怪物對應移動
		{
			pos_x += HERO_STEP;
		}

		if (isHitLeft)						// 受到向左攻擊的對應動作
		{
			if (hit_time == 0)
			{
				hit_time = 18;
				isHitLeft = false;
			}
			else if (hit_time >= 17)
			{
				rising = true;
				velocity = initial_velocity - 7;
			}
			else if (hit_time > 0)
			{
				pos_x -= HERO_STEP * 2;
			}
			hit_time--;
		}
		if (isHitRight)						// 受到向右攻擊的對應動作
		{
			if (hit_time == 0)
			{
				hit_time = 18;
				isHitRight = false;
			}
			else if (hit_time >= 17)
			{
				rising = true;
				velocity = initial_velocity - 7;
			}
			else if (hit_time > 0)
			{
				pos_x += HERO_STEP * 2;
			}
			hit_time--;
		}

		if (rising)
		{									// 上升狀態
			if (velocity > 0)
			{
				pos_y -= velocity * 2;		// 當速度 > 0時，y軸上升(移動velocity個點，velocity的單位為 點/次)
				velocity--;					// 受重力影響，下次的上升速度降低
			}
			else
			{
				rising = false;				// 當速度 <= 0，上升終止，下次改為下降
				velocity = 1;				// 下降的初速(velocity)為1
			}
		}
		else
		{									// 下降狀態
			if (pos_y < floor)
			{								// 當y座標還沒碰到地板
				pos_y += velocity * 2;		// y軸下降(移動velocity個點，velocity的單位為 點/次)
				if (velocity < 7)
					velocity++;
			}
			else
			{
				pos_y = floor;				// 當y座標低於地板，更正為地板上
				velocity = 0;
			}
		}

		if (isAttacking)					// 攻擊時間判定
		{
			if (attack_time == 0)
			{
				attack_time = 15;
				isAttacking = false;
			}
			attack_time--;
		}
	}

	void Monster::OnShow()
	{
		if (!isDead)
		{
			// 站立時的貼圖
			a.standRight.SetTopLeft(pos_x, pos_y);
			a.standLeft.SetTopLeft(pos_x, pos_y);

			if (STEP_SIZE >= 0)
			{		
				if (isAttacking)		// 攻擊時的貼圖
				{
					a.attackRight.SetTopLeft(a.standRight.Left(), a.standRight.Top());
					a.attackRight.OnShow();
					a.attackRight.OnMove();
				}
				else
				{
					a.standRight.OnShow();
					a.standRight.OnMove();
				}
			}
			else
			{
				if (isAttacking)
				{
					a.attackLeft.SetTopLeft(a.standLeft.Left(), a.standLeft.Top());
					a.attackLeft.OnShow();
					a.attackLeft.OnMove();
				}
				else
				{
					a.standLeft.OnShow();
					a.standLeft.OnMove();
				}
			}
			if (counter[poison_delay]->getCount() < 80)		// 施放技能時的貼圖
			{
				a.slashAnimation.OnShow();
				a.slashAnimation.OnMove();
			}
			hp_OnShow();			// 生命值的貼圖
		}
	}
	bool Monster::ifSkill()
	{
		return isSkill;
	}

	void Monster::attacking(Character *hero)		// 怪物攻擊角色時產生的效果與技能判定
	{
		if (skill == 0)
		{
			hero->setHP(hero->getHP() - attack);
		}
		if (skill == 1) {
			if (counter[mage_skill]->getCount() == 180) {

				hero_tempX = hero->getX();
				hero_tempY = hero->getY();
				counter[mage_skill]->start();
				counter[poison_delay]->start();
				a.slashAnimation.SetTopLeft(hero_tempX - 50, hero_tempY - 20);
			}
			if (counter[poison_delay]->getCount() <= 40 && hero->ifPoison() == false)
			{
				if (hero->getX() >= hero_tempX - 80 && hero->getX() <= hero_tempX + 80)
				{
					if (counter[is_poison]->getCount() == 40)
					{
						counter[is_poison]->start();
						CAudio::Instance()->Play(SFX_ROOT, false);
					}
				}
			}
			if (counter[is_poison]->getCount() < 40)
			{
				hero->setMovingLeft(false);
				hero->setMovingRight(false);
				hero->setMovingUp(false);
				hero->setMovingDown(false);
				hero->setPoison(true);
			}
			else
				hero->setPoison(false);
			if (counter[is_poison]->getCount() == 20 || counter[is_poison]->getCount() == 0)
			{
				if (hero->getHP() * 0.1 <= 50)
					hero->setHP(hero->getHP() - 50);
				else
					hero->setHP(int(hero->getHP() * 0.90));
			}
			if (counter[poison_delay]->getCount() == 0)
			{
				a.slashAnimation.Reset();
			}
		}
	}
} 