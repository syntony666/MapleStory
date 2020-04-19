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
		int  GetX1();					// Hero左上角 x 座標
		int  GetY1();					// Hero左上角 y 座標
		int  GetX2();					// Hero右下角 x 座標
		int  GetY2();					// Hero右下角 y 座標
		void Initialize();				// 設定Hero為初始值
		void LoadBitmap();				// 載入圖形
		void OnMove();					// 移動Hero
		void OnShow();					// 將Hero圖形貼到畫面
		//void SetMovingDown(bool flag);	// 設定是否正在往下移動
		//void SetMovingLeft(bool flag);	// 設定是否正在往左移動
		//void SetMovingRight(bool flag); // 設定是否正在往右移動
		//void SetMovingUp(bool flag);	// 設定是否正在往上移動
		void SetXY(int nx, int ny);		// 設定Hero左上角座標

	protected:
		CAnimation stand;			// 站立
		CAnimation standLeft;		// 站立面向左
		CAnimation downRight;		// 向右趴下
		CAnimation downLeft;		// 向左趴下
		CAnimation goLeft;			// 向左走
		CAnimation goRight;			// 向右走
		CAnimation jumpRight;		// 向右跳
		CAnimation jumpLeft;		// 向左跳
		CAnimation attackRight;		// 向右攻擊
		CAnimation attackLeft;		// 向左攻擊
		//bool isMovingDown;			// 是否正在往下移動
		//bool isMovingLeft;			// 是否正在往左移動
		//bool isMovingRight;			// 是否正在往右移動
		//bool isMovingUp;			// 是否正在往上移動
		int floor;				// 地板的Y座標
		int attack;				// 攻擊力
		bool rising;			// true表上升、false表下降
		int initial_velocity;	// 初始速度
		int velocity;			// 目前的速度(點/次)
		int STEP_SIZE = 8;
	};
}
#endif