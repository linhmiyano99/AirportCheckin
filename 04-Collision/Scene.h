#ifndef __SCENE_H__

#define __SCENE_H__


#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "fstream"

#include "debug.h"
#include "GameObject.h"
#include "Textures.h"
#include "MagagementTexture.h"
#include "Define.h"

#include "Camera.h"
#include "HidenObject.h"


#define TIME_KILL_ALL_ENEMY 1000
#define GATE_X 475 
#define GATE_Y 750


class CScene
{
	static CScene* __instance;
	int __hang0;
	int __hang1;
	int __hang2;
	static int gate0;
	static int gate1;
	static int gate2;
	CGame* game;
	CHidenObject* hiden;
	//Sound* sound;
	CSprites* sprites;
	vector<LPGAMEOBJECT> objects;
	int id;
	int _stage;
	bool isAutoTran;
	float auto_tran;
	DWORD start_killAllEnemy;
	float cam_x;
	float cam_y;
	bool isOutSide;
	vector<LPGAMEOBJECT> coObjects;
	int id_cus;

public:
	static CScene* GetInstance();
	bool getFirst(int hang, int hang_checkin);
	CScene(int id = 0);
	void LoadResoure();
	void Update(DWORD dt);
	void Render();
	void SetMap(int id = 0);
	int GetScene() { return id; }
	vector<LPGAMEOBJECT> GetObjects() { return objects; }
	static int getGate(int gate) {
		switch (gate) {
		case 0:
			return gate0;
		case 1:
			return gate1;
		case 2:
			return gate2;
		}
	}
	static int upGate(int gate) {
		switch (gate) {
		case 0:
			return ++gate0;
		case 1:
			return ++gate1;
		case 2:
			return ++gate2;
		}
	}
	static int downGate(int gate) {
		switch (gate) {
		case 0:
			return --gate0;
		case 1:
			return --gate1;
		case 2:
			return --gate2;
		}
	}
	int getGateNull(int gate);
	void nullGate(int gate) {
		switch (gate) {
		case 0:
			gate0 = 0;
			break;
		case 1:
			gate1 = 0;
			break;
		case 2:
			gate2 = 0;
			break;
		}
	}
};
#endif // !__SMALLBALL_H__