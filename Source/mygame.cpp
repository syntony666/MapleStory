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
	CAudio::Instance()->Load(SFX_HERO_HIT, "sounds\\sfx_hero_hit.mp3");
	CAudio::Instance()->Load(SFX_MONSTER_HIT, "sounds\\sfx_monster_hit.mp3");
	CAudio::Instance()->Load(SFX_GUN, "sounds\\sfx_gun.mp3");

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
	CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
	CFont f,*fp;
	f.CreatePointFont(300,"Times New Roman");	// 產生 font f; 160表示16 point的字
	fp=pDC->SelectObject(&f);					// 選用 font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
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

	int over[] = { IDB_GAME_OVER_0 ,IDB_GAME_OVER_1 ,IDB_GAME_OVER_2 ,IDB_GAME_OVER_3,
					IDB_GAME_OVER_4 ,IDB_GAME_OVER_5 ,IDB_GAME_OVER_6 ,IDB_GAME_OVER_7,
					IDB_GAME_OVER_8 ,IDB_GAME_OVER_9 ,IDB_GAME_OVER_10,IDB_GAME_OVER_11,
					IDB_GAME_OVER_12,IDB_GAME_OVER_13,IDB_GAME_OVER_14,IDB_GAME_OVER_0,
					IDB_GAME_OVER_0 ,IDB_GAME_OVER_0 ,IDB_GAME_OVER_0 ,IDB_GAME_OVER_0,
					IDB_GAME_OVER_0 ,IDB_GAME_OVER_0 ,IDB_GAME_OVER_0 ,IDB_GAME_OVER_0,
					IDB_GAME_OVER_0 ,IDB_GAME_OVER_0 ,IDB_GAME_OVER_0 ,IDB_GAME_OVER_0, };

	Gameover = CAnimation(9);
	for (int i = 0; i < 28; i++)
		Gameover.AddBitmap(over[i], RGB(255, 255, 255));
}

void CGameStateOver::OnInit()
{
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//

	ShowInitProgress(66);	// 接個前一個狀態的進度，此處進度視為66%
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
}

