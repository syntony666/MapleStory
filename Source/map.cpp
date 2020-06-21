#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "map.h"
#include "portal.h"

namespace game_framework {

	Map::Map(){
		Initialize();
	}
	Map::~Map() {
		//delete _portal;
	}
	void Map::Initialize() {
		zoom = 2;
		isMovingLeft = isMovingRight = false;
		rising = false;
	}

	void Map::LoadBitmap() {
		map.LoadBitmap(_bitmap);
	}
	void Map::setInitFloor(int i) {
		floor = i;
	}
	void Map::setInitXY(int x, int y) {
		_x = x;
		_y = y;
	}
	void Map::setInitZoom(double i) {
		zoom = i;
	}
	void Map::setInitPlatform(Platform *plats,int i) {
		floors = Floor(plats, i);
	}
	void Map::setInitBitmap(int bitmap) {
		_bitmap = bitmap;
	}
	void Map::setInitPortal(int x, int y) {
		_portal = Portal(x, y);
	}
	void Map::setMovingLeft(bool flag) {	
		isMovingLeft = flag;
	}
	void Map::setMovingRight(bool flag) {
		isMovingRight = flag;
	}
	void Map::OnMove() {
		const int STEP_SIZE = 8;

		if (_x >= -1020 && isMovingRight) {	//若碰壁就動地圖直到地圖的邊緣
			_x -= STEP_SIZE;
		}
		if (_x < 0 && isMovingLeft) {		//若碰壁就動地圖直到地圖的邊緣
			_x += STEP_SIZE;
		}
	}
	void Map::OnShow() {
		map.SetTopLeft(_x, _y);
		map.ShowBitmap(zoom);
	}
	void Map::portalOnShow() {
		_portal.OnShow(_portal.getX() + _x, _portal.getY());
	}
	int Map::getFloorXBegin(int i) const{
		return floors.getXBegin(i);
	}
	int Map::getFloorXLast(int i) const {
		return floors.getXLast(i);
	}
	int Map::getFloorY(int i) const {
		return floors.getY(i);
	}
	int Map::getX()const {
		return _x;
	}
	int Map::getY()const {
		return _y;
	}
	Portal& Map::getPortal() {
		return _portal;
	}
	bool Map::ifMovingLeft()const {	
		return isMovingLeft; 	
	}
	bool Map::ifMovingRight()const { 
		return isMovingRight;	
	}
}