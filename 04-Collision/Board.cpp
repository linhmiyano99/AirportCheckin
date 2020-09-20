#include "Board.h"
#include "Boss.h"
#include "Scene.h"
#include "Ghost.h"

CBoard* CBoard::__instance = NULL;

CBoard* CBoard::GetInstance()
{
	if (__instance == NULL) __instance = new CBoard();
	return __instance;
}

void CBoard::Update(DWORD dt)
{
	if (isStop)
	{
		return;
	}
	if (GetTickCount() - _count >= 1000)
	{
		_time++;
		_count = GetTickCount();
	}
}
void CBoard::Render()
{

	CGame* game = CGame::GetInstance();
	float cx, cy;
	game->GetCamPos(cx, cy);
	CSprites* sprites = CSprites::GetInstance();
	code->DrawNumber(6, 50, 600, _time);
	code->DrawNumber(1, CHECKIN_0, 50, CScene::getTimeGate(0));
	code->DrawNumber(1, CHECKIN_1, 50, CScene::getTimeGate(1));
	code->DrawNumber(1, CHECKIN_2, 50, CScene::getTimeGate(2));	
	
	
	code->DrawNumber(4, CHECKIN_0 - 80, 25, CScene::getNumOfGate(0));
	code->DrawNumber(4, CHECKIN_1 - 80, 25, CScene::getNumOfGate(1));
	code->DrawNumber(4, CHECKIN_2 - 80, 25, CScene::getNumOfGate(2));
	
	
	code->DrawNumber(4, CHECKIN_0 , 750, CScene::getGate(0));
	code->DrawNumber(4, CHECKIN_1 , 750, CScene::getGate(1));
	code->DrawNumber(4, CHECKIN_2 , 750, CScene::getGate(2));



	game = NULL;
	sprites = NULL;
}