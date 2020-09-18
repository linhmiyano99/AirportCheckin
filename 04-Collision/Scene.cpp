#include "Game.h"
#include "Scene.h"
#include "Enemy.h"
#include "Ghost.h"


CScene* CScene::__instance = NULL;
int CScene::cus_hang0 = 0;
int CScene::cus_hang1 = 0;
int CScene::cus_hang2 = 0;
static bool isKillAllEnemy = false;

int CScene::cusHang0Up() 
{
	return ++cus_hang0;
}
int CScene::cusHang1Up()
{
	return ++cus_hang1;

}
int CScene::cusHang2Up()
{
	return ++cus_hang2;

}
int CScene::cusHang0Down()
{
	return --cus_hang0;

}
int CScene::cusHang1Down()
{
	return --cus_hang1;

}
int CScene::cusHang2Down()
{
	return --cus_hang2;

}
CScene* CScene::GetInstance()
{
	if (__instance == NULL) __instance = new CScene();
	return __instance;
}
void CScene::setHang0(int n) {
	__hang0 = n;
}
void CScene::setHang1(int n) {
	__hang1 = n;
}
void CScene::setHang2(int n) {
	__hang2 = n;
}

CScene::CScene(int id)
{
	this->id = id;
	game = CGame::GetInstance();
	isAutoTran = false;
	auto_tran = 0;
	_stage = 1;
	isOutSide = true;
	//Sound::GetInstance()->Play(eSound::musicStage1);
	CManagementTexture* manage = new CManagementTexture();
	SAFE_DELETE(manage);
	CGhost::Start();
	id_cus = 0;
	__hang0 = 10;
	__hang1 = 20;
	__hang2 = 30;
}


void CScene::LoadResoure()
{
		CSprites::GetInstance()->Get(1000000)->Draw(0, 0);
		CHidenObject* cus = new CHidenObject(225, 73, 400);
		cus->SetState(400);
		coObjects.push_back(cus);
		cus = new CHidenObject(475, 73, 401);
		cus->SetState(401);
		coObjects.push_back(cus);
		cus = new CHidenObject(725, 73, 402);
		cus->SetState(402);
		coObjects.push_back(cus);
}

void CScene::Update(DWORD dt)
{
	if (GetTickCount() % 1000 == 0) {
		if (__hang0 + __hang1 + __hang2 > 0) {
			srand(time(NULL));
			int res = rand() % 3;
			if (res == 0 && __hang0 > 0 && getFirst(0) == false) {
				CGhost* cus = new CGhost(GATE_X, GATE_Y, 0);
				coObjects.push_back(cus);
				__hang0--;
				CScene::cusHang0Up();

			}
			else {
				if (res == 1 && __hang1 > 0 && getFirst(1) == false) {

					CGhost* cus = new CGhost(GATE_X, GATE_Y, 1);
					coObjects.push_back(cus);

					__hang1--;
					CScene::cusHang1Up();
				}
				else if (__hang2 > 0 && getFirst(2) == false) {

					CGhost* cus = new CGhost(GATE_X, GATE_Y, 2);
					coObjects.push_back(cus);
					__hang2--;
					CScene::cusHang2Up();
				}
			}
		}
	}
	
		for (int i = 0; i < coObjects.size(); i++)
		{
			if(coObjects[i]->GetState() == (TORCH_STATE_EXSIST))
			coObjects[i]->Update(dt, &coObjects);
		}
		
}
void CScene::Render() 
{
	CSprites::GetInstance()->Get(1000000)->Draw(0, 0);


	for (int i = 0; i < coObjects.size(); i++)
	{
		coObjects[i]->Render();
	}

}
void CScene::SetMap(int id)
{
	this->id = id;

}
int CScene::GetLeft()
{
	if (isAutoTran)
	{
		return cam_x;
	}
	switch (id)
	{
	case 0:
		return SCENCE_0_LEFT;
	case 1:
		return SCENCE_1_LEFT;
	case 2:
		return SCENCE_2_LEFT;
	case 3:
		return SCENCE_3_LEFT;
	case 4:
		return SCENCE_4_LEFT;
	case 5:
		return SCENCE_5_LEFT;
	default:
		return 0;
	}
}
int CScene::GetTop()
{
	switch (id)
	{
	case 0:
	case 1:
	case 2:
	case 4:
	case 5:
		return SCENCE_0_TOP;
	case 3:
		return SCENCE_1_TOP;
	default:
		return 0;
	}
}

bool CScene::getFirst(int hang)
{
	for each (LPGAMEOBJECT obj in coObjects)
	{
		if (obj->GetState() != TORCH_STATE_EXSIST) {
			obj->SetState(TORCH_STATE_EXSIST);
			obj->SetHang(hang);
			return true;
		}
	}
	return false;
}
