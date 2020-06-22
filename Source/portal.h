#pragma once
namespace game_framework
{
	class Portal
	{
	public:
		Portal() {}
		~Portal();
		Portal(int x, int y);
		void addBitMaps(int bitmaps[], int num);
		void OnMove();
		void OnShow(int x, int y);
		int getX();
		int getY();

	private:
		int _x, _y;
		CAnimation _portal;
	};
} // namespace game_framework
