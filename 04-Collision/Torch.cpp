#include "Torch.h"
CTorch::~CTorch()
{
	CGameObject::~CGameObject();
	SAFE_DELETE(item);
}
CTorch::CTorch(float _x, float _y, int id, int type) : CGameObject(_x, _y, type)
{
	dt_die = 0;
	state = TORCH_STATE_EXSIST;
	
	switch (type)
	{
	case eType::TORCH:
		AddAnimation(501);
		break;
	case eType::CANDLE:
		AddAnimation(502);
		break;
	case eType::BRICK_1:
		AddAnimation(499);
		break;
	case eType::BRICK_2:
		AddAnimation(500);
		break;
	case eType::BRICK_3:
		AddAnimation(498);
		break;
	case eType::BRICK_4:
		AddAnimation(497);
		break;
	case eType::BRICK_5:
		AddAnimation(500);
		break;
	}
	AddAnimation(800); // fire
	AddAnimation(802); // bright

	x = _x;
	y = _y;
}

void CTorch::Render()
{

	if (state == TORCH_STATE_EXSIST)
	{
		animations[0]->Render(x, y);
	}
	else if (state == TORCH_STATE_ITEM)
	{
		if (item != NULL)
			item->Render();
	}
	else
	{
		if (GetTickCount() - dt_die <= 300)
		{
			animations[1]->Render(x, y);
			if(animations[1]->GetCurrentFrame() > 0)
				animations[2]->Render(x - 2, y - 5);
		}
	}

	//RenderBoundingBox();
}
void CTorch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (dt_die == 0)
	{
		if (state == TORCH_STATE_NOT_EXSIST) {
			dt_die = GetTickCount();
			if (item)
				item->SetPosition(x, y);
			else
				state = ITEM_STATE_NOT_EXSIST;
		}
	}
	else
	{
		if (item != NULL) {//co item
			if (GetTickCount() - dt_die > 150) // cho 150 mili second
			{
				item->Update(dt, coObjects);
				item->GetPosition(x, y);
				state = TORCH_STATE_ITEM;
			}
		}
	}

}

void CTorch::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == TORCH_STATE_EXSIST)
	{
		left = x;
		top = y;
		if (_type == eType::CANDLE)
		{
			right = x + CANDLE_WIDTH;
			bottom = y + CANDLE_HEIGHT;
		}
		else
		{
			right = x + TORCH_WIDTH;
			bottom = y + TORCH_HEIGHT;
		}
	}
	else if (state == TORCH_STATE_ITEM)
	{
		//item->SetPosition(x,y);
		item->GetBoundingBox(left, top, right, bottom);
	}
}
