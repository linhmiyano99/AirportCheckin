#include "Game.h"
#include "Scene.h"
#include "Enemy.h"
#include "Ghost.h"


CScene* CScene::__instance = NULL;
static bool isKillAllEnemy = false;

CScene* CScene::GetInstance()
{
	if (__instance == NULL) __instance = new CScene();
	return __instance;
}

int CScene::gate0 = 0;
int CScene::gate1 = 0;
int CScene::gate2 = 0;

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
	__hang1 = 30;
	__hang2 = 60;
}


void CScene::LoadResoure()
{
		CSprites::GetInstance()->Get(1000000)->Draw(0, 0);
		CHidenObject* cus = new CHidenObject(225, 73, 400);
		coObjects.push_back(cus);
		cus = new CHidenObject(475, 73, 401);
		coObjects.push_back(cus);
		cus = new CHidenObject(725, 73, 402);
		coObjects.push_back(cus);
}

void CScene::Update(DWORD dt)
{
	if (__hang0 + __hang1 + __hang2 >0)
	{
		if (GetTickCount() % 1000 == 0) {
			srand(time(NULL));
			int res = rand() % 3;
			switch (res)
			{
				case 0:
					if (__hang0 > 0) {
						if (getFirst(0, 0) == false) {
							CGhost* cus = new CGhost(GATE_X, GATE_Y, 0, getGateNull(0));
							coObjects.push_back(cus);
						}
						__hang0--;
						break;
					}
				case 1:
					if (__hang1 > 0) {
						if (res == 1)
						{
							if (getFirst(1, 1) == false) {
								CGhost* cus = new CGhost(GATE_X, GATE_Y, 1, getGateNull(1));
								coObjects.push_back(cus);
							}
						}
						__hang1--;
						break;
					}
				default:
					if (__hang2 > 0) {
						if (getFirst(2, 2) == false) {
							CGhost* cus = new CGhost(GATE_X, GATE_Y, 2, getGateNull(2));
							coObjects.push_back(cus);
						}
						__hang2--;
						break;
					}
					if (__hang0 > 0) {
						if (getFirst(0, 0) == false) {
							CGhost* cus = new CGhost(GATE_X, GATE_Y, 0);
							coObjects.push_back(cus);
						}
						__hang0--;
						break;
					}
					if (__hang1 > 0) {
						if (getFirst(1, 1) == false) {
							CGhost* cus = new CGhost(GATE_X, GATE_Y, 1);
							coObjects.push_back(cus);
						}
						__hang1--;
						break;
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

bool CScene::getFirst(int hang, int hang_checkin)
{
	for each (LPGAMEOBJECT obj in coObjects)
	{
		if (obj->GetState() != TORCH_STATE_EXSIST && !dynamic_cast<CHidenObject*>(obj)) {
			obj->SetState(TORCH_STATE_EXSIST);
			obj->SetHang(hang, getGateNull(hang_checkin));
			return true;
		}
	}
	return false;
}

int CScene::getGateNull(int gate) {
	DebugOut(L"\n[getGateNull]  %d", getGate(0));
	DebugOut(L"\n[getGateNull]  %d", getGate(1));
	DebugOut(L"\n[getGateNull] %d", getGate(2));
	if (getGate(gate) > 3) {
		if (getGate(0) == 0)
		{
			upGate(0);
			return 0;
		}
		if (getGate(1) == 0)
		{
			upGate(1);
			return 1;
		}		
		if (getGate(2) == 0)
		{
			upGate(2);
			return 2;
		}
		switch (gate) {
		case 0:
			if (__hang1 == 0 && getGate(1) < getGate(0))
			{
				upGate(1);
				return 1;
			}			
			break;
		case 1:
			if (__hang0 == 0 && getGate(0) < getGate(1))
			{
				upGate(0);
				return 0;
			}			
			break;
		case 2:
			if (__hang0 == 0 && getGate(0) < getGate(1))
			{
				upGate(0);
				return 0;
			}			
			if (__hang1 == 0 && getGate(1) < getGate(0))
			{
				upGate(1);
				return 1;
			}
			if (__hang0 == 0 && __hang1 == 0) {
				if (getGate(0) < getGate(2))
				{
					upGate(0);
					return 0;
				}
			}
		}
	}
	upGate(gate);
	return gate;
}