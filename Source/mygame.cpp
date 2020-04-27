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
	CAudio::Instance()->Load(SFX_JUMP, "sounds\\sfx_jump.mp3");
	CAudio::Instance()->Load(BGM_GAMEOVER, "sounds\\bgm_gameover.mp3");

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
	initHero(*character);
	
	character->SetMaxHP(500);
	character->SetAttack(30);

	CAudio::Instance()->Stop(BGM_MENU);
	CAudio::Instance()->Play(BGM_STAGE1, true);

	for (size_t i = 0; i < monster.size(); i++) {
		monster[i]->Initialize();
		monster[i]->SetMaxHP(100);
		monster[i]->SetAttack(50);
	}
}

#define HEIGHT_CHECK hero_pos.getY() <= monster_pos.getY() + 100 && hero_pos.getY() + 100 >= monster_pos.getY()
#define HIT_CHECK_CHARACTER !character->ifHitLeft() && !character->ifHitRight()
#define HIT_CHECK_MONSTER !monster[i]->ifHitLeft() && !monster[i]->ifHitRight()
#define MONSTER_HIT_CHARACTER hero_pos.getX() - monster_pos.getX() <= 50 && monster_pos.getX() - hero_pos.getX() <= 0 || hero_pos.getX() - monster_pos.getX() <= 0 && monster_pos.getX() - hero_pos.getX() <= 50
#define CHARACTER_HIT_MONSTER character->ifAttacking() && character->GetFacing() == 2 && hero_pos.getX() - monster_pos.getX() <= 100 && monster_pos.getX() - hero_pos.getX() <= 0 || character->ifAttacking() && character->GetFacing() == 1 && hero_pos.getX() - monster_pos.getX() <= 0 && monster_pos.getX() - hero_pos.getX() <= 100
#define ON_PLATFORM hero_pos.getY() <= map1.getFloorY(i) + 100 && hero_pos.getY() >= map1.getFloorY(i) - 14 && hero_pos.getX() >= map1.getFloorXBegin(i) && hero_pos.getX() <= map1.getFloorXLast(i)

