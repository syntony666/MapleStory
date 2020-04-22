#ifndef MAP_H
#define MAP_H

#include "floor.h"

namespace game_framework {
	class Map
	{
	public:
		Map();
		void Initialize();
		void LoadBitmap();
		void OnShow();
		void OnMove();

		//SETs Init

		void setInitFloor(int i);
		void setInitXY(int x, int y);
		void setInitZoom(double i);
		void setInitPlatform(Platform *plats,int i);
		void setInitBitmap(int bitmap);

		//SETs in game

		void SetMovingLeft(bool flag);	// 設定是否正在往左移動
		void SetMovingRight(bool flag); // 設定是否正在往右移動

		//GETs

		int getFloorXBegin(int i) const;
		int getFloorXLast(int i) const;
		int getFloorY(int i) const;
		int getX() const;
		int getY() const;
		bool ifMovingLeft() const;
		bool ifMovingRight() const;

	protected:
		CMovingBitmap map;
		int _x, _y, floor;
		double zoom;
		bool rising;			// true表上升、false表下降
		int velocity;			// 目前的速度(點/次)
		int _bitmap;
		bool isMovingRight, isMovingLeft;
		Floor *floors;
	};
}
#endif