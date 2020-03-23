#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "map.h"

namespace game_framework {
	Map::Map()
		:X(0), Y(0), zoom(2) {
		isMovingLeft = isMovingRight = false;
	}
	void Map::LoadBitmap(int bitmap) {
		map1.LoadBitmap(bitmap);
	}
	void Map::OnShow() {
		map1.SetTopLeft(X, Y);
		map1.ShowBitmap(zoom);
	}
	void Map::SetMovingLeft(bool flag) {
		isMovingRight = flag;
	}	// 設定是否正在往左移動
	void Map::SetMovingRight(bool flag) {
		isMovingLeft = flag;
	} // 設定是否正在往右移動
	void Map::OnMove() {
		const int STEP_SIZE = 8;
		if (X >= -1036 && isMovingRight) {
			X -= STEP_SIZE;
		}
		if (X < 0 && isMovingLeft) {
			X += STEP_SIZE;
		}
	}
}