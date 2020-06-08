/*
 * mygame.cpp: 本檔案儲遊戲本身的class的implementation
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *
*/

#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"

namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g)
: CGameState(g)
{
}

void CGameStateInit::OnInit()
{
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(0);	// 一開始的loading進度為0%
	//
	// 開始載入資料
	//
	CAudio::Instance()->Load(BGM_MENU, "sounds\\bgm_menu.mp3");
	CAudio::Instance()->Play(BGM_MENU, true);
	CAudio::Instance()->Load(BGM_STAGE1, "sounds\\bgm_stage1.mp3");
	CAudio::Instance()->Load(BGM_STAGE2, "sounds\\bgm_stage2.mp3");
	CAudio::Instance()->Load(BGM_STAGE3, "sounds\\bgm_stage3.mp3");
	CAudio::Instance()->Load(BGM_STAGE4, "sounds\\bgm_stage4.mp3");
	CAudio::Instance()->Load(BGM_BOSS, "sounds\\bgm_boss.mp3");
	CAudio::Instance()->Load(BGM_GAMEOVER, "sounds\\bgm_gameover.mp3");
	CAudio::Instance()->Load(SFX_JUMP, "sounds\\sfx_jump.mp3");
	CAudio::Instance()->Load(SFX_ATTACK, "sounds\\sfx_attack.mp3");
	CAudio::Instance()->Load(SFX_SLASH, "sounds\\sfx_slash.mp3");
	CAudio::Instance()->Load(SFX_HEAL, "sounds\\sfx_heal.mp3");
	CAudio::Instance()->Load(SFX_HERO_HIT, "sounds\\sfx_hero_hit.mp3");
	CAudio::Instance()->Load(SFX_MONSTER_HIT, "sounds\\sfx_monster_hit.mp3");
	CAudio::Instance()->Load(SFX_GUN, "sounds\\sfx_gun.mp3");
	CAudio::Instance()->Load(SFX_LEVEL_UP, "sounds\\sfx_levelup.mp3");

	menu = 1;
	
	ShowInitProgress(5);

	logo.LoadBitmap(IDB_LOGO);
	info.LoadBitmap(IDB_INFO);
	start1.LoadBitmap(IDB_START1, RGB(255, 255, 255));
	start2.LoadBitmap(IDB_START2, RGB(255, 255, 255));
	exit1.LoadBitmap(IDB_EXIT1, RGB(255, 255, 255));
	exit2.LoadBitmap(IDB_EXIT2, RGB(255, 255, 255));
	info1.LoadBitmap(IDB_INFO1, RGB(255, 255, 255));
	info2.LoadBitmap(IDB_INFO2, RGB(255, 255, 255));

	ShowInitProgress(10);

	//
	// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
	//
}

void CGameStateInit::OnBeginState()
{
}

void CGameStateInit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_ENTER = 0x0D;	// Enter
	const char KEY_LEFT = 0x25;		// keyboard左箭頭
	const char KEY_UP = 0x26;		// keyboard上箭頭
	const char KEY_DOWN = 0x28;		// keyboard下箭頭

	if (nChar == KEY_ENTER && menu == 1 && ifInfoOn == 0) {
		GotoGameState(GAME_STATE_RUN);
	}

	if (nChar == KEY_ENTER && menu == 2 && ifInfoOn == 0) {
		ifInfoOn = 1;
	}

	if (nChar == KEY_LEFT && ifInfoOn == 1) {
		ifInfoOn = 0;
	}

	if (nChar == KEY_ENTER && menu == 3 && ifInfoOn == 0) {
		PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);
	}

	if (nChar == KEY_DOWN && ifInfoOn == 0) {
		if(menu < 3)
			menu++;
	}

	if (nChar == KEY_UP && ifInfoOn == 0) {
		if (menu > 1)
			menu--;
	}
	
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	//GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
}