void CGameStateRun::OnMove()							// 移動遊戲元素
{
	TRACE("----monster_num---%d\n", monster.size());
	character->OnMove();
	map1.OnMove();
	Position hero_pos(character, map1);

	// 地圖移動相關
	if (character->getX() <= 100 && character->ifMovingLeft())
		map1.SetMovingLeft(true);
	else 
		map1.SetMovingLeft(false);
	if (character->getX() >= 1164 && character->ifMovingRight())
		map1.SetMovingRight(true);
	else
		map1.SetMovingRight(false);

	// 地板判定相關
	int flag = 0;
	for (int i = 0; i < 8; i++) {
		if (ON_PLATFORM) {
			character->SetFloor(570 - map1.getFloorY(i));
		}
		else {
			flag++;
		}
	}

	if (flag == 8) {
		character->SetFloor(570);
	}

	// 玩家死亡相關
	if (character->GetHP() <= 0)
		GotoGameState(GAME_STATE_OVER);

	for (size_t i = 0; i < monster.size(); i++) {
		Position monster_pos(monster[i], map1);
		monster[i]->OnMove();
		//TRACE("----hero-pos_xy---(%d, %d)\n", hero_pos.getX(), hero_pos.getY());
		//TRACE("----mons-pos_xy---(%d, %d)\n", monster_pos.getX(), monster_pos.getY());
		//TRACE("----------HP------(%d, %d)\n", monster[0]->GetHP(), character->GetHP());
		//TRACE("-------Floor------(%d)\n", character->GetFloor());
		//TRACE("------y to y------(%d, %d)\n", hero_pos.getY(), monster_pos.getY());

		// 人物移動相關
		if (character->getX() <= 100) {
			character->SetXY(100, character->getY());
		}
		else if (character->getX() >= 1164) {
			character->SetXY(1164, character->getY());
		}

		if (character->getX() <= 100) {
			character->SetXY(100, character->getY());
		}
		if (character->getX() <= 100 && character->ifMovingLeft()) {
			if (hero_pos.getX() <= 110) {
				monster[i]->SetMovingLeft(false);
			}
			else {
				monster[i]->SetMovingLeft(true);
			}
		}
		else {
			monster[i]->SetMovingLeft(false);
		}
		if (character->getX() >= 1164 && character->ifMovingRight()) {
			if (hero_pos.getX() >= 2200) {
				monster[i]->SetMovingRight(false);
			}
			else {
				monster[i]->SetMovingRight(true);
			}
		}
		else {
			monster[i]->SetMovingRight(false);
		}

		// 怪物移動相關
		if (monster_pos.getX() >= hero_pos.getX()) {
			monster[i]->Set_Monster_Go_Left(true);
			monster[i]->Set_Monster_Go_Right(false);
		}
		else {
			monster[i]->Set_Monster_Go_Right(true);
			monster[i]->Set_Monster_Go_Left(false);
		}

		// 地板判定相關

		// 攻擊互動相關
		if (MONSTER_HIT_CHARACTER && HIT_CHECK_CHARACTER) {
			if (HEIGHT_CHECK) {
				monster[i]->SetAttacking(true);
				character->SetHP(character->GetHP() - monster[i]->GetAttack());
				if (monster_pos.getX() >= hero_pos.getX())
					character->SetHitLeft();
				else if (monster_pos.getX() < hero_pos.getX())
					character->SetHitRight();
			}
		}
		if (CHARACTER_HIT_MONSTER && HIT_CHECK_MONSTER) {
			if (HEIGHT_CHECK) {
				monster[i]->SetHP(monster[i]->GetHP() - character->GetAttack());
				if (character->GetFacing() == 2)
					monster[i]->SetHitLeft();
				else if (character->GetFacing() == 1)
					monster[i]->SetHitRight();
			}
		}

		// 死亡相關
		if (monster[i]->GetHP() <= 0)
			monster.erase(monster.begin() + i);
	}
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(33);	// 接個前一個狀態的進度，此處進度視為33%
	//
	// 開始載入資料
	//
	for (size_t i = 0; i < monster.size(); i++) {
		monster[i]->LoadBitmap();
	}
	character->LoadBitmap();
	map1.LoadBitmap();					// 載入背景的圖形
	//
	// 完成部分Loading動作，提高進度
	//
	ShowInitProgress(50);
	//
	// 繼續載入其他資料
	//
	ShowInitProgress(100);
}

int map_position[] = { 0, 0 };

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard左箭頭
	const char KEY_UP    = 0x26; // keyboard上箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
	const char KEY_DOWN  = 0x28; // keyboard下箭頭
	const char KEY_Z = 0x5A; // keyboard Z

	if (nChar == KEY_Z) {
		character->SetAttacking(true);
	}

	if (nChar == KEY_LEFT) {
		character->SetMovingLeft(true);
		character->SetFacing(2);
	}
	
	if (nChar == KEY_RIGHT) {
		character->SetMovingRight(true);
		character->SetFacing(1);
	}

	if (nChar == KEY_UP) {
		character->SetMovingUp(true);
	}
	if (nChar == KEY_DOWN) {
		character->SetMovingDown(true);
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
		character->SetAttacking(false);

	}
	if (nChar == KEY_LEFT) {
		character->SetMovingLeft(false);
		map1.SetMovingRight(false);
	}
	if (nChar == KEY_RIGHT) {
		character->SetMovingRight(false);
		map1.SetMovingLeft(false);
	}
	if (nChar == KEY_UP)
		character->SetMovingUp(false);
	if (nChar == KEY_DOWN)
		character->SetMovingDown(false);
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
	map1.OnShow();			// 貼上背景圖
	for (size_t i = 0; i < monster.size(); i++) {
		monster[i]->OnShow();
	}
	character->OnShow();			// 貼上人物
}
}