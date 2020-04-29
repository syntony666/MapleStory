#ifndef INITIALIZE_H
#define INITIALIZE_H
#include "hero.h"
#include "map.h"
#include "monster.h"
#include "position.h"
#include <vector>
namespace game_framework {
	inline Map Map1() {
		Map gamemap;
		Platform plats[8] = {	{260, 404, 200},
								{580, 980, 290},
								{764, 1316,590},
								{1204,1908,418},
								{1436,1924,253},
								{1948,2196,150},
								{1780,2148,590},
								{0,3000,0} };
		gamemap.setInitFloor(570);
		gamemap.setInitZoom(2);
		gamemap.setInitXY(0, 0);
		gamemap.setInitPlatform(plats, 8);
		gamemap.setInitBitmap(IDB_BACKGROUND);
		return gamemap;
	}
	inline Map Map2() {
		Map gamemap;
		Platform plats[8] = {	{460 , 948,118},
								{1044,1780,192},
								{1748,1980,323},
								{1300,1704,441},
								{868 ,1276,560},
								{460 ,780 ,513},
								{20  ,404 ,390},
								{1756,1924,568} };
		gamemap.setInitFloor(570);
		gamemap.setInitZoom(2);
		gamemap.setInitXY(0, 0);
		gamemap.setInitPlatform(plats, 8);
		gamemap.setInitBitmap(IDB_BACKGROUND2);
		return gamemap;
	}
	inline Map Map3() {
		Map gamemap;
		Platform plats[8] = {	{260, 404, 200},
								{580, 980, 290},
								{764, 1316,590},
								{1204,1908,418},
								{1436,1924,253},
								{1948,2196,150},
								{1780,2148,590},
								{0,3000,0} };
		gamemap.setInitFloor(570);
		gamemap.setInitZoom(2);
		gamemap.setInitXY(0, 0);
		gamemap.setInitPlatform(plats, 8);
		gamemap.setInitBitmap(IDB_BACKGROUND3);
		return gamemap;
	}
	inline void initHero(Character& hero) {
		hero.Initialize();
		hero.SetXY(100, 570);
		hero.SetFacing(1);
	}
	inline void initMonster1(vector<Character*> & monster) {
		monster.push_back(new Monster(500, 570, 50));
		monster.push_back(new Monster(800, 570, 50));
	}
	inline vector<Character*> Monster1() {
		vector<Character*> monster;
		initMonster1(monster);
		return monster;
	}
}

#endif // !INITIALIZE_H