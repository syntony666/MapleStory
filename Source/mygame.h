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

namespace game_framework
{
#define SEC 30
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	enum AUDIO_ID
	{					 // 定義各種音效的編號
		BGM_MENU,		 // 0
		BGM_STAGE1,		 // 1
		BGM_STAGE2,		 // 2
		BGM_STAGE3,		 // 3
		BGM_BOSS,		 // 4
		BGM_GAMEOVER,	 // 5
		SFX_JUMP,		 // 6
		SFX_ATTACK,		 // 7
		SFX_SLASH,		 // 8
		SFX_HERO_HIT,	 // 9
		SFX_MONSTER_HIT, // 10
		SFX_GUN,		 // 11
		SFX_LEVEL_UP,	 // 12
		SFX_HEAL,		 // 13
		SFX_ROOT,		 // 14
		BGM_CLEAR,		 // 15
		SFX_LASER,		 // 16
		SFX_LIGHTING,	 // 17
		SFX_KNOCKBACK	 // 18
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState
	{
	public:
		CGameStateInit(CGame *g);
		void OnInit();									// 遊戲的初值及圖形設定
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnKeyDown(UINT, UINT, UINT);				// 處理按下按鍵的反應
		void OnLButtonDown(UINT nFlags, CPoint point);	// 處理滑鼠的動作
	protected:
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		CMovingBitmap logo;		// 封面圖
		CMovingBitmap info;		// 說明頁面
		CMovingBitmap start1;	// 開始按鈕
		CMovingBitmap start2;	// 開始按鈕(選擇中)
		CMovingBitmap exit1;	// 離開按鈕
		CMovingBitmap exit2;	// 離開按鈕(選擇中)
		CMovingBitmap info1;	// 說明按鈕
		CMovingBitmap info2;	// 說明按鈕(選擇中)
		int menu = 1;			// 選單判定用
		int ifInfoOn = 0;		// 說明選單 0=關 1=開
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun : public CGameState
	{
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();									// 遊戲的初值及圖形設定
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		void OnLButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		void OnRButtonDown(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		void OnRButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
	protected:
		void OnMove(); // 移動遊戲元素
		void OnShow(); // 顯示這個狀態的遊戲畫面
	private:
		int stage, stage_count;
		CMovingBitmap slashCD[9], healCD[9];				// 技能 CD 圖
		CMovingBitmap background;							// 背景圖
		CMovingBitmap PoisonRoot;							// 定身圖片
		CAnimation Boss_laser_delay, Boss_laser;			// 這三行都是 BOSS 的技能動畫
		CAnimation Boss_knockback_delay, Boss_knockback;
		CAnimation Boss_lighting_delay1, Boss_lighting_delay2, Boss_lighting1, Boss_lighting2;
		Character *hero;									// 角色
		vector<Map> maps;									// 地圖
		Map *map;
		vector<Character *> monster1, monster2, monster3;	// 怪物
		vector<Character *> *monster;
		Boss boss;											// BOSS
		Position hero_pos;									// 角色座標位置
		inline int monster_num(vector<Character *> monster);	// 怪物剩餘數量判定
		void heroMonsterInteraction(Character &hero, vector<Character *> &monster, Map &map);	// 角色與怪物互動判定
		void heroBossInteraction(Character &hero, Boss &mboss, Map &map);						// 角色與 BOSS 互動判定
		void checkStage();									// 關卡檢測用
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState
	{
	public:
		CGameStateOver(CGame *g);
		//~CGameStateOver();
		void OnBeginState(); // 設定每次重玩所需的變數
		void OnInit();

	protected:
		void OnMove(); // 移動遊戲元素
		void OnShow(); // 顯示這個狀態的遊戲畫面
		void number_OnShow(int nx, int pos_nx, int pos_ny); // 顯示數字 Bitmap 用

	private:
		int counter = 210; // 倒數之計數器
		int clearTime = 0; // 紀錄過關時間用
		CAnimation Gameover; // 通關失敗動畫
		CMovingBitmap clear_info; // 過關背景圖
		CAnimation num[10]; // 顯示數字 Bitmap
	};

}