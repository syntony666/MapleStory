#include "counter.h"

namespace game_framework {
	Counter::Counter(int max, int min) {
		_max = max;
		_count = max;
		_min = min;
	}
	void Counter::start() {
		if(_count ==_max)
			_count--;
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