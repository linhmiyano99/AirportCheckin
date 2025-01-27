﻿#include"Ghost.h"
#include"Scene.h"
#include"HidenObject.h"

bool CGhost::isStart = false;

CGhost::CGhost(float _x, float _y, int id, int hang_checkin ) :CEnemy(_x, _y, id, eType::GHOST)
{
	animations.clear();
	AddAnimation(1300);
	AddAnimation(1301);
	AddAnimation(1302);
	AddAnimation(1310);
	AddAnimation(1311);
	AddAnimation(1312);
	nx = -1;
	SetSpeed(0, 0);
	dt_appear = 0;
	hang = id;
	this->hang_checkin = hang_checkin;
	vx = 1;
}
void CGhost::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!CGhost::IsStart())
		return;
	if (dt_appear > 0)
	{
		if (GetTickCount() - dt_appear > dt_check_in) {
			Dead();
			dt_appear = 0;
			vx = vy = 0;
			x = GATE_X;
			y = GATE_Y;
			dt_check_in = 0;
			CScene::downGate(hang_checkin);
			CScene::upNumOfGate(hang_checkin);
			CScene::resetTimeGate(hang_checkin);
			hang_checkin = -1;
		}
		else 
		{
			if (GetTickCount() - dt_appear > 1000 * CScene::getTimeGate(hang_checkin))
			{
				CScene::upTimeGate(hang_checkin);
			}
		}
		return;
	}
	switch (hang_checkin)
	{
		case 0:
			if (x > CHECKIN_0)
			{
				vx = -0.005f * dt;
				vy = 0;
			}
			else vx = 0;
			break;
		case 2:
			if (x < CHECKIN_2)
			{
				vx = 0.005f * dt;
				vy = 0;
			}
			else
				vx = 0;
			break;
		default:
			if (vx < 0 && x < CHECKIN_1 + 1 || vx > 0 && x > CHECKIN_1 - 1)
			{
				vx = 0;
				vy = 0;
			}
			else if (x > CHECKIN_1 + 1 && vx <= 0)
			{
				vx = -0.005f * dt;
				vy = 0;
			}
			else if (x < CHECKIN_1 - 1 && vx >= 0)
			{
				vx = 0.005f * dt;
				vy = 0;
			}
			else {
				vx = 0;
				vy = 0;
			}
			break;
	}
	if (dt_die == 0)
	{
		if (state == TORCH_STATE_EXSIST)
		{
			float _x, _y;
			if (vx == 0) {
				vy = -GHOST_SPEED * dt;
				this->dt = dt;
				dx = 0;
				dy = vy * dt;
			}
			else {
				vy = 0;
				this->dt = dt;
				dx = vx * dt;
				dy = vy * dt;
				x += dx;
				return;
			}
			

			// Simple fall down
			vector<LPCOLLISIONEVENT> coEvents;
			vector<LPCOLLISIONEVENT> coEventsResult;

			coEvents.clear();


			CalcPotentialCollisions(coObjects, coEvents);

			if (coEvents.size() == 0)
			{
				x += dx;
				y += dy;
			}
			else {
				float min_tx, min_ty, nx = 0, ny_1;
				vy = 0;

				FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny_1);

				for (UINT i = 0; i < coEventsResult.size(); i++)
				{
					LPCOLLISIONEVENT e = coEventsResult[i];
					if (dynamic_cast<CHidenObject*>(e->obj))
					{
						CHidenObject* ohiden = dynamic_cast<CHidenObject*>(e->obj);
						dt_appear = GetTickCount();
						switch (ohiden->GetState()) {
							case eType::OBJECT_HIDDEN_GATE_0:
								dt_check_in = 1000 * (2 + rand() % 2);
							break;
							case eType::OBJECT_HIDDEN_GATE_1:
								dt_check_in = 1000 * (1 + rand() % 4);
							break;
							case eType::OBJECT_HIDDEN_GATE_2:
							dt_check_in = 1000 * (3 + rand() % 5);
							break;
						}
						vx = vy = 0;
						ohiden = NULL;
					}
					else {
						//y += min_ty * dy + ny * 0.4f;
						vy = 0;
						vx = 0;
						y += 0.4f;
					}

				}

			}
			// clean up collision events
			for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

		}
	}

}
void CGhost::Render()
{
	if (!CGhost::IsStart())
		return;
	if (x == 0 && y == 0)
		return;
	if (state == TORCH_STATE_EXSIST)
	{
		if (hang == 0)
		{
			if(vy != 0 || vx != 0)
				animations[0]->Render(x, y, nx, 255);
			else
				animations[3]->Render(x, y, nx, 255);
		}
		else if(hang == 1)
		{
			if (vy != 0 || vx != 0)
				animations[1]->Render(x, y, nx, 255);
			else
				animations[4]->Render(x, y, nx, 255);
		}
		else
		{
			if (vy != 0 || vx != 0)
				animations[2]->Render(x, y, nx, 255);
			else
				animations[5]->Render(x, y, nx, 255);
		}

	}

	//RenderBoundingBox();
}
void CGhost::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

	if (state == TORCH_STATE_EXSIST)
	{
		left = x;
		top = y;
		right = x + GHOST_BBOX_WIDTH;
		bottom = y + GHOST_BBOX_HEIGHT;
	}
}


void CGhost::SetHang(int hang, int hang_checkin) {
	this->hang = hang;
	this->hang_checkin = hang_checkin;
}


void CGhost::SetHang(int hang_checkin) {
	this->hang_checkin = hang_checkin;
	vy = 0;
	vx = -0.005f;
}
