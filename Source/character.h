#ifndef CHARACTER_H

#define CHARACTER_H


namespace game_framework {

#define HP_PERCENT 100*hP/maxHP
#define DEFAULT_RGB RGB(255, 255, 255)

	struct Animations {
		CAnimation standRight;		// 站立
		CAnimation standLeft;		// 站立面向左
		CAnimation downRight;		// 向右趴下
		CAnimation downLeft;			// 向左趴下
		CAnimation goLeft;			// 向左走
		CAnimation goRight;			// 向右走
		CAnimation jumpRight;		// 向右跳
		CAnimation jumpLeft;			// 向左跳
		CAnimation attackRight;		// 向右攻擊
		CAnimation attackLeft;		// 向左攻擊
	};

	class Character
	{
	public:
		Character() {}
		virtual void Initialize() = 0;	// 設定初始值
		virtual void LoadBitmap() = 0;	// 載入圖形
		virtual void OnMove() = 0;		// 移動
		virtual void OnShow() = 0;		// 顯示角色

		//HP

		void hp_addBitmaps();
		void hp_OnShow();

		//SETs

		void SetHP(int Health);			// 設定生命值
		void SetAttack(int Atk);			// 設定攻擊力
		void SetMaxHP(int Health);		// 設定最大生命值
		void SetFloor(int Floor);		// 設定地板
		void SetMovingDown(bool flag);	// 設定是否正在往下移動
		void SetMovingLeft(bool flag);	// 設定是否正在往左移動
		void SetMovingRight(bool flag);	// 設定是否正在往右移動
		void SetMovingUp(bool flag);		// 設定是否正在往上移動
		void SetAttacking(bool flag);	// 設定是否正在攻擊
		void SetFacing(int face);		// 設定面向方向
		void SetXY(int nx, int ny);		// 設定Hero左上角座標
		void SetHitLeft();				// 設定是否被擊中
		void SetHitRight();				// 設定是否被擊中
		void SetDead(bool flag);		// 設定是否死亡

		//Monsters
		void Set_Monster_Go_Left(bool flag);
		void Set_Monster_Go_Right(bool flag);

		//GETs

		int getX();						// 左邊 x 座標
		int getY();						// 左邊 y 座標
		int getXr();						// 右邊 x 座標
		int getYr();						// 右邊 y 座標
		int GetAttack();					// 擷取攻擊力
		int GetHP();						// 擷取生命值
		int GetFloor();					// 擷取地板
		int GetFacing();
		bool ifAttacking();
		bool ifHitLeft();
		bool ifHitRight();
		bool ifMovingLeft();
		bool ifMovingRight();
		bool ifMovingUp();
		bool ifMovingDown();
	protected:
		CAnimation hp[11];
		int pos_x,	pos_y;				//左邊座標
		int pos_rx, pos_ry;				//右邊座標
		int attack;
		int floor;						//地板高度
		int hP, maxHP;
		int facing = 1;					// 1=面向右 2=面向左
		bool isMovingDown, isMovingUp,// 是否正在移動
			 isMovingRight, isMovingLeft;
		bool isAttacking = false;		// 是否正在攻擊
		bool isHitLeft = false;			// 是否受到攻擊
		bool isHitRight = false;		// 是否受到攻擊
		bool isDead = false;
		bool rising;					// true表上升、false表下降
		bool is_Monster_Go_Left = false;
		bool is_Monster_Go_Right = false;
		int initial_velocity;			// 初始速度
		int hit_time = 18;
		int velocity;					// 目前的速度(點/次)
		int STEP_SIZE = 8;				// 行走速度
		Animations a;
	};
}
#endif