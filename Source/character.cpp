#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "character.h"

namespace game_framework {

	int Character::getX() {
	return pos_x;
	}
	int Character::getY() {
		return pos_y;
	}
	int  Character::getXr() {
		return pos_rx;
	}
	int  Character::getYr() {
		return pos_ry;
	}
	void Character::SetXY(int nx, int ny)
	{
		pos_x = nx; pos_y = ny;
	}

	int Character::GetAttack() {
		return attack; 
	}
	void Character::SetAttack(int Atk) {
		attack = Atk;
	}
	int Character::GetHP() {
		return hP;
	}
	int Character::GetMaxHP() {
		return maxHP;
	}
	void Character::SetHP(int Health){
		hP = Health;
	}
	void Character::SetMaxHP(int Health) {
		maxHP = Health;
		hP = Health;
	}
	void Character::SetFloor(int Floor) {
		floor = Floor;
	}
	int Character::GetFloor() {
		return floor;
	}
	void Character::SetXP(int nxp) {
		exp = nxp;
	}
	int Character::GetXP() {
		return exp;
	}
	void Character::SetLevel(int nlv) {
		level = nlv;
	}
	int Character::GetLevel() {
		return level;
	}
	void Character::SetMovingDown(bool flag) {
		isMovingDown = flag; 
	}
	void Character::SetMovingLeft(bool flag) {
		isMovingLeft = flag;
	}
	void Character::SetMovingRight(bool flag) {
		isMovingRight = flag; 
	}	
	void Character::SetMovingUp(bool flag) { 
		isMovingUp = flag; 
	}
	void Character::SetAttacking(bool flag) { 
		isAttacking = flag; 
	}
	void Character::SetDead(bool flag) {
		isDead = flag;
	}
	bool Character::ifAttacking() { 
		return isAttacking; 
	}
	void Character::SetHitLeft() {
		isHitLeft = true;
	}
	void Character::SetHitLeft(bool flag) {
		isHitLeft = flag;
	}
	bool Character::ifHitLeft() {
		return isHitLeft;
	}
	void Character::SetHitRight() {
		isHitRight = true;
	}
	void Character::SetHitRight(bool flag) {
		isHitRight = flag;
	}
	bool Character::ifHitRight() {
		return isHitRight;
	}
	void Character::SetFacing(int face) {
		facing = face; 
	}
	int Character::GetFacing() {
		return facing;
	}
	void Character::hp_addBitmaps() {
		int hp_bitmaps[] = { IDB_HP_0,IDB_HP_10,IDB_HP_20,IDB_HP_30,IDB_HP_40,IDB_HP_50,IDB_HP_60,IDB_HP_70,IDB_HP_80,IDB_HP_90,IDB_HP_100 };
		for (int i = 0; i < 11; i++)
			hp[i].AddBitmap(hp_bitmaps[i]);
	}
	void Character::hp_OnShow() {
		for (int i = 10; i > 0; i--) {
			if (HP_PERCENT > 10 * (i - 1) && HP_PERCENT <= 10 * i) {
				hp[i].SetTopLeft(pos_x, pos_y - 20);
				hp[i].OnShow();
				break;
			}
		}
	}
	void Character::number_addBitmaps() {
		int number_bitmaps[] = { IDB_0,IDB_1,IDB_2,IDB_3,IDB_4,IDB_5,IDB_6,IDB_7,IDB_8,IDB_9,IDB_LV,IDB_HP,IDB_ATK };
		for (int i = 0; i < 13; i++)
			num[i].AddBitmap(number_bitmaps[i], RGB(230, 212, 132));
	}
	void Character::number_OnShow(int nx, int pos_nx, int pos_ny) {		//10 = Lv, 11 = HP, 12 = ATK
		num[nx].SetTopLeft(pos_nx, pos_ny);
		num[nx].OnShow();
	}
	void Character::SetLevelUP() {
		if(level_animation == 0)
			level_animation = 80;
	}
	bool Character::ifMovingLeft() {
		return isMovingLeft;
	}
	bool Character::ifMovingRight() {
		return isMovingRight; 
	}
	bool Character::ifMovingUp() { 
		return isMovingUp;
	}
	bool Character::ifMovingDown() { 
		return isMovingDown;
	}
	bool Character::ifDead() {
		return isDead;
	}
	


	void Character::addBitmap(int standR, int standL, int downR, int downL, int jumpR, int jumpL, vector<int> goR, vector<int> goL, vector<int> attackR, vector<int> attackL, vector<int> slash, vector<int> lv_up)
	{
		if (standR != 0)
			a.standRight.AddBitmap(standR, DEFAULT_RGB);
		if (standL != 0)
			a.standLeft.AddBitmap(standL, DEFAULT_RGB);
		if (downR != 0)
			a.downRight.AddBitmap(downR, DEFAULT_RGB);
		if (downL != 0)
			a.downLeft.AddBitmap(downL, DEFAULT_RGB);
		if (jumpR != 0)
			a.jumpRight.AddBitmap(jumpR, DEFAULT_RGB);
		if (jumpL != 0)
			a.jumpLeft.AddBitmap(jumpL, DEFAULT_RGB);
		a.goRight = CAnimation(3);
		a.goLeft = CAnimation(3);
		a.attackRight = CAnimation(2);
		a.attackLeft = CAnimation(2);
		a.slashAnimation = CAnimation(2);
		a.lv_up = CAnimation(4);
		for (size_t i = 0; i < goR.size(); i++) 
			a.goRight.AddBitmap(goR[i], DEFAULT_RGB);
		for (size_t i = 0; i < goL.size(); i++) 
			a.goLeft.AddBitmap(goL[i], DEFAULT_RGB);
		for (size_t i = 0; i < attackR.size(); i++) 
			a.attackRight.AddBitmap(attackR[i], DEFAULT_RGB);
		for (size_t i = 0; i < attackL.size(); i++) 
			a.attackLeft.AddBitmap(attackL[i], DEFAULT_RGB);
		for (size_t i = 0; i < slash.size(); i++)
			a.slashAnimation.AddBitmap(slash[i], RGB(0,0,0));
		for (size_t i = 0; i < lv_up.size(); i++)
			a.lv_up.AddBitmap(lv_up[i], RGB(3, 3, 3));
		hp_addBitmaps();
		number_addBitmaps();
	}


	// Monsters
	void Character::Set_Monster_Go_Left(bool flag) {
		is_Monster_Go_Left = flag;
	}
	void Character::Set_Monster_Go_Right(bool flag) {
		is_Monster_Go_Right = flag;
	}

	// Hero
	void Character::SetSlashing(bool flag) {
		isSlashing = flag;
	}
	bool Character::ifSlashing() {
		return isSlashing;
	}
}