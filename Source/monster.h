#ifndef MONSTER_H
#define MONSTER_H


#include "character.h"

namespace game_framework {
	enum MonsterCounters {
		mage_skill, is_poison, poison_delay
	};
	class Monster: public Character
	{
	public:
		Monster(){}
		Monster(int nx, int ny, int nxp);
		~Monster();
		void Initialize();				// 設定monster為初始值
		void OnMove();					// 移動monster
		void OnShow();					// 將monster圖形貼到畫面
		bool ifSkill();
		void setSkill(bool flag);
		void attacking(Character *hero);

	protected:
		const int HERO_STEP = 8;
		int initX, initY;
		int skill = 0;
		bool isSkill = false;
	};
}
#endif