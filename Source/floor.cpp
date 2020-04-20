#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "floor.h"

namespace game_framework {
	Floor::Floor(P plats[], int count) {
		_count = count;
		_plat = new P[_count];
		for (int i = 0; i < count; ++i)
			_plat[i] = plats[i];
	}
	Floor::~Floor() {
		delete[] _plat;
	}
	int Floor::getXBegin(int i) const{
		return _plat[i].xBegin;
	}
	int Floor::getXLast(int i) const{
		return _plat[i].xLast;
	}
	int Floor::getY(int i) const{
		return 570 - _plat[i].y;
	}
	/*bool Floor::isFloor(Position& p) {
		for (int i = 0; i < _count; i++) {
			if (p.getY() >= _plat[i].getY() && p.getX() < _plat[i].getXBegin() && p.getX() > _plat[i].getXLast())
			{
				return true;
			}
		}
		return false;
	}*/

}