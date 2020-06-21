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