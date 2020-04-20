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
		void LoadBitmap();				// 載入圖形
		void OnMove();					// 移動Hero
		void OnShow();					// 將Hero圖形貼到畫面

	protected:
		CAnimation stand;			// 站立
		CAnimation standLeft;		// 站立面向左
		CAnimation downRight;		// 向右趴下
		CAnimation downLeft;			// 向左趴下
		CAnimation goLeft;			// 向左走
		CAnimation goRight;			// 向右走
		CAnimation jumpRight;		// 向右跳
		CAnimation jumpLeft;			// 向左跳
		CAnimation attackRight;		// 向右攻擊
		CAnimation attackLeft;		// 向左攻擊
	};
}
#endif