void CGameStateInit::OnShow()
{
	//
	// 貼上logo
	//
	if (ifInfoOn == 1) {
		info.SetTopLeft(0, 0);
		info.ShowBitmap();
	}
	else {
		logo.SetTopLeft(0, 0);
		logo.ShowBitmap();

		if (menu == 1) {
			start2.SetTopLeft(483, 350);
			start2.ShowBitmap();
			info1.SetTopLeft(483, 460);
			info1.ShowBitmap();
			exit1.SetTopLeft(483, 570);
			exit1.ShowBitmap();
		}

		if (menu == 2) {
			start1.SetTopLeft(483, 350);
			start1.ShowBitmap();
			info2.SetTopLeft(483, 460);
			info2.ShowBitmap();
			exit1.SetTopLeft(483, 570);
			exit1.ShowBitmap();
		}

		if (menu == 3) {
			start1.SetTopLeft(483, 350);
			start1.ShowBitmap();
			info1.SetTopLeft(483, 460);
			info1.ShowBitmap();
			exit2.SetTopLeft(483, 570);
			exit2.ShowBitmap();
		}
	}
	//
	// Demo螢幕字型的使用，不過開發時請盡量避免直接使用字型，改用CMovingBitmap比較好
	//
	/*
	CDC *pDC = CDDraw::getBackCDC();			// 取得 Back Plain 的 CDC 
	CFont f,*fp;
	f.CreatePointFont(300,"Times New Roman");	// 產生 font f; 160表示16 point的字
	fp=pDC->SelectObject(&f);					// 選用 font f
	pDC->setBkColor(RGB(0,0,0));
	pDC->setTextColor(RGB(255,255,0));
	pDC->TextOut(450,200,"按下任意鍵開始遊戲");
	pDC->TextOut(5,395,"Press Ctrl-F to switch in between window mode and full screen mode.");
	if (ENABLE_GAME_PAUSE)
		pDC->TextOut(5,455,"Press Ctrl-Q to pause the Game.");
	pDC->TextOut(5,515,"按下 Alt-F4 離開遊戲");
	pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
	CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	*/
}								

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的結束狀態(Game Over)
/////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame *g)
: CGameState(g)
{
}

void CGameStateOver::OnMove()
{
	Gameover.OnMove();
	counter--;
	if (counter < 0) {
		CAudio::Instance()->Play(BGM_MENU, true);
		GotoGameState(GAME_STATE_INIT);
	}
}

void CGameStateOver::OnBeginState()
{
	counter = 30 * 7; // 7 seconds
	CAudio::Instance()->Stop(BGM_STAGE1);
	CAudio::Instance()->Stop(BGM_STAGE2);
	CAudio::Instance()->Stop(BGM_STAGE3);
	CAudio::Instance()->Stop(BGM_STAGE4);
	CAudio::Instance()->Stop(BGM_BOSS);
	CAudio::Instance()->Stop(SFX_ATTACK);
	CAudio::Instance()->Play(BGM_GAMEOVER, false);
}

void CGameStateOver::OnInit()
{
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	
	int over[] = { IDB_GAME_OVER_0 ,IDB_GAME_OVER_1 ,IDB_GAME_OVER_2 ,IDB_GAME_OVER_3,
					IDB_GAME_OVER_4 ,IDB_GAME_OVER_5 ,IDB_GAME_OVER_6 ,IDB_GAME_OVER_7,
					IDB_GAME_OVER_8 ,IDB_GAME_OVER_9 ,IDB_GAME_OVER_10,IDB_GAME_OVER_11,
					IDB_GAME_OVER_12,IDB_GAME_OVER_13,IDB_GAME_OVER_14,IDB_GAME_OVER_0,
					IDB_GAME_OVER_0 ,IDB_GAME_OVER_0 ,IDB_GAME_OVER_0 ,IDB_GAME_OVER_0,
					IDB_GAME_OVER_0 };

	Gameover = CAnimation(10);
	for (int i = 0; i < 21; i++)
		Gameover.AddBitmap(over[i], RGB(255, 255, 255));

	ShowInitProgress(15);
	//
	// 開始載入資料
	//
	//
	// 最終進度為100%
	//
	ShowInitProgress(100);
}

void CGameStateOver::OnShow()
{
	Gameover.SetTopLeft(233, 234);
	Gameover.OnShow();
	/*
	CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
	CFont f, *fp;
	f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
	fp = pDC->SelectObject(&f);					// 選用 font f
	pDC->SetBkColor(RGB(0, 0, 0));
	pDC->SetTextColor(RGB(255, 255, 0));
	char str[80];								// Demo 數字對字串的轉換
	sprintf(str, "Game Over ! (%d)", counter / 30);
	pDC->TextOut(240, 210, str);
	pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
	CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	*/
}



/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g)
: CGameState(g)
{
}

CGameStateRun::~CGameStateRun()
{
	delete hero;
	for (auto i : monster1)
		delete i;
	for (auto i : monster2)
		delete i;
	for (auto i : monster3)
		delete i;
	for (auto i : monster4)
		delete i;
	monster1.clear();
	monster2.clear();
	monster3.clear();
	monster4.clear();
	maps.clear();
}

