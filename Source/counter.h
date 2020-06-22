#pragma once
namespace game_framework
{
	class Counter
	{
	public:
		Counter(int max, int min = 0);
		void start();
		void stop();
		void countdown();
		int getCount();

	private:
		int _count;
		int _max;
		int _min;
	};
} // namespace game_framework