void CGameStateRun::OnBeginState()
{
	initHero(*hero);
	initMonster1(monster1);

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
		hero_pos.SetPosition(hero, map[0]);
	}
	else if (stage == 2) {
		map[1].OnMove();
		hero_pos.SetPosition(hero, map[1]);
	}
	else if (stage == 3) {
		map[2].OnMove();
		hero_pos.SetPosition(hero, map[2]);
	}
	portal.OnMove();
	TRACE("-----------hero-pos_xy---(%d, %d)\n", hero_pos.getX(), hero_pos.getY());
	TRACE("--hero-level_Attack_HP---(%d, %d, %d)\n", hero->GetLevel(), hero->GetAttack(), hero->GetHP());
	TRACE("-----------Slash_CD------(%d)\n", slash_cd/30);
	TRACE("-----------Stage---------(%d)\n", stage);

	// 地圖移動相關
	if (hero->getX() <= 100 && hero->ifMovingLeft()) {
		if (stage == 1)
			map[0].SetMovingLeft(true);
		if (stage == 2)
			map[1].SetMovingLeft(true);
		if (stage == 3)
			map[2].SetMovingLeft(true);
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
			map[0].SetMovingLeft(false);
		if (stage == 2)
			map[1].SetMovingLeft(false);
		if (stage == 3)
			map[2].SetMovingLeft(false);
	}
	if (hero->getX() >= 1164 && hero->ifMovingRight()) {
		if (stage == 1)
			map[0].SetMovingRight(true);
		if (stage == 2)
			map[1].SetMovingRight(true);
		if (stage == 3)
			map[2].SetMovingRight(true);
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
			map[0].SetMovingRight(false);
		if (stage == 2)
			map[1].SetMovingRight(false);
		if (stage == 3)
			map[2].SetMovingRight(false);
	}

	// 人物移動相關
	if (hero_pos.getX() <= 100) {
		hero->SetXY(100, hero->getY());
	}
	else if (hero_pos.getX() >= 2204) {
		hero->SetXY(1164, hero->getY());
	}

	// 地板判定相關
	int flag = 0;
	for (int i = 0; i < 8; i++) {
		if (stage == 1) {
			if (ON_PLATFORM_STAGE1) 
				hero->SetFloor(570 - map[0].getFloorY(i));
			else 
				flag++;
		}
		if (stage == 2) {
			if (ON_PLATFORM_STAGE2) 
				hero->SetFloor(570 - map[1].getFloorY(i));
			else
				flag++;
		}
		if (stage == 3) {
			if (ON_PLATFORM_STAGE3) 
				hero->SetFloor(570 - map[2].getFloorY(i));
			else
				flag++;
		}
	}

	if (flag == 8) {
		hero->SetFloor(570);
	}

	// 玩家等級相關
	if (hero->GetXP() >= 100) {
		hero->SetXP(0);
		hero->SetLevel(hero->GetLevel() + 1);
		hero->SetMaxHP(hero->GetMaxHP() + hero->GetLevel() * 50);
		hero->SetAttack(hero->GetAttack() + hero->GetLevel() * 5);
	}

	// 玩家技能相關
	if (slash_cd <= 299) {
		slash_cd--;
		if (slash_cd == 0)
			slash_cd = 300;
	}

	// 玩家死亡相關
	if (hero->GetHP() <= 0)
		GotoGameState(GAME_STATE_OVER);

	for (size_t i = 0; i < monster1.size(); i++) {
		if (monster1[i]->ifDead())
			continue;

		Position monster1_pos(monster1[i], map[0]);
		monster1[i]->OnMove();

		// 人物移動相關
		if (hero->getX() <= 100 && hero->ifMovingLeft()) {
			if (hero_pos.getX() <= 110) {
				monster1[i]->SetMovingLeft(false);
			}
			else {
				monster1[i]->SetMovingLeft(true);
			}
		}
		else {
			monster1[i]->SetMovingLeft(false);
		}
		if (hero->getX() >= 1164 && hero->ifMovingRight()) {
			if (hero_pos.getX() >= 2200) {
				monster1[i]->SetMovingRight(false);
			}
			else {
				monster1[i]->SetMovingRight(true);
			}
		}
		else {
			monster1[i]->SetMovingRight(false);
		}

		// 怪物移動相關
		if (monster1_pos.getX() - hero_pos.getX()>=200) {
			monster1[i]->Set_Monster_Go_Left(true);
			monster1[i]->Set_Monster_Go_Right(false);
		}
		else if(hero_pos.getX() - monster1_pos.getX()>= 200) {
			monster1[i]->Set_Monster_Go_Right(true);
			monster1[i]->Set_Monster_Go_Left(false);
		}
		else {
			monster1[i]->Set_Monster_Go_Right(false);
			monster1[i]->Set_Monster_Go_Left(false);
		}

		// 攻擊互動相關
		if (MONSTER_HIT_CHARACTER(200)) {
			if (HIT_CHECK_CHARACTER) {
				if (HEIGHT_CHECK) {
					monster1[i]->SetAttacking(true);
					hero->SetHP(hero->GetHP() - monster1[i]->GetAttack());
					CAudio::Instance()->Play(SFX_HERO_HIT, false);
					if (monster1_pos.getX() >= hero_pos.getX())
						hero->SetHitLeft();
					else if (monster1_pos.getX() < hero_pos.getX())
						hero->SetHitRight();
				}
			}
		}
		if (CHARACTER_HIT_MONSTER) {
			if (HIT_CHECK_MONSTER) {
				if (HEIGHT_CHECK) {
					monster1[i]->SetHP(monster1[i]->GetHP() - hero->GetAttack());
					CAudio::Instance()->Play(SFX_MONSTER_HIT, false);
					if (hero->GetFacing() == 2)
						monster1[i]->SetHitLeft();
					else if (hero->GetFacing() == 1)
						monster1[i]->SetHitRight();
				}
			}
		}
		if (CHARACTER_SLASH_MONSTER) {
			if (HIT_CHECK_MONSTER) {
				if (SLASH_HEIGHT_CHECK) {
					monster1[i]->SetHP(monster1[i]->GetHP() - hero->GetAttack() * 2);
					CAudio::Instance()->Play(SFX_MONSTER_HIT, false);
					if (monster1_pos.getX() >= hero_pos.getX())
						monster1[i]->SetHitRight();
					else
						monster1[i]->SetHitLeft();
				}
			}
		}

		// 怪物死亡相關
		if (monster1[i]->GetHP() <= 0) {
			hero->SetXP(hero->GetXP() + monster1[i]->GetXP());
			monster1[i]->SetDead(true);
			monster1[i]->SetXY(-1, -1);
		}
	}
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

	hero->addBitmap(
		IDB_FROG_STAND_RIGHT, IDB_FROG_STAND_LEFT,
		IDB_FROG_DOWN_RIGHT, IDB_FROG_DOWN_LEFT,
		IDB_FROG_JUMP_RIGHT, IDB_FROG_JUMP_LEFT,
		hero_goRight, hero_goLeft,
		hero_attackRight, hero_attackLeft,slash);

	ShowInitProgress(33);	

	// Load Bitmaps of Monsters

	monster1.push_back(new Monster(500, 570, 50));
	monster1.push_back(new Monster(800, 570, 50));
	monster1.push_back(new Monster(1000, 570, 50));
	monster1.push_back(new Monster(1100, 570, 50));
	monster1.push_back(new Monster(1300, 570, 50));
	monster1.push_back(new Monster(2000, 570, 50));

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
		attackRight, attackLeft,slash);
	}

	ShowInitProgress(66);

	// Load Bitmaps of Maps

	map.push_back(Map1());
	map.push_back(Map2());
	map.push_back(Map3());
	for (size_t i = 0; i < map.size(); i++)
		map[i].LoadBitmap();

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
	Position hero_pos(hero, map[0]);

	if (nChar == KEY_Z) {
		hero->SetAttacking(true);
		CAudio::Instance()->Play(SFX_ATTACK, true);
	}

	if (nChar == KEY_X) {
		if (slash_cd == 300) {
			hero->SetSlashing(true);
			CAudio::Instance()->Play(SFX_SLASH, false);
			slash_cd--;
		}
	}

	if (nChar == KEY_LEFT) {
		hero->SetMovingLeft(true);
		hero->SetFacing(2);
	}
	
	if (nChar == KEY_RIGHT) {
		hero->SetMovingRight(true);
		hero->SetFacing(1);
	}

	if (nChar == KEY_UP) {
		if (monster_num(monster1)==0) {
			if (stage == 1) {
				if (IN_PORTAL1)
					stage++;
				else
				{
					if (hero->ifMovingUp() == false)
						CAudio::Instance()->Play(SFX_JUMP, false);
					hero->SetMovingUp(true);
				}
			}
			if (stage == 2) {
				if (IN_PORTAL2)
					stage++;
				else
				{
					if (hero->ifMovingUp() == false)
						CAudio::Instance()->Play(SFX_JUMP, false);
					hero->SetMovingUp(true);
				}
			}
			if (stage == 3) {
				if (IN_PORTAL3)
					stage++;
				else 
				{
					if (hero->ifMovingUp() == false)
						CAudio::Instance()->Play(SFX_JUMP, false);
					hero->SetMovingUp(true);
				}
			}
		}
		else {
			if (hero->ifMovingUp() == false)
				CAudio::Instance()->Play(SFX_JUMP, false);
			hero->SetMovingUp(true);
		}

	}
	if (nChar == KEY_DOWN) {
		hero->SetMovingDown(true);
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
		hero->SetAttacking(false);
		CAudio::Instance()->Stop(SFX_ATTACK);
	}
	if (nChar == KEY_LEFT) {
		hero->SetMovingLeft(false);
		map[0].SetMovingRight(false);
	}
	if (nChar == KEY_RIGHT) {
		hero->SetMovingRight(false);
		map[0].SetMovingLeft(false);
	}
	if (nChar == KEY_UP)
		hero->SetMovingUp(false);
	if (nChar == KEY_DOWN)
		hero->SetMovingDown(false);
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
	}
	if (stage == 2) {
		if (stage_count == 2) {
			initHero(*hero);
			portal.SetTopLeft(portal2X, 550);
			//monster1.push_back(new Monster(500, 570, 50));
			//monster1.push_back(new Monster(800, 570, 50));
			stage_count++;
			CAudio::Instance()->Stop(BGM_STAGE1);
			CAudio::Instance()->Play(BGM_STAGE2, true);
		}
		map[1].OnShow();			// 貼上背景圖
		if (monster_num(monster1) == 0)
			portal.OnShow();
	}
	if (stage == 3) {
		if (stage_count == 3) {
			initHero(*hero);
			portal.SetTopLeft(portal3X, 450);
			//monster1.push_back(new Monster(500, 570, 50));
			//monster1.push_back(new Monster(800, 570, 50));
			stage_count++;
			CAudio::Instance()->Stop(BGM_STAGE2);
			CAudio::Instance()->Play(BGM_STAGE3, true);
		}
		map[2].OnShow();			// 貼上背景圖
		if (monster_num(monster1) == 0)
			portal.OnShow();
	}
	for (size_t i = 0; i < monster1.size(); i++) {
		monster1[i]->OnShow();
	}
	hero->OnShow();			// 貼上人物
}
inline int CGameStateRun::monster_num(vector<Character*>monster) {
	int n = 0;
	for (size_t i = 0; i < monster.size(); i++)
		if (!monster[i]->ifDead())
			n++;
	return n;
}
}