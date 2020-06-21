#ifndef BOSS_H
#define BOSS_H

#include "character.h"
#include "counter.h"

namespace game_framework 
{
	struct BossAnimations	// 動畫
	{
		CAnimation normal;
	};
	enum BossCounter 
	{		// 倒數器名稱
		skills
	};
	class Boss
	{
	public:
		Boss() {};
		~Boss();
		void addBitmap();					// 設定圖檔
		void Initialize();					// 設定Boss為初始值
		void OnMove();						// 移動Boss
		void OnShow();						// 將Boss圖形貼到畫面
		void showHPBar();					// 顯示血量條
		void setMovingLeft(bool flag);		// 設定是否向左移動
		void setMovingRight(bool flag);		// 設定是否向左移動
		void setXY(int nx, int ny);			// 設定Boss位置
		void setHit();						// 設定是否被擊中
		void setHit(bool flag);				// 設定是否被擊中
		void setHP(int Health);				// 設定生命值
		bool ifHit();						// 擷取是否被擊中
		int getHP();						// 擷取生命值
		int getMaxHP();						// 擷取最大生命值
		int getAttack();					// 擷取攻擊力
		int getSkill();						// 擷取技能組代號
		Counter& getCounter(int i);			// 取得倒數器
	protected:
		const int HERO_STEP = 8;			// 挑戰者步伐大小
		const int floor = 570;				// 地板高度
		BossAnimations a;					// 動畫
		CMovingBitmap hpIcon;				// HP條旁的圖形
		int pos_x, pos_y;					// Boss位置
		bool isMovingRight, isMovingLeft;	// 是否移動
		bool isDead;						// 是否死亡
		bool isHit;							// 是否被攻擊
		int attack;							// 攻擊力
		int maxHP, HP;						// 最高血量, 目前血量
		int skill;							// 技能組代號
		int attack;					// 攻擊力
		std::vector<Counter*> counter;		// 倒數器
	};
}
#endif
