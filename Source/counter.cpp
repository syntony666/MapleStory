#include "counter.h"
namespace game_framework {
	Counter::Counter(int max, int min) {
		_max = max * 30;
		_count = max * 30;
		_min = min * 30;
	}
	void Counter::start() {
		_count-=1;
	}
	void Counter::stop() {
		_count = _max;
	}
	int Counter::getCount() {
		return _count;
	}
	void Counter::countdown() {
		if (_count == _max)
			return;
		if (_count == _min){
			stop();
			return;
		}
		_count--;
	}
}