void CGameStateRun::OnBeginState()
{
	stage = 1;
	stage_count = stage;
	initHero(*hero);
	for (int i = 0; i < 5; i++)
		maps[i].setInitXY(0, 0);
	initMonster1(monster1);
	initMonster2(monster2);
	initMonster3(monster3);
	initMonster4(monster4);
	boss.setXY(1550, 220);

	slash_cd = 10 * SEC;
	heal_cd = 20 * SEC;
	mage_skill_cd = 3 * SEC;

	CAudio::Instance()->Stop(BGM_MENU);
	CAudio::Instance()->Play(BGM_STAGE1, true);
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
	checkStage();
	hero->OnMove();
	map->OnMove();
	map->getPortal()->OnMove();

	hero_pos.setPosition(hero, *map);

	TRACE("-------hero-pos_xy-------(%d, %d)\n", hero_pos.getX(), hero_pos.getY());
	TRACE("---------Poison Delay--------(%d)\n", poison_delay);
	TRACE("-----Monster_Skill_CD----(%d)\n", mage_skill_cd);
	TRACE("-----------Stage---------(%d)\n", stage);
	TRACE("\n\n");

	//// 地圖移動相關
	if (hero->getX() <= 300 && hero->ifMovingLeft() || hero->getX() <= 300 && hero->ifHitLeft()) {
		map->setMovingLeft(true);
	}
	else {
		map->setMovingLeft(false);
	}
	if (hero->getX() >= 964 && hero->ifMovingRight() || hero->getX() >= 964 && hero->ifHitRight()) {
		map->setMovingRight(true);
	}
	else {
		map->setMovingRight(false);
	}

	//// 人物移動相關
	if (map->getX() == 0) {
		if (hero->getX() <= 10)
			hero->setXY(10, hero->getY());
	}
	else if (hero->getX() <= 300)
		hero->setXY(300, hero->getY());

	if (map->getX() == -1024) {
		if (hero->getX() >= 1280)
			hero->setXY(1280, hero->getY());
	}
	else if (hero->getX() >= 980)
		hero->setXY(980, hero->getY());

	//// 地板判定相關
	int flag = 0;
	for (int i = 0; i < 8; i++) {
		if (ON_FLOOR)
			hero->setFloor(570 - map->getFloorY(i));
		else
			flag++;
	}
	if (flag == 8)
		hero->setFloor(570);

	//// 玩家等級相關
	if (hero->getXP() >= hero->getLevel() * 50) {
		hero->setXP(0);
		CAudio::Instance()->Play(SFX_LEVEL_UP, false);
		hero->setLevelUP();
		hero->setLevel(hero->getLevel() + 1);
		hero->setMaxHP(hero->getMaxHP() + hero->getLevel() * 50);
		hero->setAttack(hero->getAttack() + hero->getLevel() * 5);
	}

	// 技能倒數相關
	countDown(slash_cd, 300);
	countDown(heal_cd, 600);
	countDown(mage_skill_cd, 90, 0);
	countDown(poison_delay, 60, 0);
	countDown(isPoison, 90, 0);

	if (poison_delay < 60) {
		Mage_Skill.OnMove();
	}
	if (poison_delay <= 30 && hero->getX() >= hero_tempX - 60) {
		if(hero->getX() <= hero_tempX + 100)
			isPoison--;
	}
	if (isPoison < 70) {
		hero->setMovingLeft(false);
		hero->setMovingRight(false);
		hero->setMovingUp(false);
		hero->setMovingDown(false);
	}
	if (isPoison == 45 || isPoison == 0) {
		if (hero->getHP() * 0.1 <= 100)
			hero->setHP(hero->getHP() - 100);
		else
			hero->setHP(int(hero->getHP() * 0.8));
	}


	// 怪物互動相關
	if(stage <= 4)
		heroMonsterInteraction(*hero, *monster, *map);

	// BOSS互動相關
	if (stage == 5)
		heroBossInteraction(*hero, boss, *map);

	// 玩家死亡相關
	if (hero->getHP() <= 0)
		GotoGameState(GAME_STATE_OVER);

}

