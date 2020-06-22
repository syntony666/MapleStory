#pragma once
namespace game_framework
{
	class Counter
	{
	public:
		Counter(int max, int min = 0);	// 
		void start();					// 秨﹍璸
		void stop();					// 氨ゎ璸
		void countdown();				// 璸计竟计
		int getCount();					// 眔讽玡璸计

	private:
		int _count;						// ず场ㄏノ把计
		int _max;
		int _min;
	};
} // namespace game_framework
