#ifndef POSITION_H
#define POSITION_H

#include "character.h"
#include "map.h"

namespace game_framework {
	class Map;

	class Position		//¦ì¸m
	{
	public:
		Position(Character* c, Map m);
		int getX();
		int getY();
	private:
		int pos_x, pos_y;
	};
}

#endif // !POSITION_H