void CGameStateRun::OnInit() {	

	// Load Hero's Bitmap

	hero = new Hero;
	vector<int> hero_goLeft = { IDB_FROG_GO_LEFT1,IDB_FROG_GO_LEFT2, IDB_FROG_STAND_LEFT };
	vector<int> hero_goRight = { IDB_FROG_GO_RIGHT1,IDB_FROG_GO_RIGHT2, IDB_FROG_STAND_RIGHT };
	vector<int> hero_attackRight = { IDB_FROG_ATTACK_RIGHT1, IDB_FROG_ATTACK_RIGHT2, IDB_FROG_ATTACK_RIGHT3,
							  IDB_FROG_ATTACK_RIGHT4, IDB_FROG_ATTACK_RIGHT5, IDB_FROG_ATTACK_RIGHT6 };
	vector<int> hero_attackLeft = { IDB_FROG_ATTACK_LEFT1, IDB_FROG_ATTACK_LEFT2, IDB_FROG_ATTACK_LEFT3,
							 IDB_FROG_ATTACK_LEFT4, IDB_FROG_ATTACK_LEFT5, IDB_FROG_ATTACK_LEFT6 };
	vector<int> slash = { IDB_SLASH_01, IDB_SLASH_02, IDB_SLASH_03, IDB_SLASH_04,
				IDB_SLASH_05, IDB_SLASH_06, IDB_SLASH_07, IDB_SLASH_08,
				IDB_SLASH_09, IDB_SLASH_10, IDB_SLASH_11, IDB_SLASH_12,
				IDB_SLASH_13 };
	vector<int> lv_up = { IDB_LV_UP_01, IDB_LV_UP_02, IDB_LV_UP_03, IDB_LV_UP_04, IDB_LV_UP_05
						, IDB_LV_UP_06, IDB_LV_UP_07, IDB_LV_UP_08, IDB_LV_UP_09, IDB_LV_UP_10
						, IDB_LV_UP_11, IDB_LV_UP_12, IDB_LV_UP_13, IDB_LV_UP_14, IDB_LV_UP_15
						, IDB_LV_UP_16, IDB_LV_UP_17, IDB_LV_UP_18, IDB_LV_UP_19, IDB_LV_UP_20 };

	vector<int> heal = { IDB_HEAL_01, IDB_HEAL_02, IDB_HEAL_03, IDB_HEAL_04, IDB_HEAL_05,
						 IDB_HEAL_06, IDB_HEAL_07, IDB_HEAL_08, IDB_HEAL_09 };

	hero->addBitmap(
		IDB_FROG_STAND_RIGHT, IDB_FROG_STAND_LEFT,
		IDB_FROG_DOWN_RIGHT, IDB_FROG_DOWN_LEFT,
		IDB_FROG_JUMP_RIGHT, IDB_FROG_JUMP_LEFT,
		hero_goRight, hero_goLeft,
		hero_attackRight, hero_attackLeft,slash,heal,lv_up,255,255,255);

	ShowInitProgress(20);	

	// Load Bitmaps of Monsters

	monster1.push_back(new Monster(500, 570, 40));
	monster1.push_back(new Monster(350, 370, 40));
	monster1.push_back(new Monster(700, 280, 40));
	monster1.push_back(new Monster(750, 280, 40));
	monster1.push_back(new Monster(1000, -20, 40));
	monster1.push_back(new Monster(1300, 152, 40));
	monster1.push_back(new Monster(1500, 317, 40));
	monster1.push_back(new Monster(2000, 420, 40));
	monster1.push_back(new Monster(2100, -20, 40));

	for (auto monster : monster1) {
		vector<int> attackRight = { IDB_MONSTER_ATTACK_RIGHT1,IDB_MONSTER_ATTACK_RIGHT2, IDB_MONSTER_ATTACK_RIGHT3 };
		vector<int> attackLeft = { IDB_MONSTER_ATTACK_LEFT1,IDB_MONSTER_ATTACK_LEFT2, IDB_MONSTER_ATTACK_LEFT3 };
		vector<int> goRight;
		vector<int> goLeft;
		vector<int> slash;
		monster->addBitmap(
		IDB_MONSTER_STAND_RIGHT, IDB_MONSTER_STAND_LEFT,
		0, 0, 0, 0,
		goRight, goLeft,
		attackRight, attackLeft,slash,heal,lv_up,255,255,255);
	}

	ShowInitProgress(35);

	monster2.push_back(new Monster(500, 570, 70));
	monster2.push_back(new Monster(800, 570, 70));
	monster2.push_back(new Monster(1000, 570, 70));
	monster2.push_back(new Monster(1100, 570, 70));
	monster2.push_back(new Monster(1300, 570, 70));
	monster2.push_back(new Monster(2000, 570, 70));
	monster2.push_back(new Monster(700, 452, 70));
	monster2.push_back(new Monster(1600, 378, 70));
	monster2.push_back(new Monster(1900, 570-323, 70));
	monster2.push_back(new Monster(1700, 570-441, 70));
	monster2.push_back(new Monster(1200, 570-560, 70));
	monster2.push_back(new Monster(700, 570-513, 70));
	monster2.push_back(new Monster(400, 570-390, 70));
	monster2.push_back(new Monster(1900, 570-568, 70));

	for (auto monster = monster2.begin(); monster < monster2.end(); monster++) {
		vector<int> attackRight = { IDB_GUNER_ATTACK_RIGHT1,IDB_GUNER_ATTACK_RIGHT2, IDB_GUNER_ATTACK_RIGHT3 };
		vector<int> attackLeft = { IDB_GUNER_ATTACK_LEFT1,IDB_GUNER_ATTACK_LEFT2, IDB_GUNER_ATTACK_LEFT3 };
		vector<int> goRight;
		vector<int> goLeft;
		vector<int> slash;
		(*monster)->addBitmap(
			IDB_GUNER_STAND_RIGHT, IDB_GUNER_STAND_LEFT,
			0, 0, 0, 0,
			goRight, goLeft,
			attackRight, attackLeft, slash,heal, lv_up,255,255,255);
	}

	ShowInitProgress(50);
	
	monster3.push_back(new Monster(812,  570-202, 100));
	monster3.push_back(new Monster(500,  570-330, 100));
	monster3.push_back(new Monster(732,  570-488, 100));
	monster3.push_back(new Monster(1164, 570-606, 100));
	monster3.push_back(new Monster(1492, 570-441, 100));
	monster3.push_back(new Monster(2100, 570-320, 100));
	monster3.push_back(new Monster(1724, 570-320, 100));
	monster3.push_back(new Monster(1420, 570-194, 100));
	monster3.push_back(new Monster(1124, 570-124, 100));
	monster3.push_back(new Monster(716,	 570 ,    100));
	monster3.push_back(new Monster(1636, 570 ,    100));
	monster3.push_back(new Monster(2172, 570 ,    100));

	for (auto monster = monster3.begin(); monster < monster3.end(); monster++) {
		vector<int> attackRight = { IDB_MAGE_ATTACK_RIGHT1, IDB_MAGE_ATTACK_RIGHT2, IDB_MAGE_ATTACK_RIGHT3,
									IDB_MAGE_ATTACK_RIGHT4, IDB_MAGE_ATTACK_RIGHT5, IDB_MAGE_ATTACK_RIGHT6,
									IDB_MAGE_ATTACK_RIGHT7, IDB_MAGE_ATTACK_RIGHT8};
		vector<int> attackLeft = {  IDB_MAGE_ATTACK_LEFT1, IDB_MAGE_ATTACK_LEFT2, IDB_MAGE_ATTACK_LEFT3,
									IDB_MAGE_ATTACK_LEFT4, IDB_MAGE_ATTACK_LEFT5, IDB_MAGE_ATTACK_LEFT6,
									IDB_MAGE_ATTACK_LEFT7, IDB_MAGE_ATTACK_LEFT8 };
		vector<int> goRight;
		vector<int> goLeft;
		vector<int> slash;
		(*monster)->addBitmap(
			IDB_MAGE_STAND_RIGHT, IDB_MAGE_STAND_LEFT,
			0, 0, 0, 0,
			goRight, goLeft,
			attackRight, attackLeft, slash,heal, lv_up, 0,0,0);
	}
	ShowInitProgress(65);

	monster4.push_back(new Monster(100, 570 - 166, 150));
	monster4.push_back(new Monster(300, 570 - 166, 150));
	monster4.push_back(new Monster(500, 570 - 166, 150));
	monster4.push_back(new Monster(700, 570 - 166, 150));
	monster4.push_back(new Monster(900, 570 - 166, 150));
	monster4.push_back(new Monster(1500, 570 - 166, 150));
	monster4.push_back(new Monster(1700, 570 - 166, 150));
	monster4.push_back(new Monster(1900, 570 - 166, 150));
	monster4.push_back(new Monster(2100, 570 - 166, 150));
	monster4.push_back(new Monster(200, 570 - 496, 150));
	monster4.push_back(new Monster(400, 570 - 496, 150));
	monster4.push_back(new Monster(600, 570 - 496, 150));
	monster4.push_back(new Monster(800, 570 - 496, 150));
	monster4.push_back(new Monster(1400, 570 - 494, 150));
	monster4.push_back(new Monster(1600, 570 - 494, 150));
	monster4.push_back(new Monster(1800, 570 - 494, 150));
	monster4.push_back(new Monster(2000, 570 - 494, 150));
	monster4.push_back(new Monster(2200, 570 - 494, 150));

	for (auto monster = monster4.begin(); monster < monster4.end(); monster++) {
		vector<int> attackRight = { IDB_MAGE_ATTACK_RIGHT1, IDB_MAGE_ATTACK_RIGHT2, IDB_MAGE_ATTACK_RIGHT3,
									IDB_MAGE_ATTACK_RIGHT4, IDB_MAGE_ATTACK_RIGHT5, IDB_MAGE_ATTACK_RIGHT6,
									IDB_MAGE_ATTACK_RIGHT7, IDB_MAGE_ATTACK_RIGHT8 };
		vector<int> attackLeft = { IDB_MAGE_ATTACK_LEFT1, IDB_MAGE_ATTACK_LEFT2, IDB_MAGE_ATTACK_LEFT3,
									IDB_MAGE_ATTACK_LEFT4, IDB_MAGE_ATTACK_LEFT5, IDB_MAGE_ATTACK_LEFT6,
									IDB_MAGE_ATTACK_LEFT7, IDB_MAGE_ATTACK_LEFT8 };
		vector<int> goRight;
		vector<int> goLeft;
		vector<int> slash;
		(*monster)->addBitmap(
			IDB_MAGE_STAND_RIGHT, IDB_MAGE_STAND_LEFT,
			0, 0, 0, 0,
			goRight, goLeft,
			attackRight, attackLeft, slash,heal, lv_up, 0, 0, 0);
	}
	ShowInitProgress(80);
	int Poison[] = { IDB_POISON_01, IDB_POISON_02, IDB_POISON_03, IDB_POISON_04, IDB_POISON_05,
					 IDB_POISON_06, IDB_POISON_07, IDB_POISON_08, IDB_POISON_09, IDB_POISON_10,
					 IDB_POISON_11, IDB_POISON_12, IDB_POISON_13, IDB_POISON_14, IDB_POISON_15,
					 IDB_POISON_16, IDB_POISON_17, IDB_POISON_18, IDB_POISON_19, IDB_POISON_20 };
	Mage_Skill = CAnimation(3);
	for (int i = 0; i < 20; i++)
		Mage_Skill.AddBitmap(Poison[i], RGB(0,0,0));
	boss.addBitmap();

	ShowInitProgress(90);

	// Load Bitmaps of Maps

	int portal_bitmaps[] = { IDB_PORTAL_BLUE1,IDB_PORTAL_BLUE2 };
	int portal_boss_bitmaps[] = { IDB_PORTAL_PURPLE1,IDB_PORTAL_PURPLE2 };

	maps.push_back(Map1());
	maps.push_back(Map2());
	maps.push_back(Map3());
	maps.push_back(Map4());
	maps.push_back(Map5());
	for (size_t i = 0; i < maps.size() ; i++) {
		maps[i].LoadBitmap();
		if (i < 3)
			maps[i].getPortal()->addBitMaps(portal_bitmaps, 2);
		if (i >= 3)
			maps[i].getPortal()->addBitMaps(portal_boss_bitmaps, 2);
	}

	ShowInitProgress(95);

	int slash_cd_bitmaps[] = {
		IDB_SLASH_CD_1,IDB_SLASH_CD_2,IDB_SLASH_CD_3,
		IDB_SLASH_CD_4,IDB_SLASH_CD_5,IDB_SLASH_CD_6,
		IDB_SLASH_CD_7,IDB_SLASH_CD_8,IDB_SLASH_CD_0 };
	for (int i = 0; i < 9; i++)
		slashCD[i].LoadBitmap(slash_cd_bitmaps[i]);


	int heal_cd_bitmaps[] = {
		IDB_HEAL_CD_1,IDB_HEAL_CD_2, IDB_HEAL_CD_3, 
		IDB_HEAL_CD_4,IDB_HEAL_CD_5, IDB_HEAL_CD_6,
		IDB_HEAL_CD_7,IDB_HEAL_CD_8, IDB_HEAL_CD_0};
	for (int i = 0; i < 9; i++)
		healCD[i].LoadBitmap(heal_cd_bitmaps[i]);

	boss.Initialize();

	ShowInitProgress(100);
}


