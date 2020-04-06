#define CHARACTER_H

namespace game_framework {

	class Character
	{
	public:
		Character() {
		}
		virtual void Initialize() = 0;	// �]�w��l��
		virtual void LoadBitmap() = 0;	// ���J�ϧ�
		int getX() {		// ���� x �y��
			return pos_x;
		}
		int getY() {		// ���� y �y��
			return pos_y;
		}
		int  GetXr() {		// �k�� x �y��
			return pos_rx;
		}
		int  GetYr() {		// �k�� y �y��
			return pos_ry;
		}
		virtual void OnMove() = 0;	// ����
		virtual void OnShow() = 0;	// ��ܨ���
		virtual void SetMovingDown(bool flag) = 0;	// �]�w�O�_���b���U����
		virtual void SetMovingLeft(bool flag) = 0;	// �]�w�O�_���b��������
		virtual void SetMovingRight(bool flag) = 0;	// �]�w�O�_���b���k����
		virtual void SetMovingUp(bool flag) = 0;		// �]�w�O�_���b���W����
		void SetXY(int nx, int ny) {		// �]�wHero���W���y��

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
		bool isMovingDown;			// �O�_���b���U����
		bool isMovingLeft;			// �O�_���b��������
		bool isMovingRight;			// �O�_���b���k����
		bool isMovingUp;			// �O�_���b���W����
	};
}