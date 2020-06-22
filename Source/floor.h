#ifndef FLOOR_H
#define FLOOR_H

namespace game_framework
{
	struct Platform
	{
		int xBegin, xLast, y;				// 平台 x 起始位置、結束位置以及 y 高度
	};
	class Floor								// 平台集合體
	{
	public:
		Floor() : _count(0) {}
		Floor(Platform plats[], int count); // 一個地圖所有平台組合成陣列
		int getXBegin(int i) const;			// 回傳平台 x 起始位置
		int getXLast(int i) const;			// 回傳平台 x 結束位置
		int getY(int i) const;				// 回傳平台 y 高度

	private:								// 內部參數
		int _count;
		vector<Platform> _plat;
	};
} // namespace game_framework

#endif // !FLOOR_H