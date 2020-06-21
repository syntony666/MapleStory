#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include"portal.h"

namespace game_framework {
	Portal::~Portal() {}
	Portal::Portal(int x, int y) {
		_x = x;
		_y = y;
	}
	void Portal::addBitMaps(int bitmaps[], int num) {
		_portal = CAnimation(2);
		for (int i = 0; i < num; i++)
			_portal.AddBitmap(bitmaps[i], RGB(255, 255, 255));
	}
	void Portal::OnMove() {
		_portal.OnMove();
	}
	void Portal::OnShow(int x, int y) {
		_portal.SetTopLeft(x, y);
		_portal.OnShow();
	}
	int Portal::getX() {
		return _x;
	}
	int Portal::getY() {
		return _y;
	}
}
