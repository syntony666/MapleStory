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
		int  GetXr() {		// 右邊 x 座標
			return pos_rx;
		}
		int  GetYr() {		// 右邊 y 座標
			return pos_ry;
		}
		virtual void OnMove() = 0;	// 移動
		virtual void OnShow() = 0;	// 顯示角色
		void SetMovingDown(bool flag) { isMovingDown = flag; };	// 設定是否正在往下移動
		void SetMovingLeft(bool flag) { isMovingLeft = flag; };	// 設定是否正在往左移動
		void SetMovingRight(bool flag) { isMovingRight = flag; };	// 設定是否正在往右移動
		void SetMovingUp(bool flag) { isMovingUp = flag; };		// 設定是否正在往上移動
		void SetXY(int nx, int ny) {		// 設定Hero左上角座標

		}
		bool ifMovingLeft() { return isMovingLeft; }
		bool ifMovingRight() { return isMovingRight; }
		bool ifMovingUp() { return isMovingUp; }
		bool ifMovingDown() { return isMovingDown; }
		//protected:
		int pos_x;
		int pos_y;
		int pos_rx;
		int pos_ry;
		bool isMovingDown;			// 是否正在往下移動
		bool isMovingLeft;			// 是否正在往左移動
		bool isMovingRight;			// 是否正在往右移動
		bool isMovingUp;			// 是否正在往上移動
	};
}
#endif