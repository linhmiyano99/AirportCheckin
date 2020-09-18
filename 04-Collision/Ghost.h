#pragma once
#include "Enemy.h"

#define GHOST_BBOX_WIDTH 40
#define GHOST_BBOX_HEIGHT 10

#define GHOST_SPEED 0.003f
#define GHOST_GRAVITY -0.05f

#define GHOST_DISTANCE_TOO_FAR 300

#define CHECKIN_0 225
#define CHECKIN_1 475
#define CHECKIN_2 725


class CGhost: public CEnemy
{
	static bool isStart;
	float _leftLimit;
	float _rightLimit;
	DWORD dt_check_in;
	int hang;
	int hang_checkin;
public:
	CGhost(float _x, float _y, int id = 0, int hang_checkin = 0);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	static void Start() { isStart = true; }
	static void Stop() { isStart = false; }
	static bool IsStart() { return isStart; }
	void SetHang(int hang, int hang_checkin);
	
};