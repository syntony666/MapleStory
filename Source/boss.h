#ifndef BOSS_H
#define BOSS_H

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供可以用鍵盤或滑鼠控制的單位
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////

	class Boss
	{
	public:
		Boss() {};
		~Boss();
		void Initialize();				// 設定monster為初始值
		void OnMove();					// 移動monster
		void OnShow();					// 將monster圖形貼到畫面
		void showHPBar(int percent);
		void setMovingLeft(bool flag);
		void setMovingRight(bool flag);
		void setXY(int nx, int ny);


	protected:
		CAnimation bossStand;
		int pos_x, pos_y;
		bool isMovingRight, isMovingLeft;
		bool isDead = false;
		const int HERO_STEP = 8;
		const int floor = 570;
	};
}
#endif
