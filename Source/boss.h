#ifndef BOSS_H
#define BOSS_H

#include "character.h"
#include "counter.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供可以用鍵盤或滑鼠控制的單位
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////
	struct BossAnimations
	{
		CAnimation normal;
	};
	enum BossCounter {
		skills,
		laser_delay,
		laser_skill,
		knockback_delay,
		knockback_skill
	};
	class Boss
	{
	public:
		Boss() {};
		~Boss();
		void addBitmap();
		void Initialize();				// 設定monster為初始值
		void OnMove();					// 移動monster
		void OnShow();					// 將monster圖形貼到畫面
		void showHPBar();
		void setMovingLeft(bool flag);
		void setMovingRight(bool flag);
		void setXY(int nx, int ny);
		bool ifHit();
		int getX();
		int getHP();					// 擷取生命值
		int getMaxHP();
		int getAttack();				// 擷取攻擊力
		Counter& getCounter(int i);
		void countdown();
		void setHit();				// 設定是否被擊中
		void setHit(bool flag);		// 設定是否被擊中
		void setHP(int Health);			// 設定生命值
		int getSkill();

	protected:
		BossAnimations a;
		CMovingBitmap hpIcon;
		int pos_x, pos_y;
		bool isMovingRight, isMovingLeft;
		bool isDead = false;
		bool isHit = false;
		int hit_time = 18;
		const int HERO_STEP = 8;
		const int floor = 570;
		int maxHP = 100000;
		int HP;
		int attack = 400;
		std::vector<Counter*> counter;
		int skill;
	};
}
#endif
