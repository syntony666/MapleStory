#ifndef POSITION_H
#define POSITION_H

#include "character.h"
#include "map.h"

namespace game_framework
{

	class Position								// 位置
	{
	public:
		Position();
		Position(Character *c, Map m);
		int getX();								// 取得座標上 X 位置
		int getY();								// 取得座標上 Y 位置
		void setPosition(Character *c, Map m);	// 取得角色在座標上的位置

	private:
		int pos_x, pos_y;						// 內部 X Y 參數
	};
}
#endif
