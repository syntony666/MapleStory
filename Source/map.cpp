#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "map.h"

namespace game_framework {

	Map::Map(){
		Initialize();
	}
	void Map::Initialize() {
		const int X_POS = 0;
		const int Y_POS = 0;
		x = X_POS;
		y = Y_POS;
		charX = 100;
		charY = 570;
		zoom = 2;
		isMovingLeft = isMovingRight = false;

		const int INITIAL_VELOCITY = 14;
		const int FLOOR = 570;
		rising = false;
		floor = FLOOR;
		initial_velocity = INITIAL_VELOCITY;
	}

	void Map::LoadBitmap(int bitmap) {
		map1.LoadBitmap(bitmap);
	}

	void Map::SetMovingLeft(bool flag) {	// 設定是否正在往左移動
		isMovingLeft = flag;
	}
	void Map::SetMovingRight(bool flag) {
		isMovingRight = flag;	// 設定是否正在往右移動
	}
	void Map::OnMove() {
		const int STEP_SIZE = 8;

		if (x >= -1034 && isMovingRight) {	//若碰壁就動地圖直到地圖的邊緣
			x -= STEP_SIZE;
		}
		if (x < 0 && isMovingLeft) {		//若碰壁就動地圖直到地圖的邊緣
			x += STEP_SIZE;
		}
	}

	void Map::OnShow() {
		map1.SetTopLeft(x, y);
		map1.ShowBitmap(zoom);
	}
	int Map::getFloorXBegin(int i) const{
		return floors->getXBegin(i);
	}
	int Map::getFloorXLast(int i) const {
		return floors->getXLast(i);
	}
	int Map::getFloorY(int i) const {
		return floors->getY(i);
	}
	int Map::getX() {return x;}
	int Map::getY() {return y;}
	bool Map::ifMovingLeft() {	return isMovingLeft; 	}
	bool Map::ifMovingRight() { return isMovingRight;	}
}