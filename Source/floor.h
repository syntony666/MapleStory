#ifndef FLOOR_H
#define FLOOR_H

#include <vector>
#include "position.h"

namespace game_framework {

	class Floor
	{
	public:
		Floor(Platform plats[],int count) {
			_count = count;
			_plat = new Platform[_count];
			for (int i = 0; i < count; ++i) {
				_plat[i] = plats[i];
			}
		}
		~Floor() {
			delete[] _plat;
		}
		int getXBegin() {
			return _plat[_mem].getXBegin();
		}
		int getXLast() {
			return _plat[_mem].getXLast();
		}
		int getY() {
			return _plat[_mem].getY();
		}
		bool isFloor(Position p) {
			for (int i = 0; i < _count; i++)
				if (p.getY() >= _plat[i].getY() && p.getX() < _plat[i].getXBegin() && p.getX > _plat[i].getXLast())
				{
					_mem = i;
					return true;
				}
			_mem = -1;
			return false;
		}

	private:
		int** _points;
		int _count;
		Platform* _plat;
		int _mem = -1;
	};


	class Platform
	{
	public:
		Platform():_x_begin(-1),_x_last(-1),_y(-1){}
		Platform(int x_begin, int x_last, int y) :
			_x_begin(x_begin), _x_last(x_last), _y(y) {}
		int getXBegin() {
			return _x_begin;
		}
		int getXLast() {
			return _x_last;
		}
		int getY() {
			return _y;
		}

	private:
		int _x_begin, _x_last, _y;

	};

}


#endif // !FLOOR_H
