#pragma once
#ifndef INITIALIZE_H
#define INITIALIZE_H
#include "hero.h"
#include "map.h"
#include "monster.h"
#include "position.h"
namespace game_framework {
	inline Map Map1() {
		Map gamemap;
		Platform plats[8] = {	{268, 404, 200},
						{624, 1018,570 - 205},
						{802, 1264,570 - 52 },
						{1240,1964,570 - 140},
						{1478,1966,570 - 220},
						{1964,2172,570 - 272},
						{1802,2198,570 - 50},
						{0,3000,0} };
		gamemap.setInitFloor(570);
		gamemap.setInitZoom(2);
		gamemap.setInitXY(0, 0);
		gamemap.setInitPlatform(plats, 8);
		gamemap.setInitBitmap(IDB_BACKGROUND);
		return gamemap;
	}
	inline Character* Monster1() {
		Character *monster = new Monster;
		return monster;
	}
}

#endif // !INITIALIZE_H


