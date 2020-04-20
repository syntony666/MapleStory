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
		int floor_num = 2;
		P plats[2] = { {2,2,3},{2,4,3} };
		Floor *floors=new Floor(plats, 2);
	};
}
#endif