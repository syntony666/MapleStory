#ifndef POSITION_H
#define POSITION_H

#include "character.h"
#include "map.h"

namespace game_framework {
	class Position
	{
	public:
		Position(Character* c, Map m);
		int getX();
		int getY();
	private:
		int pos_x, pos_y;
	};

	class Platform		//單平台物件
	{
	public:
		Platform() :_x_begin(-1), _x_last(-1), _y(-1) {}
		Platform(int x_begin, int x_last, int y) :
			_x_begin(x_begin), _x_last(x_last), _y(y) {}
		int getXBegin();
		int getXLast();
		int getY();
	private:
		int _x_begin, _x_last, _y;
	};

	class Floor
	{
	public:
		Floor(Platform plats[], int count);
		~Floor();
		int getXBegin();
		int getXLast();
		int getY();
		bool isFloor(Position& p);
	private:
		int** _points;
		int _count;
		Platform* _plat;
		int _mem = -1;
	};
}

#endif // !POSITION_H


