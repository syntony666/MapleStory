#ifndef INITIALIZE_H
#define INITIALIZE_H
#include "hero.h"
#include "map.h"
#include "monster.h"
#include "position.h"
#include <vector>
namespace game_framework {

	// Map 直接回傳物件

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

	// Character 只重置數值

	inline void initHero(Character& hero) {
		hero.Initialize();
		hero.SetXY(100, 570);
		hero.SetFacing(1);	
		hero.SetMaxHP(500);
		hero.SetAttack(30);
		hero.SetXP(0);
		hero.SetLevel(1);
	}
	inline void initMonster1(vector<Character*> & monster) {
		if(monster.size()<6){
		
		}
		for (size_t i = 0; i < monster.size(); i++) {
			monster[i]->Initialize();
			monster[i]->SetMaxHP(100);
			monster[i]->SetAttack(50);
		}
	}
}

#endif // !INITIALIZE_H