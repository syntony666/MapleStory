#ifndef MAP_H
#define MAP_H

#include "floor.h"
#include "portal.h"

namespace game_framework
{
	class Portal;
	class Map
	{
	public:
		Map();
		void Initialize();					// 初始化地圖
		void LoadBitmap();					// 讀取背景圖
		void OnShow();						// 顯示地圖
		void OnMove();						// 移動地圖
		void portalOnShow();				// 顯示傳送門

		//SETs Init 設定所有基礎數值

		void setInitFloor(int i);
		void setInitXY(int x, int y);
		void setInitZoom(double i);
		void setInitPlatform(Platform *plats, int i);
		void setInitBitmap(int bitmap);
		void setInitPortal(int x, int y);

		//SETs in game

		void setMovingLeft(bool flag);		// 設定是否正在往左移動
		void setMovingRight(bool flag);		// 設定是否正在往右移動

		//GETs

		int getFloorXBegin(int i) const;	// 獲取地板 x 起始位置
		int getFloorXLast(int i) const;		// 獲取地板 x 結束位置
		int getFloorY(int i) const;			// 獲取地板 y 高度
		int getX() const;
		int getY() const;
		bool ifMovingLeft() const;
		bool ifMovingRight() const;
		Portal &getPortal();				// 獲取傳送門設定

	protected:
		CMovingBitmap map;					// 地圖的貼圖
		Portal _portal;						// 傳送門的導入
		int _x, _y, floor;					// 內部參數
		double zoom;						// 放大倍率
		bool rising;						// true表上升、false表下降
		int velocity;						// 目前的速度(點/次)
		int _bitmap;
		bool isMovingRight, isMovingLeft;
		Floor floors;						// 導入 Floor 地板數據
	};
}
#endif