class Boss {
public:
	Boss() {
		max_hp = 100000;
		initialize();
	}
	void initialize() {
		max_hp = 100000;
		hp = max_hp;
	}
	void setHP(int i) {
		hp = i;
	}
	int getHP() {
		return hp;
	}
private:
	int max_hp, hp;

};
