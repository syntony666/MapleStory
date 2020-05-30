#ifndef MAP_H
#define MAP_H

#include "floor.h"


namespace game_framework {
	class Portal;
	class Map
	{
	public:
		Map();
		~Map();
		void Initialize();
		void LoadBitmap();
		void OnShow();
		void OnMove(); 
		void portalOnShow();

		//SETs Init

		void setInitFloor(int i);
		void setInitXY(int x, int y);
		void setInitZoom(double i);
		void setInitPlatform(Platform *plats,int i);
		void setInitBitmap(int bitmap);
		void setInitPortal(int x, int y);

		//SETs in game

		void setMovingLeft(bool flag);	// 設定是否正在往左移動
		void setMovingRight(bool flag); // 設定是否正在往右移動

		//GETs

		int getFloorXBegin(int i) const;
		int getFloorXLast(int i) const;
		int getFloorY(int i) const;
		int getX() const;
		int getY() const;
		bool ifMovingLeft() const;
		bool ifMovingRight() const;
		Portal* getPortal();

	protected:
		CMovingBitmap map;
		Portal *_portal;
		int _x, _y, floor;
		double zoom;
		bool rising;			// true表上升、false表下降
		int velocity;			// 目前的速度(點/次)
		int _bitmap;
		bool isMovingRight, isMovingLeft;
		Floor floors;
	};
	class Portal {
	public:
		Portal(){}
		Portal(int x, int y) {
			_x = x;
			_y = y;
		}
		//~Portal() {

		//}
		void addBitMaps(int bitmaps[],int num) {
			_portal = CAnimation(2);
			for (int i = 0; i < num; i++)
				_portal.AddBitmap(bitmaps[i], RGB(255, 255, 255));
		}
		void OnMove() {
			_portal.OnMove();
		}
		void OnShow(int x,int y) {
			_portal.SetTopLeft(x, y);
			_portal.OnShow();
		}
		int getX() {
			return _x;
		}
		int getY() {
			return _y;
		}
	private:
		int _x, _y;
		CAnimation _portal;
	};
}
#endif