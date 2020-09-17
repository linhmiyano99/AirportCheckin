#include "Game.h"
#include "Scene.h"
#include "Enemy.h"


CScene* CScene::__instance = NULL;
static bool isKillAllEnemy = false;

CScene* CScene::GetInstance()
{
	if (__instance == NULL) __instance = new CScene();
	return __instance;
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
	game->GetCamPos(cam_x, cam_y);
	
	if (start_killAllEnemy > 0)
	{
		if (GetTickCount() - start_killAllEnemy > TIME_KILL_ALL_ENEMY)
		{
			start_killAllEnemy = 0;
			BACKGROUND_COLOR = BACKGROUND_COLOR_DEFAULT;
		}
		else
		{
			if ((GetTickCount() - start_killAllEnemy) % 10 == 0)
			{
				if (BACKGROUND_COLOR == BACKGROUND_COLOR_DEFAULT)
				{
					BACKGROUND_COLOR = BACKGROUND_COLOR_CROSS;
				}
				else
				{
					BACKGROUND_COLOR = BACKGROUND_COLOR_DEFAULT;
				}
			}
		}
	}

	for each (LPGAMEOBJECT var in smallballs)
	{
		var->Update(dt);
	}

	game->GetCamPos(cam_x, cam_y);

	if (isAutoTran)
	{
		
		if (cam_x < auto_tran)
		{
			if (cam_x < auto_tran - SCREEN_WIDTH / 2)
				game->SetCamPos(cam_x + 2.0f, cam_y);// vận tốc chuyển màn 2.0f pixcel / milisecond 
			else
			{
			
					game->SetCamPos(cam_x + 2.0f, cam_y);// vận tốc chuyển màn 2.0f pixcel / milisecond 
			}

		}
		else
		{
			_stage++;
			id = GetStartScene();
			isAutoTran = false;
			
			CGate::Stop();
		}
	}
	else
	{
		if (id == 5)
		{
			Sound::GetInstance()->Stop(eSound::musicStage1);
			Sound::GetInstance()->Play(eSound::music_Boss);
		}
		float cx, cy;
		game->GetCamPos(cam_x, cam_y);
		grid->GetListObject(objects, cam_x, cam_y);

		
		// Update camera to follow simon
		cx = SCREEN_WIDTH / 2 - 40;
		//cy -= SCREEN_HEIGHT / 2 + 40;

		vector<LPGAMEOBJECT> coObjects;
		for (int i = 0; i < objects.size(); i++)
		{
			coObjects.push_back(objects[i]);
		}

		for (int i = 0; i < objects.size(); i++)
		{
			objects[i]->Update(dt, &coObjects);
		}


		if (cx < GetLeft())
			cx = GetLeft();
		if (id != 4)
		{
			if (cx > GetRight() - SCREEN_WIDTH)
				cx = GetRight() - SCREEN_WIDTH;
		}

		coObjects.clear();

	}

}
void CScene::Render() 
{
	CSprites::GetInstance()->Get(1000000)->Draw(0, 0);

	for each (LPGAMEOBJECT var in smallballs)
	{
		var->Render();
	}

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
	smallballs.push_back(smallball);
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