void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard左箭頭
	const char KEY_UP    = 0x26; // keyboard上箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
	const char KEY_DOWN  = 0x28; // keyboard下箭頭
	const char KEY_Z = 0x5A; // keyboard Z
	const char KEY_Y = 0x59; // keyboard Y
	const char KEY_X = 0x58; // keyboard X
	const char KEY_C = 0x43; // keyboard C
	const char KEY_T = 0x54; // keyboard T
	const char KEY_O = 0x4F; // keyboard O
	const char KEY_Q = 0x51; // keyboard Q
	Position hero_pos(hero, *map);

	if (nChar == KEY_Z) {
		hero->setAttacking(true);
		CAudio::Instance()->Play(SFX_ATTACK, true);
	}

	if (nChar == KEY_X) {
		if (slash_cd == 300) {
			hero->setSlashing(true);
			CAudio::Instance()->Play(SFX_SLASH, false);
			slash_cd--;
		}
	}

	if (nChar == KEY_C) {
		if (heal_cd == 600) {
			hero->setHealing(true);
			hero->setHP(hero->getMaxHP());
			CAudio::Instance()->Play(SFX_HEAL, false);
			heal_cd--;
		}
	}
	if (nChar == KEY_Y && stage <= 4) {		//monster all dead
	for (auto i = monster->begin(); i < monster->end(); i++)
		(*i)->setDead(1);
	}
	if (nChar == KEY_Q)
		hero->setXP(hero->getXP()+50);		 //作弊過關用

	if (nChar == KEY_T) 
		stage++;		 //作弊過關用

	if (nChar == KEY_O)
		GotoGameState(GAME_STATE_OVER);		 //作弊死亡用

	if (nChar == KEY_LEFT) {
		hero->setMovingLeft(true);
		hero->setFacing(2);
	}
	
	if (nChar == KEY_RIGHT) {
		hero->setMovingRight(true);
		hero->setFacing(1);
	}

	if (nChar == KEY_UP) {
		if (stage <= 4) {
			if (monster_num(*monster) == 0 && ON_PORTAL) {
				stage++;
				return;
			}
		}
		if (hero->ifMovingUp() == false)
			CAudio::Instance()->Play(SFX_JUMP, false);
		hero->setMovingUp(true);
	}
	if (nChar == KEY_DOWN) {
		hero->setMovingDown(true);
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25;	// keyboard左箭頭
	const char KEY_UP    = 0x26;	// keyboard上箭頭
	const char KEY_RIGHT = 0x27;	// keyboard右箭頭
	const char KEY_DOWN  = 0x28;	// keyboard下箭頭
	const char KEY_Z = 0x5A;		// keyboard Z

	if (nChar == KEY_Z) {
		hero->setAttacking(false);
		CAudio::Instance()->Stop(SFX_ATTACK);
	}
	if (nChar == KEY_LEFT) {
		hero->setMovingLeft(false);
		map->setMovingRight(false);
	}
	if (nChar == KEY_RIGHT) {
		hero->setMovingRight(false);
		map->setMovingLeft(false);
	}
	if (nChar == KEY_UP)
		hero->setMovingUp(false);
	if (nChar == KEY_DOWN)
		hero->setMovingDown(false);
}

