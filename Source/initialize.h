#ifndef INITIALIZE_H
#define INITIALIZE_H
#include "hero.h"
#include "map.h"
#include "monster.h"
#include "position.h"
#include <vector>
namespace game_framework {


	//DEFINE
#define HEIGHT_CHECK hero_pos.getY() <= monster_pos.getY() + 100 && hero_pos.getY() + 100 >= monster_pos.getY()
#define SLASH_HEIGHT_CHECK hero_pos.getY() <= monster_pos.getY() + 100 && hero_pos.getY() + 300 >= monster_pos.getY()
#define HIT_CHECK_CHARACTER !hero.ifHitLeft() && !hero.ifHitRight()
#define HIT_CHECK_MONSTER !monster[i]->ifHitLeft() && !monster[i]->ifHitRight()
#define MONSTER_HIT_CHARACTER(a) (hero_pos.getX() - monster_pos.getX() <= a && monster_pos.getX() - hero_pos.getX() <= a)
#define CHARACTER_HIT_MONSTER hero.ifAttacking() && hero.getFacing() == 2 && hero_pos.getX() - monster_pos.getX() <= 100 && monster_pos.getX() - hero_pos.getX() <= 0 || hero.ifAttacking() && hero.getFacing() == 1 && hero_pos.getX() - monster_pos.getX() <= 0 && monster_pos.getX() - hero_pos.getX() <= 100
#define CHARACTER_SLASH_MONSTER hero.ifSlashing() && hero_pos.getX() - monster_pos.getX() <= 340 && monster_pos.getX() - hero_pos.getX() <= 0 || hero.ifSlashing() && hero_pos.getX() - monster_pos.getX() <= 0 && monster_pos.getX() - hero_pos.getX() <= 340
#define ON_PLATFORM_STAGE1 hero_pos.getY() <= map[0].getFloorY(i) + 50 && hero_pos.getY() >= map[0].getFloorY(i) - 14 && hero_pos.getX() >= map[0].getFloorXBegin(i) && hero_pos.getX() <= map[0].getFloorXLast(i)
#define ON_PLATFORM_STAGE2 hero_pos.getY() <= map[1].getFloorY(i) + 50 && hero_pos.getY() >= map[1].getFloorY(i) - 14 && hero_pos.getX() >= map[1].getFloorXBegin(i) && hero_pos.getX() <= map[1].getFloorXLast(i)
#define ON_PLATFORM_STAGE3 hero_pos.getY() <= map[2].getFloorY(i) + 50 && hero_pos.getY() >= map[2].getFloorY(i) - 14 && hero_pos.getX() >= map[2].getFloorXBegin(i) && hero_pos.getX() <= map[2].getFloorXLast(i)
#define ON_PLATFORM_MONSTER monster_pos.getY() <= map.getFloorY(j) + 50 && monster_pos.getY() >= map.getFloorY(j) - 14 && monster_pos.getX() >= map.getFloorXBegin(j) && monster_pos.getX() <= map.getFloorXLast(j)
#define IN_PORTAL1 hero_pos.getY() == 150 && hero_pos.getX() >= 2060 && hero_pos.getX() <= 2132
#define IN_PORTAL2 hero_pos.getY() <= 20 && hero_pos.getX() >= 2084 && hero_pos.getX() <= 2156
#define IN_PORTAL3 hero_pos.getY() == 100 && hero_pos.getX() >= 2084 && hero_pos.getX() <= 2156




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
		Platform plats[8] = {	{228, 708, 330},
								{682,1012, 202},
								{1068,1236,124},
								{1324,1564,194},
								{1508,2232,320},
								{1313,1706,441},
								{998 ,1386,606},
								{582 , 982,488} };
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
		hero.setXY(100, 570);
		hero.setFacing(1);	
		hero.setMaxHP(500);
		hero.setAttack(30); //30
		hero.setXP(0);
		hero.setLevel(1);
	}
	inline void initMonster1(vector<Character*> & monster) {
		for (size_t i = 0; i < monster.size(); i++) {
			monster[i]->Initialize();
			monster[i]->setMaxHP(100);
			monster[i]->setAttack(50);
			monster[i]->setAttackRange(10);
		}
	}
	inline void initMonster2(vector<Character*> & monster) {
		for (size_t i = 0; i < monster.size(); i++) {
			monster[i]->Initialize();
			monster[i]->setMaxHP(300);
			monster[i]->setAttack(100);
			monster[i]->setAttackRange(150);
		}
	}
}

#endif // !INITIALIZE_H
