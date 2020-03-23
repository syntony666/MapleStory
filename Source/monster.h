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
		void SetXY(int nx, int ny);		// 設定monster左上角座標

	protected:
		CAnimation monster;		// 站立
		int x, y;				// Hero左上角座標
		int STEP_SIZE;
		int tempX, tempY;
		int floor;				// 地板的Y座標
	};
}