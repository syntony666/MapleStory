#ifndef MONSTER_H
#define MONSTER_H


#include "character.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供可以用鍵盤或滑鼠控制的單位
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////

	class Monster: public Character
	{
	public:
		Monster();
		void Initialize();				// 設定monster為初始值
		void LoadBitmap();				// 載入圖形
		void OnMove();					// 移動monster
		void OnShow();					// 將monster圖形貼到畫面

	protected:
		CAnimation monsterRight;		// 站立
		CAnimation monsterLeft;
		const int HERO_STEP = 8;//
		int range_X;				// Hero左上角座標
		int tempX, tempY;
	};
}
#endif