namespace game_framework {
	class Map
	{
	public:
		Map();
		void Initialize();
		void LoadBitmap(int bitmap);
		void OnShow();
		void SetMovingLeft(bool flag);
		void SetMovingRight(bool flag);
		void OnMove();

	protected:
		CMovingBitmap map1;
		int x, y, zoom;
		bool isMovingRight, isMovingLeft;
	};

}
