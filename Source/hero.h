#ifndef HERO_H
#define HERO_H

#include "character.h"

namespace game_framework {

	class Hero: public Character
	{
	public:
		Hero();
		void Initialize();				// 設定Hero為初始值
		void OnMove();					// 移動Hero
		void OnShow();					// 將Hero圖形貼到畫面
		void attacking(Character *monster);

	protected:
		const int d = 17;				// UI文字間距
	};
}
#endif