#ifndef BOSS_H
#define BOSS_H


#include "character.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供可以用鍵盤或滑鼠控制的單位
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////

	class Boss: public Character
	{
	public:
		Boss() {};
		~Boss();
		void Initialize();				// 設定monster為初始值
		void OnMove();					// 移動monster
		void OnShow();					// 將monster圖形貼到畫面

	protected:
		CMovingBitmap bossStand;
		int initX, initY;
		const int HERO_STEP = 8;
	};
}
#endif