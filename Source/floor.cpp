#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "floor.h"

namespace game_framework {
	Floor::Floor(Platform plats[], int count) {
		_count = count;
		for (int i = 0; i < count; ++i)
			_plat.push_back(plats[i]);
	}
	Floor::~Floor() {
		/*if (sizeof(_plat) != 0) {
			for (auto i = _plat.begin(); i < _plat.end(); i++)
				delete[] & i;
			_plat.erase(_plat.begin(), _plat.end());
		}*/
	}
	int Floor::getXBegin(int i) const{
		return _plat[i].xBegin;
	}
	int Floor::getXLast(int i) const{
		return _plat[i].xLast;
	}
	int Floor::getY(int i) const{
		return _plat[i].y;
	}

}