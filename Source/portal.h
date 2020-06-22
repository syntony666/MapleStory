#pragma once
namespace game_framework
{
	class Portal
	{
	public:
		Portal() {}
		~Portal();
		Portal(int x, int y);						// 設定傳送門的座標位置
		void addBitMaps(int bitmaps[], int num);	// 設定傳送門貼圖
		void OnMove();								// 傳送門移動
		void OnShow(int x, int y);					// 顯示傳送門
		int getX();									// 獲取 x 座標
		int getY();									// 獲取 y 座標

	private:										// 內部參數
		int _x, _y;
		CAnimation _portal;
	};
}
