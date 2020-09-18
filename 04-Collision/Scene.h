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

#include "Simon.h"
#include "Map.h"
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
	static int cus_hang0;
	static int cus_hang1;
	static int cus_hang2;
	CMap* map;
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
	static int cusHang0Up();
	static int cusHang1Up();
	static int cusHang2Up();
	static int cusHang0Down();
	static int cusHang1Down();
	static int cusHang2Down();
	void setHang0(int n);
	void setHang1(int n);
	void setHang2(int n);
	bool getFirst(int hang);
	CScene(int id = 0);
	void LoadResoure();
	void Update(DWORD dt);
	void Render();
	void SetMap(int id = 0);
	int GetScene() { return id; }
	vector<LPGAMEOBJECT> GetObjects() { return objects; }
	int GetLeft();
	int GetTop();
	int GetRight();
	int GetBottom();
};
#endif // !__SMALLBALL_H__