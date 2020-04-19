#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "position.h"

namespace game_framework {

	Position::Position(Character* c, Map m) {
		pos_x = c->getX() - m.getX();
		pos_y = 570 - c->getY();
	}
	int Position::getX() {
		return pos_x;
	}
	int Position::getY() {
		return pos_y;
	}
}