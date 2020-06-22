#ifndef HERO_H
#define HERO_H

#include "character.h"

namespace game_framework
{
	enum Counters							 // 設定 Hero 技能計數器
	{
		slash,
		heal
	};

	class Hero : public Character
	{
	public:
		Hero();
		~Hero();
		void Initialize();					 // 設定 Hero 為初始值
		void OnMove();						 // 移動 Hero
		void OnShow();						 // 將 Hero 圖形貼到畫面
		void attacking(Character *monster);	 // 判定 hero 攻擊 monster 的效果

	protected:
		const int d = 17;					 // UI文字間距
		int skill_time;						 // 技能動畫時間
		int heal_time;						 // 技能動畫時間
	};
} // namespace game_framework
#endif