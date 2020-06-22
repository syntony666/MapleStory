#ifndef CHARACTER_H
#define CHARACTER_H

#include "counter.h"

namespace game_framework
{

#define HP_PERCENT 100 * HP / maxHP
#define DEFAULT_RGB RGB(255, 255, 255)

	struct Animations
	{
		CAnimation standRight;	   // 站立
		CAnimation standLeft;	   // 站立面向左
		CAnimation downRight;	   // 向右趴下
		CAnimation downLeft;	   // 向左趴下
		CAnimation goLeft;		   // 向左走
		CAnimation goRight;		   // 向右走
		CAnimation jumpRight;	   // 向右跳
		CAnimation jumpLeft;	   // 向左跳
		CAnimation attackRight;	   // 向右攻擊
		CAnimation attackLeft;	   // 向左攻擊
		CAnimation slashAnimation; // 技能動畫
		CAnimation healAnimation;  // 技能動畫
		CAnimation lv_up;		   // 升級動畫
	};

	class Character
	{
	public:
		Character();
		~Character();
		virtual void Initialize() = 0; // 設定初始值
		virtual void OnMove() = 0;	   // 移動
		virtual void OnShow() = 0;	   // 顯示角色
		void addBitmap(int standR, int standL, int downR, int downL, int jumpR, int jumpL, vector<int> goR, vector<int> goL, vector<int> attackR, vector<int> attackL, vector<int> slash, vector<int> heal, vector<int> lv_up, int nR, int nG, int nB, int slash_ani = 2);
		//加入圖形(沒有的填0)
		virtual void attacking(Character *c) = 0;	// 攻擊的 virtual 函式
		Counter &getCounter(int i);					// 取得指定 Counter 的值
		void countdown();							// 同時啟動同個 class 內的所有計時器

		//HP

		void hp_addBitmaps();
		void hp_OnShow();

		//數字

		void number_addBitmaps();
		void number_OnShow(int nx, int pos_nx, int pos_ny);

		//SETs

		void setHP(int Health);			// 設定生命值
		void setAttack(int Atk);		// 設定攻擊力
		void setMaxHP(int Health);		// 設定最大生命值
		void setXP(int nxp);			// 設定經驗值
		void setLevel(int nlv);			// 設定等級
		void setLevelUP();				// 升級囉
		void setFloor(int Floor);		// 設定地板
		void setMovingDown(bool flag);	// 設定是否正在往下移動
		void setMovingLeft(bool flag);	// 設定是否正在往左移動
		void setMovingRight(bool flag); // 設定是否正在往右移動
		void setMovingUp(bool flag);	// 設定是否正在往上移動
		void setAttacking(bool flag);	// 設定是否正在攻擊
		void setFacing(int face);		// 設定面向方向
		void setXY(int nx, int ny);		// 設定Hero左上角座標
		void setHitLeft();				// 設定是否被擊中
		void setHitRight();				// 設定是否被擊中
		void setHitLeft(bool flag);		// 設定是否被擊中
		void setHitRight(bool flag);	// 設定是否被擊中
		void setDead(bool flag);		// 設定是否死亡
		void setPoison(bool flag);		// 設定是否中毒
		void setAttackRange(int n);		// 設定攻擊距離

		//Monsters
		void set_Monster_Go_Left(bool flag);	// 設定怪物往左移動
		void set_Monster_Go_Right(bool flag);	// 設定怪物往右移動
		void setSkill(int i);					// 設定怪物施放技能

		//Hero
		void setSlashing(bool flag);			// 設定角色施放技能
		bool ifSlashing();						// 判定角色施放技能
		void setHealing(bool flag);				// 設定角色施放技能
		bool ifHealing();						// 判定角色施放技能

		//GETs

		int getX();				// 左邊 x 座標
		int getY();				// 左邊 y 座標
		int getAttack();		// 擷取攻擊力
		int getHP();			// 擷取生命值
		int getMaxHP();			// 擷取最大生命值
		int getXP();			// 擷取經驗值
		int getLevel();			// 擷取等級
		int getFloor();			// 擷取地板
		int getFacing();		// 擷取面相方向
		int getAttackRange();	// 擷取攻擊範圍

		bool ifAttacking();		// 判定是否正在攻擊
		bool ifHitLeft();		// 判定是否受到往左攻擊
		bool ifHitRight();		// 判定是否受到往右攻擊
		bool ifMovingLeft();	// 判定是否正在往左移動
		bool ifMovingRight();	// 判定是否正在往右移動
		bool ifMovingUp();		// 判定是否正在跳躍
		bool ifMovingDown();	// 判定是否正在趴下
		bool ifPoison();		// 判定是否中毒
		bool ifDead();			// 判定是否死亡

	protected:
		CAnimation hp[11];				// 生命條
		CAnimation num[13];				// UI 與數字貼圖
		int pos_x, pos_y;				// 左邊座標
		int floor;						// 地板高度
		int HP, maxHP;					// 生命、最大生命
		int exp;						// 經驗值
		int level;						// 等級
		int facing;						// 1=面向右 2=面向左
		bool isMovingDown, isMovingUp,	// 是否正在移動
			isMovingRight, isMovingLeft;
		bool isAttacking;				// 是否正在攻擊
		bool isSlashing;				// 是否正在施放技能
		bool isHitLeft, isHitRight;		// 是否受到攻擊
		bool isDead;					// 是否死亡
		bool isPoison = false;			// 是否中毒
		bool isHealing;					// 是否治療中
		bool rising;					// true表上升、false表下降
		bool is_Monster_Go_Left, is_Monster_Go_Right;
		int initial_velocity;			// 初始速度
		int velocity;					// 目前的速度(點/次)
		int STEP_SIZE;					// 行走速度
		int attackRange;				// 攻擊範圍
		int skillRange;					// 技能範圍
		int skill;						// 技能指定
		Animations a;					// 所有 Character 使用之 Animation
		std::vector<Counter *> counter; // 計數器 Vector
		int hit_time;					// 受傷無敵時間
		int attack;						// 攻擊力
		int level_animation;			// 升等動畫時間
	};
} // namespace game_framework
#endif