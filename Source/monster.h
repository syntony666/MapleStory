namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供可以用鍵盤或滑鼠控制的單位
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////

	class Monster
	{
	public:
		Monster();
		int  GetX1();					// monster左上角 x 座標
		int  GetY1();					// monster左上角 y 座標
		int  GetX2();					// monster右下角 x 座標
		int  GetY2();					// monster右下角 y 座標
		void Initialize();				// 設定monster為初始值
		void LoadBitmap();				// 載入圖形
		void OnMove();					// 移動monster
		void OnShow();					// 將monster圖形貼到畫面
		void SetMovingLeft(bool flag);	// 設定是否正在往左移動
		void SetMovingRight(bool flag); // 設定是否正在往右移動
		void SetXY(int nx, int ny);		// 設定monster左上角座標
		int GetAttack();				// 擷取攻擊力
		void SetAttack(int Atk);		// 設定攻擊力
		int GetHP();					// 擷取生命值
		void SetHP(int Health);			// 設定生命值

	protected:
		CAnimation monsterRight;		// 站立
		CAnimation monsterLeft;
		const int HERO_STEP = 8;
		int x, y, range_X;				// Hero左上角座標
		int STEP_SIZE;
		int tempX, tempY;
		int hP;					// 生命值
		int attack;				// 攻擊力
		int floor;				// 地板的Y座標
		bool isMovingRight, isMovingLeft;
	};
}