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
	
	ShowInitProgress(33);

	logo.LoadBitmap(IDB_LOGO);
	start1.LoadBitmap(IDB_START1, RGB(255, 255, 255));
	start2.LoadBitmap(IDB_START2, RGB(255, 255, 255));
	exit1.LoadBitmap(IDB_EXIT1, RGB(255, 255, 255));
	exit2.LoadBitmap(IDB_EXIT2, RGB(255, 255, 255));

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
	const char KEY_UP = 0x26;		// keyboard上箭頭
	const char KEY_DOWN = 0x28;		// keyboard下箭頭

	if (nChar == KEY_ENTER && menu == 1) {	
		GotoGameState(GAME_STATE_RUN);
	}

	if (nChar == KEY_ENTER && menu == 2) {
		PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);
	}

	if (nChar == KEY_DOWN) {
		menu = 2;
	}

	if (nChar == KEY_UP) {
		menu = 1;
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
	logo.SetTopLeft(0, 0);
	logo.ShowBitmap();

	if (menu == 1) {
		start2.SetTopLeft(483, 380);
		start2.ShowBitmap();
		exit1.SetTopLeft(483, 520);
		exit1.ShowBitmap();
	}

	if (menu == 2) {
		start1.SetTopLeft(483, 380);
		start1.ShowBitmap();
		exit2.SetTopLeft(483, 520);
		exit2.ShowBitmap();
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

	ShowInitProgress(80);	// 接個前一個狀態的進度，此處進度視為66%
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
	Gameover.OnMove();
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
}

void CGameStateRun::OnBeginState()
{
	stage = 1;
	stage_count = stage + 1;
	initHero(*hero);
	for (int i = 0; i < 3; i++)
		map[i].setInitXY(0, 0);
	initMonster1(monster1);
	initMonster2(monster2);

	CAudio::Instance()->Stop(BGM_MENU);
	CAudio::Instance()->Play(BGM_STAGE1, true);

	int blue[] = { IDB_PORTAL_BLUE1,IDB_PORTAL_BLUE2 };

	portal = CAnimation(2);
	for (int i = 0; i < 2; i++)
		portal.AddBitmap(blue[i], RGB(255, 255, 255));

	portal.SetTopLeft(portal1X, 410);
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{

	hero->OnMove();

	if (stage == 1) {
		map[0].OnMove();
		hero_pos.setPosition(hero, map[0]);
	}
	else if (stage == 2) {
		map[1].OnMove();
		hero_pos.setPosition(hero, map[1]);
	}
	else if (stage == 3) {
		map[2].OnMove();
		hero_pos.setPosition(hero, map[2]);
	}
	portal.OnMove();
	TRACE("-----------hero-pos_xy---(%d, %d)\n", hero_pos.getX(), hero_pos.getY());
	TRACE("--hero-level_Attack_HP---(%d, %d, %d)\n", hero->getLevel(), hero->getAttack(), hero->getHP());
	TRACE("-----------Slash_CD------(%d)\n", slash_cd/30);
	TRACE("-----------Stage---------(%d)\n", stage);

	// 地圖移動相關
	if (hero->getX() <= 100 && hero->ifMovingLeft()) {
		if (stage == 1)
			map[0].setMovingLeft(true);
		if (stage == 2)
			map[1].setMovingLeft(true);
		if (stage == 3)
			map[2].setMovingLeft(true);
		if (hero_pos.getX() > 100) {
			if (stage == 1) {
				portal1X += 8;
				portal.SetTopLeft(portal1X, 410);
			}
			if (stage == 2) {
				portal2X += 8;
				portal.SetTopLeft(portal2X, 550);
			}
			if (stage == 3) {
				portal3X += 8;
				portal.SetTopLeft(portal3X, 450);
			}
		}
	}
	else {
		if (stage == 1)
			map[0].setMovingLeft(false);
		if (stage == 2)
			map[1].setMovingLeft(false);
		if (stage == 3)
			map[2].setMovingLeft(false);
	}
	if (hero->getX() >= 1164 && hero->ifMovingRight()) {
		if (stage == 1)
			map[0].setMovingRight(true);
		if (stage == 2)
			map[1].setMovingRight(true);
		if (stage == 3)
			map[2].setMovingRight(true);
		if (hero_pos.getX() < 2204) {
			if (stage == 1) {
				portal1X -= 8;
				portal.SetTopLeft(portal1X, 410);
			}
			if (stage == 2) {
				portal2X -= 8;
				portal.SetTopLeft(portal2X, 500);
			}
			if (stage == 3) {
				portal3X -= 8;
				portal.SetTopLeft(portal3X, 450);
			}
		}
	}
	else {
		if (stage == 1)
			map[0].setMovingRight(false);
		if (stage == 2)
			map[1].setMovingRight(false);
		if (stage == 3)
			map[2].setMovingRight(false);
	}

	// 人物移動相關
	if (hero_pos.getX() <= 100) {
		hero->setXY(100, hero->getY());
	}
	else if (hero_pos.getX() >= 2204) {
		hero->setXY(1164, hero->getY());
	}

	// 地板判定相關
	int flag = 0;
	for (int i = 0; i < 8; i++) {
		if (stage == 1) {
			if (ON_PLATFORM_STAGE1) 
				hero->setFloor(570 - map[0].getFloorY(i));
			else 
				flag++;
		}
		if (stage == 2) {
			if (ON_PLATFORM_STAGE2) 
				hero->setFloor(570 - map[1].getFloorY(i));
			else
				flag++;
		}
		if (stage == 3) {
			if (ON_PLATFORM_STAGE3) 
				hero->setFloor(570 - map[2].getFloorY(i));
			else
				flag++;
		}
	}

	if (flag == 8) {
		hero->setFloor(570);
	}

	// 玩家等級相關
	if (hero->getXP() >= hero->getLevel() * 50) {
		hero->setXP(0);
		CAudio::Instance()->Play(SFX_LEVEL_UP, false);
		hero->setLevelUP();
		hero->setLevel(hero->getLevel() + 1);
		hero->setMaxHP(hero->getMaxHP() + hero->getLevel() * 50);
		hero->setAttack(hero->getAttack() + hero->getLevel() * 5);
	}

	// 玩家技能相關
	if (slash_cd <= 299) {
		slash_cd--;
		if (slash_cd == 0)
			slash_cd = 300;
	}
	if (heal_cd <= 599) {
		heal_cd--;
		if (heal_cd == 0)
			heal_cd = 600;
	}

	// 怪物互動相關
	if (stage == 1)
		heroMonsterInteraction(*hero, monster1, map[0]);
	if (stage == 2)
		heroMonsterInteraction(*hero, monster2, map[1]);
	if (stage == 3)
		heroMonsterInteraction(*hero, monster1, map[2]);

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

	hero->addBitmap(
		IDB_FROG_STAND_RIGHT, IDB_FROG_STAND_LEFT,
		IDB_FROG_DOWN_RIGHT, IDB_FROG_DOWN_LEFT,
		IDB_FROG_JUMP_RIGHT, IDB_FROG_JUMP_LEFT,
		hero_goRight, hero_goLeft,
		hero_attackRight, hero_attackLeft,slash,lv_up);

	ShowInitProgress(33);	

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

	for (size_t i = 0; i < monster1.size(); i++) {
		vector<int> attackRight = { IDB_MONSTER_ATTACK_RIGHT1,IDB_MONSTER_ATTACK_RIGHT2, IDB_MONSTER_ATTACK_RIGHT3 };
		vector<int> attackLeft = { IDB_MONSTER_ATTACK_LEFT1,IDB_MONSTER_ATTACK_LEFT2, IDB_MONSTER_ATTACK_LEFT3 };
		vector<int> goRight;
		vector<int> goLeft;
		vector<int> slash;
		monster1[i]->addBitmap(
		IDB_MONSTER_STAND_RIGHT, IDB_MONSTER_STAND_LEFT,
		0, 0, 0, 0,
		goRight, goLeft,
		attackRight, attackLeft,slash,lv_up);
	}

	ShowInitProgress(50);

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

	for (size_t i = 0; i < monster2.size(); i++) {
		vector<int> attackRight = { IDB_GUNER_ATTACK_RIGHT1,IDB_GUNER_ATTACK_RIGHT2, IDB_GUNER_ATTACK_RIGHT3 };
		vector<int> attackLeft = { IDB_GUNER_ATTACK_LEFT1,IDB_GUNER_ATTACK_LEFT2, IDB_GUNER_ATTACK_LEFT3 };
		vector<int> goRight;
		vector<int> goLeft;
		vector<int> slash;
		monster2[i]->addBitmap(
			IDB_GUNER_STAND_RIGHT, IDB_GUNER_STAND_LEFT,
			0, 0, 0, 0,
			goRight, goLeft,
			attackRight, attackLeft, slash, lv_up);
	}

	ShowInitProgress(66);

	// Load Bitmaps of Maps

	map.push_back(Map1());
	map.push_back(Map2());
	map.push_back(Map3());
	for (size_t i = 0; i < map.size(); i++)
		map[i].LoadBitmap();

	slash_cd_0.LoadBitmap(IDB_SLASH_CD_0);
	slash_cd_1.LoadBitmap(IDB_SLASH_CD_1);
	slash_cd_2.LoadBitmap(IDB_SLASH_CD_2);
	slash_cd_3.LoadBitmap(IDB_SLASH_CD_3);
	slash_cd_4.LoadBitmap(IDB_SLASH_CD_4);
	slash_cd_5.LoadBitmap(IDB_SLASH_CD_5);
	slash_cd_6.LoadBitmap(IDB_SLASH_CD_6);
	slash_cd_7.LoadBitmap(IDB_SLASH_CD_7);
	slash_cd_8.LoadBitmap(IDB_SLASH_CD_8);
	heal_cd_0.LoadBitmap(IDB_HEAL_CD_0);
	heal_cd_1.LoadBitmap(IDB_HEAL_CD_1);
	heal_cd_2.LoadBitmap(IDB_HEAL_CD_2);
	heal_cd_3.LoadBitmap(IDB_HEAL_CD_3);
	heal_cd_4.LoadBitmap(IDB_HEAL_CD_4);
	heal_cd_5.LoadBitmap(IDB_HEAL_CD_5);
	heal_cd_6.LoadBitmap(IDB_HEAL_CD_6);
	heal_cd_7.LoadBitmap(IDB_HEAL_CD_7);
	heal_cd_8.LoadBitmap(IDB_HEAL_CD_8);

	ShowInitProgress(100);
}


void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard左箭頭
	const char KEY_UP    = 0x26; // keyboard上箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
	const char KEY_DOWN  = 0x28; // keyboard下箭頭
	const char KEY_Z = 0x5A; // keyboard Z
	const char KEY_X = 0x58; // keyboard X
	const char KEY_C = 0x43; // keyboard C
	Position hero_pos(hero, map[0]);

	if (nChar == KEY_Z) {
		hero->setAttacking(true);
		CAudio::Instance()->Play(SFX_ATTACK, true);
	}

	if (nChar == KEY_X) {
		//hero->setXP(hero->getLevel() * 50); //作弊升級用
		if (slash_cd == 300) {
			hero->setSlashing(true);
			CAudio::Instance()->Play(SFX_SLASH, false);
			slash_cd--;
		}
	}

	if (nChar == KEY_C) {
		//stage++;		 //作弊過關用
		if (heal_cd == 600) {
			hero->setHP(hero->getMaxHP());
			CAudio::Instance()->Play(SFX_HEAL, false);
			heal_cd--;
		}
	}

	if (nChar == KEY_LEFT) {
		hero->setMovingLeft(true);
		hero->setFacing(2);
	}
	
	if (nChar == KEY_RIGHT) {
		hero->setMovingRight(true);
		hero->setFacing(1);
	}

	if (nChar == KEY_UP) {
		if (stage == 1 && monster_num(monster1) == 0) {
			if (IN_PORTAL1)
				stage++;
			else
			{
				if (hero->ifMovingUp() == false)
					CAudio::Instance()->Play(SFX_JUMP, false);
				hero->setMovingUp(true);
			}
		}
		if (stage == 2 && monster_num(monster2) == 0) {
			if (IN_PORTAL2)
				stage++;
			else
			{
				if (hero->ifMovingUp() == false)
					CAudio::Instance()->Play(SFX_JUMP, false);
				hero->setMovingUp(true);
			}
		}
		if (stage == 3) {
			if (IN_PORTAL3)
				stage++;
			else 
			{
				if (hero->ifMovingUp() == false)
					CAudio::Instance()->Play(SFX_JUMP, false);
				hero->setMovingUp(true);
			}
		}
		else {
			if (hero->ifMovingUp() == false)
				CAudio::Instance()->Play(SFX_JUMP, false);
			hero->setMovingUp(true);
		}

	}
	if (nChar == KEY_DOWN) {
		hero->setMovingDown(true);
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard左箭頭
	const char KEY_UP    = 0x26; // keyboard上箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
	const char KEY_DOWN  = 0x28; // keyboard下箭頭
	const char KEY_Z = 0x5A; // keyboard Z

	if (nChar == KEY_Z) {
		hero->setAttacking(false);
		CAudio::Instance()->Stop(SFX_ATTACK);
	}
	if (nChar == KEY_LEFT) {
		hero->setMovingLeft(false);
		map[0].setMovingRight(false);
	}
	if (nChar == KEY_RIGHT) {
		hero->setMovingRight(false);
		map[0].setMovingLeft(false);
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

	if (stage == 1) {
		map[0].OnShow();			// 貼上背景圖
		if (monster_num(monster1) == 0)
			portal.OnShow(); 
		for (size_t i = 0; i < monster1.size(); i++)
			monster1[i]->OnShow();
	}
	if (stage == 2) {
		if (stage_count == 2) {
			hero->setXY(100, 570);
			portal.SetTopLeft(portal2X, 550);
			stage_count++;
			CAudio::Instance()->Stop(BGM_STAGE1);
			CAudio::Instance()->Play(BGM_STAGE2, true);
		}
		map[1].OnShow();			// 貼上背景圖
		if (monster_num(monster2) == 0)
			portal.OnShow();
		for (size_t i = 0; i < monster2.size(); i++)
			monster2[i]->OnShow();
	}
	if (stage == 3) {
		if (stage_count == 3) {
			hero->setXY(100, 570);
			portal.SetTopLeft(portal3X, 450);
			stage_count++;
			CAudio::Instance()->Stop(BGM_STAGE2);
			CAudio::Instance()->Play(BGM_STAGE3, true);
		}
		map[2].OnShow();			// 貼上背景圖
		if (monster_num(monster1) == 0)
			portal.OnShow();
	}
	hero->OnShow();			// 貼上人物
	if (slash_cd == 300) {
		slash_cd_0.SetTopLeft(15, 125);
		slash_cd_0.ShowBitmap();
	}
	if (slash_cd <= 299) {
		if (slash_cd >= 300 * 7 / 8) {
			slash_cd_8.SetTopLeft(15, 125);
			slash_cd_8.ShowBitmap();
		}
		else if (slash_cd >= 300 * 6 / 8) {
			slash_cd_7.SetTopLeft(15, 125);
			slash_cd_7.ShowBitmap();
		}
		else if (slash_cd >= 300 * 5 / 8) {
			slash_cd_6.SetTopLeft(15, 125);
			slash_cd_6.ShowBitmap();
		}
		else if (slash_cd >= 300 * 4 / 8) {
			slash_cd_5.SetTopLeft(15, 125);
			slash_cd_5.ShowBitmap();
		}
		else if (slash_cd >= 300 * 3 / 8) {
			slash_cd_4.SetTopLeft(15, 125);
			slash_cd_4.ShowBitmap();
		}
		else if (slash_cd >= 300 * 2 / 8) {
			slash_cd_3.SetTopLeft(15, 125);
			slash_cd_3.ShowBitmap();
		}
		else if (slash_cd >= 300 * 1 / 8) {
			slash_cd_2.SetTopLeft(15, 125);
			slash_cd_2.ShowBitmap();
		}
		else if (slash_cd > 300 * 0 / 8) {
			slash_cd_1.SetTopLeft(15, 125);
			slash_cd_1.ShowBitmap();
		}
	}
	if (heal_cd == 600) {
		heal_cd_0.SetTopLeft(60, 125);
		heal_cd_0.ShowBitmap();
	}
	if (heal_cd <= 599) {
		if (heal_cd >= 600 * 7 / 8) {
			heal_cd_8.SetTopLeft(60, 125);
			heal_cd_8.ShowBitmap();
		}
		else if (heal_cd >= 600 * 6 / 8) {
			heal_cd_7.SetTopLeft(60, 125);
			heal_cd_7.ShowBitmap();
		}
		else if (heal_cd >= 600 * 5 / 8) {
			heal_cd_6.SetTopLeft(60, 125);
			heal_cd_6.ShowBitmap();
		}
		else if (heal_cd >= 600 * 4 / 8) {
			heal_cd_5.SetTopLeft(60, 125);
			heal_cd_5.ShowBitmap();
		}
		else if (heal_cd >= 600 * 3 / 8) {
			heal_cd_4.SetTopLeft(60, 125);
			heal_cd_4.ShowBitmap();
		}
		else if (heal_cd >= 600 * 2 / 8) {
			heal_cd_3.SetTopLeft(60, 125);
			heal_cd_3.ShowBitmap();
		}
		else if (heal_cd >= 600 * 1 / 8) {
			heal_cd_2.SetTopLeft(60, 125);
			heal_cd_2.ShowBitmap();
		}
		else if (heal_cd > 600 * 0 / 8) {
			heal_cd_1.SetTopLeft(60, 125);
			heal_cd_1.ShowBitmap();
		}
	}
}
inline int CGameStateRun::monster_num(vector<Character*>monster) {
	int n = 0;
	for (size_t i = 0; i < monster.size(); i++)
		if (!monster[i]->ifDead())
			n++;
	return n;
}


void CGameStateRun :: heroMonsterInteraction(Character&hero, vector<Character*> & monster, Map &map) {

	for (size_t i = 0; i < monster.size(); i++) {
		if (monster[i]->ifDead())
			continue;

		Position monster_pos(monster[i], map);
		monster[i]->OnMove();

		// 人物移動相關
		if (hero.getX() <= 100 && hero.ifMovingLeft()) {
			if (hero_pos.getX() <= 110) {
				monster[i]->setMovingLeft(false);
			}
			else {
				monster[i]->setMovingLeft(true);
			}
		}
		else {
			monster[i]->setMovingLeft(false);
		}
		if (hero.getX() >= 1164 && hero.ifMovingRight()) {
			if (hero_pos.getX() >= 2200) {
				monster[i]->setMovingRight(false);
			}
			else {
				monster[i]->setMovingRight(true);
			}
		}
		else {
			monster[i]->setMovingRight(false);
		}

		// 怪物移動相關
		if (monster_pos.getX() - hero_pos.getX() >= monster[i]->getAttackRange() && monster_pos.getX() - hero_pos.getX() <= 500) {
			monster[i]->set_Monster_Go_Left(true);
			monster[i]->set_Monster_Go_Right(false);
		}
		else if (hero_pos.getX() - monster_pos.getX() >= monster[i]->getAttackRange() && hero_pos.getX() - monster_pos.getX() <= 500) {
			monster[i]->set_Monster_Go_Right(true);
			monster[i]->set_Monster_Go_Left(false);
		}
		else {
			monster[i]->set_Monster_Go_Right(false);
			monster[i]->set_Monster_Go_Left(false);
		}

		int flag = 0;
		for (int j = 0; j < 8; j++) {
			if (ON_PLATFORM_MONSTER)
				monster[i]->setFloor(570 - map.getFloorY(j));
			else
				flag++;
		}

		if (flag == 8) {
			monster[i]->setFloor(570);
		}

		// 攻擊互動相關
		if (MONSTER_HIT_CHARACTER(monster[i]->getAttackRange())) {
			if (HIT_CHECK_CHARACTER&&HEIGHT_CHECK) {
					monster[i]->setAttacking(true);
					hero.setHP(hero.getHP() - monster[i]->getAttack());
					CAudio::Instance()->Play(SFX_HERO_HIT, false);
					if(stage == 2)
						CAudio::Instance()->Play(SFX_GUN, false);
					if (monster_pos.getX() >= hero_pos.getX())
						hero.setHitLeft();
					else if (monster_pos.getX() < hero_pos.getX())
						hero.setHitRight();
					if (hero.getHP() <= 0)
						return;
			}
		}
		if (CHARACTER_HIT_MONSTER) {
			if (HIT_CHECK_MONSTER) {
				if (HEIGHT_CHECK) {
					monster[i]->setHP(monster[i]->getHP() - hero.getAttack());
					CAudio::Instance()->Play(SFX_MONSTER_HIT, false);
					if (hero.getFacing() == 2)
						monster[i]->setHitLeft();
					else if (hero.getFacing() == 1)
						monster[i]->setHitRight();
				}
			}
		}
		if (CHARACTER_SLASH_MONSTER) {
			if (HIT_CHECK_MONSTER) {
				if (SLASH_HEIGHT_CHECK) {
					monster[i]->setHP(monster[i]->getHP() - hero.getAttack() * 2);
					CAudio::Instance()->Play(SFX_MONSTER_HIT, false);
					if (monster_pos.getX() >= hero_pos.getX())
						monster[i]->setHitRight();
					else
						monster[i]->setHitLeft();
				}
			}
		}

		// 怪物死亡相關
		if (monster[i]->getHP() <= 0) {
			hero.setXP(hero.getXP() + monster[i]->getXP());
			monster[i]->setDead(true);
			monster[i]->setXY(-1, -1);
		}
	}
}
}