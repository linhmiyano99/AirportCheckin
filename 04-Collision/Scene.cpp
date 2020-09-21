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

int CScene::num_of_gate0 = 0;
int CScene::num_of_gate1 = 0;
int CScene::num_of_gate2 = 0;

int CScene::time_of_gate0 = 0;
int CScene::time_of_gate1 = 0;
int CScene::time_of_gate2 = 0;

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
	board = CBoard::GetInstance();
	id_cus = 0;
	__hang0 = 10;
	__hang1 = 30;
	__hang2 = 60;
	check = 0;
}


void CScene::LoadResoure()
{
		CSprites::GetInstance()->Get(1000000)->Draw(0, 0);
		CHidenObject* cus = new CHidenObject(CHECKIN_0, 73, 400);
		coObjects.push_back(cus);
		cus = new CHidenObject(CHECKIN_1, 73, 401);
		coObjects.push_back(cus);
		cus = new CHidenObject(CHECKIN_2, 73, 402);
		coObjects.push_back(cus);
}

void CScene::Update(DWORD dt)
{
	board->Update(dt);
	if (__hang0 + __hang1 + __hang2 >0)
	{
		if (GetTickCount() % 1000 == 0) {
			srand(time(NULL));
			int res = rand() % 10;
			switch (res)
			{
				case 0:
					if (__hang0 > 0) {
						if (!getFirst(0, 0)) 
						{
							CGhost* cus = new CGhost(GATE_X, GATE_Y, 0, getGateNull(0));
							coObjects.push_back(cus);
						}
						__hang0--;
						break;
					}
				case 1:
				case 2:
				case 3:
					if (__hang1 > 0) {
						
							if (!getFirst(1, 1)) {
								CGhost* cus = new CGhost(GATE_X, GATE_Y, 1, getGateNull(1));
								coObjects.push_back(cus);
							}
						
						__hang1--;
						break;
					}
				default:
					if (__hang2 > 0) {
						if (!getFirst(2, 2)) {
							CGhost* cus = new CGhost(GATE_X, GATE_Y, 2, getGateNull(2));
							coObjects.push_back(cus);
						}
						__hang2--;
						break;
					}
					if (__hang0 > 0) {
						if (!getFirst(0, 0)) {
							CGhost* cus = new CGhost(GATE_X, GATE_Y, getGateNull(0));
							coObjects.push_back(cus);
						}
						__hang0--;
						break;
					}
					if (__hang1 > 0) {
						if (!getFirst(1, 1)) {
							CGhost* cus = new CGhost(GATE_X, GATE_Y, getGateNull(1));
							coObjects.push_back(cus);
						}
						__hang1--;
						break;
					}

			}

		}
		for (int i = 0; i < coObjects.size(); i++)
		{
			if (coObjects[i]->GetState() == (TORCH_STATE_EXSIST))
			{
				coObjects[i]->Update(dt, &coObjects);
			}
		}

	}
	else
	{
		if (check == 0 && getGate(0) == 0 && getGate(1) == 0) {
			check = 1;
			int temp = 0;
			for (int i = 0; i < coObjects.size(); i++)
			{
				if (coObjects[i]->GetState() == (TORCH_STATE_EXSIST))
				{
					temp++;
					if (temp > 3) {
						switch (temp % 5)
						{
						case 0:
							break;
						case 1:
						case 2:
							CScene::downGate(coObjects[i]->getHang());
							CScene::upGate(1);
							coObjects[i]->SetHang(1);
							break;
						default:
							CScene::downGate(coObjects[i]->getHang());
							CScene::upGate(0);
							coObjects[i]->SetHang(0);
							break;
						}
					}
				}

			}

		}
		else{
			for (int i = 0; i < coObjects.size(); i++)
			{
				if (coObjects[i]->GetState() == (TORCH_STATE_EXSIST))
				{
					coObjects[i]->Update(dt, &coObjects);
					DebugOut(L"\n[Hang] %d", coObjects[i]->getHang());
				}
			}
		}

	}

		
}
void CScene::Render() 
{
	CSprites::GetInstance()->Get(1000000)->Draw(0, 0);


	for (int i = 0; i < coObjects.size(); i++)
	{
		if (coObjects[i]->GetState() == (TORCH_STATE_EXSIST))
		{
			coObjects[i]->Render();
		}
	}
	board->Render();

}
void CScene::SetMap(int id)
{
	this->id = id;

}

bool CScene::getFirst(int hang, int hang_checkin)
{
	return false;
	//for (int i = 0; i < coObjects.size(); i++)
	//{
	//	if (coObjects[i]->GetState() != TORCH_STATE_EXSIST && !dynamic_cast<CHidenObject*>(coObjects[i])) {
	//		coObjects[i]->SetState(TORCH_STATE_EXSIST);
	//		hang_checkin = getGateNull(hang_checkin);
	//		coObjects[i]->SetHang(hang, hang_checkin);
	//		return true;
	//	}
	//}
	//return false;
}

int CScene::getGateNull(int gate) {
	
	if (getGate(gate) > 0) {
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