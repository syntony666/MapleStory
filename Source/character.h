#define CHARACTER_H

class Character
{
public:
	Character();
	~Character();
	int getX() {
		return pos_x;
	}
	int getY() {
		return pos_y;
	}

private:
	int pos_x;
	int pos_y;
	int speed;
};
