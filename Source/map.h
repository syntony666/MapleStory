#ifndef MAP_H
#define MAP_H

#include "floor.h"

namespace game_framework {
	class Map
	{
	public:
		Map();
		void Initialize();
		void LoadBitmap(int bitmap);
		void OnShow();
		void SetMovingLeft(bool flag);	// 設定是否正在往左移動
		void SetMovingRight(bool flag); // 設定是否正在往右移動
		void OnMove();
		int getFloorXBegin(int i) const;
		int getFloorXLast(int i) const;
		int getFloorY(int i) const;
		int getX();
		int getY();
		bool ifMovingLeft();
		bool ifMovingRight();

	protected:
		CMovingBitmap map1;
		int x, y, zoom, charX, charY, floor;
		bool rising;			// true表上升、false表下降
		int initial_velocity;	// 初始速度
		int velocity;			// 目前的速度(點/次)
		bool isMovingRight, isMovingLeft;
		P plats[7] = {  {294,452,200},
						{624,1018,205},
						{802,1264,52 },
						{1240,1964,140},
						{1478,1966,220},
						{1802,2198,50},
						{1990,2228,272} };
		Floor *floors=new Floor(plats, 7);
	};
}
#endif