namespace game_framework {
	class Map
	{
	public:
		Map()
			:X(0), Y(0), zoom(2) {
			isMovingLeft = isMovingRight = false;
		}
		void LoadBitmap(int bitmap) {
			map1.LoadBitmap(bitmap);
		}
		void OnShow() {
			map1.SetTopLeft(X, Y);
			map1.ShowBitmap(zoom);
		}
		void SetMovingLeft(bool flag) {
			isMovingRight = flag;
		}	// 設定是否正在往左移動
		void SetMovingRight(bool flag) {
			isMovingLeft = flag;
		} // 設定是否正在往右移動
		void OnMove(){
			const int STEP_SIZE = 8;
		if (X >= -1036 && isMovingLeft) {
			X -= STEP_SIZE;
		}
		if (X < 0 && isMovingRight) {
			X += STEP_SIZE;
		}
	}

	protected:
		CMovingBitmap map1;
		int X, Y, zoom;
		bool isMovingRight;
		bool isMovingLeft;
	};

}
