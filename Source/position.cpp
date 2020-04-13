#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "position.h"

namespace game_framework {

	Position::Position(Character* c, Map m) {
		pos_x = c->getX() - m.getX();
		pos_y = 570 - c->getY();
	}
	int Position::getX() {
		return pos_x;
	}
	int Position::getY() {
		return pos_y;
	}
	int Platform::getXBegin() {
		return _x_begin;
	}
	int Platform::getXLast() {
		return _x_last;
	}
	int Platform::getY() {
		return _y;
	}
	Floor::Floor(Platform plats[], int count) {
		_count = count;
		_plat = new Platform[_count];
		for (int i = 0; i < count; ++i)
			_plat[i] = plats[i];
	}
	Floor::~Floor() {
		delete[] _plat;
	}
	int Floor::getXBegin() {
		return _plat[_mem].getXBegin();
	}
	int Floor::getXLast() {
		return _plat[_mem].getXLast();
	}
	int Floor::getY() {
		return _plat[_mem].getY();
	}
	bool Floor::isFloor(Position& p) {
		for (int i = 0; i < _count; i++) {
			if (p.getY() >= _plat[i].getY() && p.getX() < _plat[i].getXBegin() && p.getX() > _plat[i].getXLast())
			{
				_mem = i;
				return true;
			}
		}
		_mem = -1;
		return false;
	}

}