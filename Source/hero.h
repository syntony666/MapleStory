#ifndef HERO_H
#define HERO_H

#include "character.h"

namespace game_framework
{
	enum Counters
	{
		slash,
		heal
	};

	class Hero : public Character
	{
	public:
		Hero();
		~Hero();
		void Initialize(); // 設定Hero為初始值
		void OnMove();	   // 移動Hero
		void OnShow();	   // 將Hero圖形貼到畫面
		void attacking(Character *monster);

	protected:
		const int d = 17; // UI文字間距
		int skill_time;	  // 技能動畫時間
		int heal_time;	  // 技能動畫時間
	};
} // namespace game_framework
#endif