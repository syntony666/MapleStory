#include "character.h"
#include "map.h"

namespace game_framework {
	class Position
	{
	public:
		Position(Character* c, Map m) {
			pos_x = c->getX() - m.getX();
			pos_y = 570 - c->getX();
		}
		int getX() {
			return pos_x;
		}
		int getY() {
			return pos_y;
		}
	private:
		int pos_x;
		int pos_y;
	};
}