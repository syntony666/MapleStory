#ifndef CHARACTER_H

#define CHARACTER_H

namespace game_framework {

	class Character
	{
	public:
		Character() {
		}
		virtual void Initialize() = 0;	// 設定初始值
		virtual void LoadBitmap() = 0;	// 載入圖形
		int getX() {		// 左邊 x 座標
			return pos_x;
		}
		int getY() {		// 左邊 y 座標
			return pos_y;
		}
		int  getXr() {		// 右邊 x 座標
			return pos_rx;
		}
		int  getYr() {		// 右邊 y 座標
			return pos_ry;
		}
		void getXY(int nx, int ny)
		{
			pos_x = nx; pos_y = ny;
		}
		virtual void OnMove() = 0;	// 移動
		virtual void OnShow() = 0;	// 顯示角色

		int GetAttack() { return attack; };			// 擷取攻擊力
		void SetAttack(int Atk) { attack = Atk; };	// 設定攻擊力
		int GetHP() { return hP; };					// 擷取生命值
		void SetHP(int Health) { hP = Health; };	// 設定生命值
		void SetMaxHP(int Health){					// 設定最大生命值
			maxHP = Health;
			hP = Health;
		};

		void SetFloor(int Floor) { floor = Floor; };	// 設定地板
		int GetFloor() { return floor; };

		void SetMovingDown(bool flag) { isMovingDown = flag; };	// 設定是否正在往下移動
		void SetMovingLeft(bool flag) { isMovingLeft = flag; };	// 設定是否正在往左移動
		void SetMovingRight(bool flag) { isMovingRight = flag; };	// 設定是否正在往右移動
		void SetMovingUp(bool flag) { isMovingUp = flag; };		// 設定是否正在往上移動
		void SetAttacking(bool flag) { isAttacking = flag; };		// 設定是否正在攻擊
		bool ifAttacking(bool flag) { return isAttacking; };
		void SetFacing(int face) { facing = face; };			// 設定面向方向
		int GetFacing() { return facing; };
		void SetXY(int nx, int ny) {		// 設定Hero左上角座標

		}
		bool ifMovingLeft() { return isMovingLeft; }
		bool ifMovingRight() { return isMovingRight; }
		bool ifMovingUp() { return isMovingUp; }
		bool ifMovingDown() { return isMovingDown; }
	protected:
		CAnimation hP_0, hP_10, hP_20, hP_30, hP_40, hP_50, hP_60, hP_70, hP_80, hP_90, hP_100;
		int pos_x;
		int pos_y;
		int pos_rx;
		int pos_ry;
		int attack;
		int floor;
		int hP, maxHP;
		int facing = 1;				// 1=面向右 2=面向左
		bool isMovingDown;			// 是否正在往下移動
		bool isMovingLeft;			// 是否正在往左移動
		bool isMovingRight;			// 是否正在往右移動
		bool isMovingUp;			// 是否正在往上移動
		bool isAttacking = false;	// 是否正在攻擊
		bool rising;			// true表上升、false表下降
		int initial_velocity;	// 初始速度
		int velocity;			// 目前的速度(點/次)
		int STEP_SIZE = 8;//
	};
}
#endif