/*
		處理滑鼠的動作
*/

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)
{
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)
{
	// 沒事。如果需要處理滑鼠移動的話，寫code在這裡
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)
{
}

void CGameStateRun::OnShow()
{
	checkStage();
	map->OnShow();			// 貼上背景圖
	if (stage <= 4) {
		if (monster_num(*monster) == 0)
			map->portalOnShow();
		for (auto m : *monster)
			m->OnShow();
	}
	else if (stage == 5) {
		boss.OnShow();
		boss.showHPBar();
	}
	hero->OnShow();			// 貼上人物

	if (poison_delay < 60) {
		Mage_Skill.SetTopLeft(hero_tempX - 50, hero_tempY - 20);
		Mage_Skill.OnShow();
	}

	int slash_part = slash_cd / (300 / 8);
	slashCD[slash_part].SetTopLeft(15, 125);
	slashCD[slash_part].ShowBitmap();

	int heal_part = heal_cd / (600 / 8);
	healCD[heal_part].SetTopLeft(60, 125);
	healCD[heal_part].ShowBitmap();
}
inline int CGameStateRun::monster_num(vector<Character*>monsters) {
	int n = 0;
	for (auto monster = monsters.begin(); monster < monsters.end(); monster++)
		if (!(*monster)->ifDead())
			n++;
	return n;
}


