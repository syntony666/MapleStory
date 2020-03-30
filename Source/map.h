namespace game_framework {
	class Map
	{
	public:
		Map();
		void Initialize();
		void LoadBitmap(int bitmap);
		void OnShow();
		void SetMovingDown(bool flag);	// 設定是否正在往下移動
		void SetMovingLeft(bool flag);	// 設定是否正在往左移動
		void SetMovingRight(bool flag); // 設定是否正在往右移動
		void SetMovingUp(bool flag);	// 設定是否正在往上移動
		void OnMove();

	protected:
		CMovingBitmap map1;
		int x, y, zoom, charX, charY, floor;
		bool isMovingRight, isMovingLeft, isMovingDown, isMovingUp;
		bool rising;			// true表上升、false表下降
		int initial_velocity;	// 初始速度
		int velocity;			// 目前的速度(點/次)
	};

}
