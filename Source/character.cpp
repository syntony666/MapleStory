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
	bool Character::ifAttacking(bool flag) { 
		return isAttacking; 
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
}