void CGameStateRun :: heroMonsterInteraction(Character&hero, vector<Character*> & monsters, Map &map) {

	for (auto monster = monsters.begin(); monster < monsters.end(); monster++) {
		if ((*monster)->ifDead())
			continue;

		Position monster_pos(*monster, map);
		(*monster)->OnMove();

		// 人物移動相關
		if (hero.getX() <= 300 && hero.ifMovingLeft() || hero.getX() <= 300 && hero.ifHitLeft()) {
			if (hero_pos.getX() <= 310)
				(*monster)->setMovingLeft(false);
			else
				(*monster)->setMovingLeft(true);
		}
		else {
			(*monster)->setMovingLeft(false);
		}
		if (hero.getX() >= 964 && hero.ifMovingRight() || hero.getX() >= 964 && hero.ifHitRight()) {
			if (hero_pos.getX() >= 2000)
				(*monster)->setMovingRight(false);
			else
				(*monster)->setMovingRight(true);
		}
		else {
			(*monster)->setMovingRight(false);
		}

		// 怪物移動相關
		if (monster_pos.getX() - hero_pos.getX() >= (*monster)->getAttackRange() && monster_pos.getX() - hero_pos.getX() <= 500) {
			(*monster)->set_Monster_Go_Left(true);
			(*monster)->set_Monster_Go_Right(false);
		}
		else if (hero_pos.getX() - monster_pos.getX() >= (*monster)->getAttackRange() && hero_pos.getX() - monster_pos.getX() <= 500) {
			(*monster)->set_Monster_Go_Right(true);
			(*monster)->set_Monster_Go_Left(false);
		}
		else {
			(*monster)->set_Monster_Go_Right(false);
			(*monster)->set_Monster_Go_Left(false);
		}

		(*monster)->setFloor(570);
		for (int j = 0; j < 8; j++)
			if (ON_PLATFORM_MONSTER)
				(*monster)->setFloor(570 - map.getFloorY(j));

		// 攻擊互動相關
		if ((*monster)->getSkillRange()!=0 && MONSTER_HIT_CHARACTER((*monster)->getSkillRange())){
			if (HEIGHT_CHECK && mage_skill_cd == 90) {
				Mage_Skill.Reset();
				hero_tempX = hero.getX();
				hero_tempY = hero.getY();
				mage_skill_cd--;
				poison_delay--;
			}
		}
		if ((*monster)->getSkillRange() >= 0) { //測試
			if (MONSTER_HIT_CHARACTER((*monster)->getAttackRange())) {
				if (HIT_CHECK_CHARACTER && HEIGHT_CHECK) {
					(*monster)->setAttacking(true);
					if (stage == 2)
						CAudio::Instance()->Play(SFX_GUN, false);
					if (stage != 3) {
						hero.setHP(hero.getHP() - (*monster)->getAttack());
						CAudio::Instance()->Play(SFX_HERO_HIT, false);
						if (monster_pos.getX() >= hero_pos.getX())
							hero.setHitLeft();
						else if (monster_pos.getX() < hero_pos.getX())
							hero.setHitRight();
					}
				}
				if (hero.getHP() <= 0)
					return;
			}
		}
		if (CHARACTER_HIT_MONSTER){
			if (HIT_CHECK_MONSTER && HEIGHT_CHECK) {
				hero.attacking(*monster);
				CAudio::Instance()->Play(SFX_MONSTER_HIT, false);
			}
		}
		if (CHARACTER_SLASH_MONSTER) {
			if (HIT_CHECK_MONSTER && SLASH_HEIGHT_CHECK) {
				hero.attacking(*monster);
				CAudio::Instance()->Play(SFX_MONSTER_HIT, false);
			}
		}

		// 怪物死亡相關
		if ((*monster)->getHP() <= 0) {
			hero.setXP(hero.getXP() + (*monster)->getXP());
			(*monster)->setDead(true);
			(*monster)->setXY(-1, -1);
		}
	}
}
void CGameStateRun::heroBossInteraction(Character& hero, Boss &mboss, Map &map) {

	mboss.OnMove();

	// 人物移動相關
	if (hero.getX() <= 300 && hero.ifMovingLeft() || hero.getX() <= 300 && hero.ifHitLeft()) {
		if (hero_pos.getX() <= 310)
			mboss.setMovingLeft(false);
		else
			mboss.setMovingLeft(true);
	}
	else {
		mboss.setMovingLeft(false);
	}
	if (hero.getX() >= 964 && hero.ifMovingRight() || hero.getX() >= 964 && hero.ifHitRight()) {
		if (hero_pos.getX() >= 2000) {
			mboss.setMovingRight(false);
		}
		else {
			mboss.setMovingRight(true);
		}
	}
	else {
		mboss.setMovingRight(false);
	}
	
		// 攻擊互動相關

	if (HIT_CHECK_CHARACTER && hero_pos.getX() >= 1550) {
		hero.setHP(hero.getHP() - mboss.getAttack());
		CAudio::Instance()->Play(SFX_HERO_HIT, false);
		hero.setHitLeft();
		if (hero.getHP() <= 0)
			return;
		}

	if (CHARACTER_HIT_BOSS && HIT_CHECK_BOSS) {
		mboss.setHP(mboss.getHP() - hero.getAttack());
		CAudio::Instance()->Play(SFX_MONSTER_HIT, false);
		mboss.setHit();
	}
	if (CHARACTER_SLASH_BOSS && HIT_CHECK_BOSS) {
		mboss.setHP(mboss.getHP() - hero.getAttack() * 2);
		CAudio::Instance()->Play(SFX_MONSTER_HIT, false);
		mboss.setHit();
	}
	TRACE("-----------BOSS_HP---------(%d)\n", mboss.getHP());

		/*// 怪物死亡相關
		if ((*monster)->getHP() <= 0) {
			hero.setXP(hero.getXP() + (*monster)->getXP());
			(*monster)->setDead(true);
			(*monster)->setXY(-1, -1);
		}*/
}
void CGameStateRun::checkStage() {
	if (stage == stage_count) {
		hero->setXY(100, 570);
		stage_count++;
		if (stage == 1) {
			monster = &monster1;
			map = &maps[0];
		}
		if (stage == 2) {
			CAudio::Instance()->Stop(BGM_STAGE1);
			CAudio::Instance()->Play(BGM_STAGE2, true);
			monster = &monster2;
			map = &maps[1];
		}
		if (stage == 3) {
			CAudio::Instance()->Stop(BGM_STAGE2);
			CAudio::Instance()->Play(BGM_STAGE3, true);
			monster = &monster3;
			map = &maps[2];
		}
		if (stage == 4) {
			CAudio::Instance()->Stop(BGM_STAGE3);
			CAudio::Instance()->Play(BGM_STAGE4, true);
			monster = &monster4;
			map = &maps[3];
		}
		if (stage == 5) {
			CAudio::Instance()->Stop(BGM_STAGE4);
			CAudio::Instance()->Play(BGM_BOSS, true);
			monster = nullptr;
			map = &maps[4];
		}
		if (stage == 6) {
			GotoGameState(GAME_STATE_INIT);
		}
	}
}
void CGameStateRun::countDown(int &cd, int max, int min) {
	if (cd < max) {
		cd--;
		if (cd == min)
			cd = max;
	}
}
}