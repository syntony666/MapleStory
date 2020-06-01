/*
 * mygame.h: 本檔案儲遊戲本身的class的interface
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 TY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include "hero.h"
#include "map.h"
#include "monster.h"
#include "boss.h"
#include "position.h"
#include "initialize.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	enum AUDIO_ID {				// 定義各種音效的編號
		BGM_MENU,				// 0
		BGM_STAGE1,				// 1
		BGM_STAGE2,				// 2
		BGM_STAGE3,				// 3
		BGM_STAGE4,				// 4
		BGM_BOSS,				// 5
		BGM_GAMEOVER,			// 6
		SFX_JUMP,				// 7
		SFX_ATTACK,				// 8
		SFX_SLASH,				// 9
		SFX_HERO_HIT,			// 10
		SFX_MONSTER_HIT,		// 11
		SFX_GUN,				// 12
		SFX_LEVEL_UP,			// 13
		SFX_HEAL,				// 14
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnKeyDown(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
	protected:
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		CMovingBitmap logo;								// csie的logo
		CMovingBitmap info;
		CMovingBitmap start1;
		CMovingBitmap start2;
		CMovingBitmap exit1;
		CMovingBitmap exit2;
		CMovingBitmap info1;
		CMovingBitmap info2;
		int menu = 1;									//判別值 1=上 2=下
		int ifInfoOn = 0;								//說明選單 0=關 1=開
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnLButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的動作 
		void OnRButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnRButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		int stage, stage_count;
		int slash_cd = 30 * 10;							// 技能CD
		int heal_cd = 30 * 20;							// 治癒CD
		int mage_skill_cd = 30*5;
		CMovingBitmap slashCD[9], healCD[9];
		CMovingBitmap	background;						// 背景圖
		Character *hero;								// 角色
		vector<Map> maps;								// 地圖
		Map *map;
		vector<Character*> monster1, monster2, monster3, monster4;// 怪物
		vector<Character*> *monster;
		Boss boss;
		Position hero_pos;
		int temp = 300;
		inline int monster_num(vector<Character*> monster);
		void heroMonsterInteraction(Character&hero, vector<Character*> & monster, Map &map);
		void heroBossInteraction(Character&hero, Boss &mboss, Map &map);
		void checkStage();
		void countDown(int &cd, int max, int min = 0);
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		int counter;	// 倒數之計數器
		CAnimation Gameover;
	};

}