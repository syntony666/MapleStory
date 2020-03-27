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
		zoom = 2;
		isMovingLeft = isMovingRight = false;
	}
	void Map::LoadBitmap(int bitmap) {
		map1.LoadBitmap(bitmap);
	}
	void Map::OnShow() {
		map1.SetTopLeft(x,y);
		map1.ShowBitmap(zoom);
	}
	void Map::SetMovingLeft(bool flag) {	// 設定是否正在往左移動
		isMovingRight = flag;
	}
	void Map::SetMovingRight(bool flag) {	// 設定是否正在往右移動
		isMovingLeft = flag;
	}
	void Map::OnMove() {
		const int STEP_SIZE = 8;

		if (x >= -1036 && isMovingRight) {	//若碰壁就動地圖直到地圖的邊緣
			x -= STEP_SIZE;
		}
		if (x < 0 && isMovingLeft) {		//若碰壁就動地圖直到地圖的邊緣
			x += STEP_SIZE;
		}
	}
}