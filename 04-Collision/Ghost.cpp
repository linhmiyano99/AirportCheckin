#include"Ghost.h"
#include"Scene.h"
#include"HidenObject.h"
#include"Torch.h"

bool CGhost::isStart = false;

CGhost::CGhost(float _x, float _y, int id) :CEnemy(_x, _y, id, eType::GHOST)
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
	hang_checkin = id;
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
			if (hang == 0) {
				CScene::cusHang0Down();
			}
			else if (hang == 1)
			{
				CScene::cusHang1Down();
			}
			else if (hang == 2)
			{
				CScene::cusHang2Down();
			}
		}
		return;
	}
	if (hang_checkin == 0)
	{
		if (x > CHECKIN_0)
			vx = -0.005f * dt;
		else vx = 0;
	}
	else if (hang_checkin == 2) {
		if (x < CHECKIN_2)
			vx = 0.005f * dt;
		else
			vx = 0;
	}
	else
		vx = 0;
	if (dt_die == 0)
	{
		if (state == TORCH_STATE_EXSIST)
		{
			float _x, _y;
			CSimon::GetInstance()->GetPosition(_x, _y);
			vy = -GHOST_SPEED * dt;
			this->dt = dt;
			dx = vx * dt;
			dy = vy * dt;

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
						CollisionWithHiden(dt, e->obj, min_tx, min_ty, nx, ny_1);
					}
					else {
						//y += min_ty * dy + ny * 0.4f;
						vy = 0;
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
	if (CScene::GetInstance()->IsTranScene())
		return;
	if (x == 0 && y == 0)
		return;
	if (state == TORCH_STATE_EXSIST)
	{
		if (hang == 0)
		{
			if(vy != 0)
				animations[0]->Render(x, y, nx, 255);
			else
				animations[3]->Render(x, y, nx, 255);
		}
		else if(hang == 1)
		{
			if (vy != 0)
				animations[1]->Render(x, y, nx, 255);
			else
				animations[4]->Render(x, y, nx, 255);
		}
		else
		{
			if (vy != 0)
				animations[2]->Render(x, y, nx, 255);
			else
				animations[5]->Render(x, y, nx, 255);
		}

	}
	else if (state == TORCH_STATE_ITEM)
	{
		if (item != NULL)
			item->Render();

	}
	else
	{
		if (GetTickCount() - dt_die < TIME_ENEMY_DIE)
		{
			animations[1]->Render(x, y);
			if (animations[1]->GetCurrentFrame() > 0)
				animations[2]->Render(x - 2, y - 5);
		}
	}

	RenderBoundingBox();
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
	else if (state == TORCH_STATE_ITEM)
	{
		item->GetBoundingBox(left, top, right, bottom);
	}
}
void CGhost::CollisionWithBrick(DWORD dt, LPGAMEOBJECT& obj, float min_tx0, float min_ty0, int nx0, int ny0)
{

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	vector<LPGAMEOBJECT> list;
	list.push_back((LPGAMEOBJECT)(obj));
	// turn off collision when die 

	CalcPotentialCollisions(&list, coEvents);

	float min_tx, min_ty, nx = 0, ny;

	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

	//// block 
	
	list.clear();
}

void CGhost::CollisionWithHiden(DWORD dt, LPGAMEOBJECT& obj, float min_tx0, float min_ty0, int nx0, int ny0)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	vector<LPGAMEOBJECT> list;
	list.push_back((LPGAMEOBJECT)(obj));
	// turn off collision when die 

	CalcPotentialCollisions(&list, coEvents);

	float min_tx, min_ty, nx = 0, ny;

	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

	//// block 

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	CHidenObject* ohiden = dynamic_cast<CHidenObject*>(obj);
	dt_appear = GetTickCount();
	if (ohiden->GetState() == eType::OBJECT_HIDDEN_GATE_0)
	{
		dt_check_in = 1000 * (2 + rand() % 2);
	
	}
	else if (ohiden->GetState() == eType::OBJECT_HIDDEN_GATE_1)
	{
		dt_check_in = 1000 * (1 + rand() % 4);

	}
	else if (ohiden->GetState() == eType::OBJECT_HIDDEN_GATE_2)
	{
		dt_check_in = 1000 * (3 + rand() % 5);

	}


	ohiden = NULL;
	list.clear();
}