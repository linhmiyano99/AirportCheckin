#include "Game.h"
#include "Scene.h"
#include "Enemy.h"


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
int CScene::getHang0(){
	return __hang0;
}
int CScene::getHang1() {
	return __hang1;
}
int CScene::getHang2(){
	return __hang2;
}
int CScene::downHang0(){
	return --__hang0;
}
int CScene::downHang1() {
	return --__hang1;
}
int CScene::downHang2(){
	return --__hang2;
}
CScene::CScene(int id)
{
	this->id = id;
	map = CMap::GetInstance();
	game = CGame::GetInstance();
	grid = CGrid::GetInstance();
	isAutoTran = false;
	auto_tran = 0;
	_stage = 1;
	isOutSide = true;
	Sound::GetInstance()->Play(eSound::musicStage1);
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
	if (id == 0) {
		CSprites::GetInstance()->Get(1000000)->Draw(0, 0);
		grid->LoadObject("texture/objects_1.txt");
	}
	else
	{
		CSprites::GetInstance()->Get(1000000)->Draw(0, 0);
		isOutSide = false;
		grid->LoadObject("texture/objects_2.txt");

	}
	

}
		

void CScene::Update(DWORD dt)
{
	if (GetTickCount() % 3000 == 0) {
		if (getHang0() + getHang1() + getHang2() > 0) {
			srand(time(NULL));
			int res = rand() % 3;
			if (res == 0 && getHang0() > 0) {
				CGhost *cus = new CGhost(GATE_X, GATE_Y, 0);
				grid->addObject(id_cus++, cus);
				downHang0();
				CScene::cusHang0Up();
			}
			else if (res == 1 && getHang1() > 0) {
				CGhost* cus = new CGhost(GATE_X, GATE_Y, 1);
				grid->addObject(id_cus++, cus);		
				downHang1();				
				CScene::cusHang1Up();
			}
			else {
				CGhost* cus = new CGhost(GATE_X, GATE_Y, 2);
				grid->addObject(id_cus++, cus);
				downHang2();
				CScene::cusHang2Up();
			}
		}
	}
	grid->GetListObject(objects, 0, 0);
	for (int i = 0; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

		
		// Update camera to follow simon
		//cy -= SCREEN_HEIGHT / 2 + 40;
		for (int i = 0; i < objects.size(); i++)
		{
			objects[i]->Update(dt, &coObjects);
		}
		
}
void CScene::Render() 
{
	CSprites::GetInstance()->Get(1000000)->Draw(0, 0);


	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Render();
	}

	switch (CBoard::GetInstance()->GetWeapon())
	{
	case  eType::DAGGER:
		CDagger::GetInstance()->Render();
		break;
	case eType::ITEMAXE:
		CAxe::GetInstance()->Render();
		break;
	case eType::ITEMHOLLYWATTER:
		CHollyWatter::GetInstance()->Render();
		break;
	case eType::ITEMBOONGMERANG:
		CBoongmerang::GetInstance()->Render();
		break;
	default:
		break;
	}

	float s_x, s_y;

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
int CScene::GetRight()
{
	if (isAutoTran)
	{
		return cam_x + SCREEN_WIDTH;
	}
	switch (id)
	{
	case 0:
		return SCENCE_0_RIGHT;
	case 1:
		return SCENCE_1_RIGHT;
	case 2:
	case 3:
		return SCENCE_3_RIGHT;
	case 4:
	case 5:
		return SCENCE_5_RIGHT;
	default:
		return 0;
	}
}
int CScene::GetBottom()
{
	switch (id)
	{
	case 0:
	case 1:
	case 2:
	case 4:
	case 5:
		return SCENCE_0_BOTTOM;
	case 3:
		return SCENCE_1_BOTTOM;
	default:
		return SCENCE_0_BOTTOM;
	}
}

void CScene::TranScene()
{
	auto_tran = GetRight();
	isAutoTran = true;

}
void CScene::AddSmallBall(LPGAMEOBJECT smallball)
{
}

void CScene::UpStage()
{ 
	_stage++;
}
void CScene::ResetScene()
{
	if (id == 3 || id == 2)
		id = 2;
	else if (id == 5 || id == 4)
	{
		id = 4;
		CBoss::GetInstance()->ResetBoss();
		Sound::GetInstance()->Play(eSound::musicStage1);
		Sound::GetInstance()->Stop(eSound::music_Boss);
	}
}
void CScene::TestStage(int stage)
{
	_stage = stage;
	switch (_stage)
	{
	case 1:
		id = 1;
		break;
	case 2:
		id = 2;
		CBat::Start();
		break;
	case 3:
		id = 4;
		break;
	default:
		id = 1;
		break;
	}
	LoadResoure();
	CGate::Stop();
}
bool CScene::IsKillAllEnemy()
{
	if (start_killAllEnemy > 0)
		return true;
	return false;
}
float CScene::GetSimonStartHeight()
{
	switch (_stage)
	{
		case 1:
			return SIMON_START_LOW;
		case 2:
		case 3:
			return SIMON_START_HIGH;
	default:
		return SIMON_START_HIGH;
		break;
	}
}
int CScene::GetStartScene()
{
	switch (_stage)
	{
	case 1:
		return 1;
	case 2:
		return 2;
	case 3:
		return 4;
	default:
		return 0;
		break;
	}
}
float CScene::GetMapRight()
{
	if (id == 0)
		return SCENCE_0_RIGHT;
	else
		return SCENCE_5_RIGHT;
}
