#ifndef MONSTER_H
#define MONSTER_H

#include "character.h"

namespace game_framework
{
	enum MonsterCounters					// Monster 技能計數器
	{
		mage_skill,
		is_poison,
		poison_delay
	};
	class Monster : public Character
	{
	public:
		Monster() {}
		Monster(int nx, int ny, int nxp);	// monster 基本設定
		~Monster();
		void Initialize();					// 設定 monster 為初始值
		void OnMove();						// 移動 monster
		void OnShow();						// 將 monster 圖形貼到畫面
		bool ifSkill();						// 判定 monster 是否施放技能
		void attacking(Character *hero);	// 判定 monster 攻擊 hero 的效果

	protected:
		const int HERO_STEP = 8;			// 導入 Hero 移動參數
		int initX, initY;					// 內部參數
		bool isSkill = false;
		int hero_tempX, hero_tempY;
		int attack_time;					// 攻擊動畫計數器
	};
} // namespace game_framework
#endif