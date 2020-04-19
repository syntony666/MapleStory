#ifndef FLOOR_H
#define FLOOR_H

//#include "position.h"

namespace game_framework {
	struct P	
	{
		int xBegin, xLast, y;
	};
	class Floor		//平台集合體
	{
	public:
		Floor(P plats[], int count);
		~Floor();
		int getXBegin(int i) const;
		int getXLast(int i)const;
		int getY(int i) const;
		//bool isFloor(Position& p);
	private:
		int** _points;
		int _count;
		P* _plat;
		int _mem = -1;
	};
}

#endif // !FLOOR_H


