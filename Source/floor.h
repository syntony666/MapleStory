#ifndef FLOOR_H
#define FLOOR_H

//#include "position.h"

namespace game_framework {
	struct Platform
	{
		int xBegin, xLast, y;
	};
	class Floor		//平台集合體
	{
	public:
		Floor(Platform plats[], int count);
		~Floor();
		int getXBegin(int i) const;
		int getXLast(int i)const;
		int getY(int i) const;
	private:
		int _count;
		vector<Platform> _plat;
	};
}

#endif // !FLOOR_H


