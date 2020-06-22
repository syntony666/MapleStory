#ifndef FLOOR_H
#define FLOOR_H

namespace game_framework
{
	struct Platform
	{
		int xBegin, xLast, y;
	};
	class Floor //平台集合體
	{
	public:
		Floor() : _count(0) {}
		Floor(Platform plats[], int count);
		int getXBegin(int i) const;
		int getXLast(int i) const;
		int getY(int i) const;

	private:
		int _count;
		vector<Platform> _plat;
	};
} // namespace game_framework

#endif // !FLOOR_H