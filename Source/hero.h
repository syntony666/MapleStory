#ifndef HERO_H
#define HERO_H

#include "character.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供可以用鍵盤或滑鼠控制的單位
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////

	class Hero: public Character
	{
	public:
		Hero();
		void Initialize();				// 設定Hero為初始值
		void OnMove();					// 移動Hero
		void OnShow();					// 將Hero圖形貼到畫面

	protected:
	};
}
#endif