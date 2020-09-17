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
#include "WhipUpgrade.h"
#include "ItemDagger.h"
#include "Brick.h"
#include "Dagger.h"
#include "HidenObject.h"
#include "Ghost.h"
#include "Panther.h"
#include "Gate.h"
#include "Bat.h"
#include "Fishman.h"
#include "Boss.h"
#include "Board.h"
#include "Grid.h"
#include "Axe.h"
#include "HolyWater.h"
#include "Boongmerang.h"
//#include "Sound.h"

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
	CBoss* boss;
	CMap* map;
	CDagger* dagger;
	CAxe* axe;
	CHollyWatter* holly;
	CBoongmerang* boongmerang;
	CGame* game;
	CHidenObject* hiden;
	CGrid* grid;
	//Sound* sound;
	CSprites* sprites;
	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> hide_gate;
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
	int getHang0();
	int getHang1();
	int getHang2();
	int downHang0();
	int downHang1();
	int downHang2();
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
	float GetSimonStartHeight();
	int GetStartScene();
	void TranScene();
	bool IsTranScene() { return isAutoTran; }
	void AddSmallBall(LPGAMEOBJECT smallball);
	void UpStage();
	int GetStage() { return _stage; }
	void SetScene(int scene) { id = scene; }
	void ResetScene();
	void TestStage(int stage);
	bool IsKillAllEnemy();
	void KillAllEnemy() { start_killAllEnemy = GetTickCount(); }
	bool IsOutSide() { return isOutSide; }
	void GoInside() { isOutSide = false; }
	float GetMapRight();
};
#endif // !__SMALLBALL_H__