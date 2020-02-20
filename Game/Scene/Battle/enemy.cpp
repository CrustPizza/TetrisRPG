#include "stdafx.h"
#include "enemy.h"

HRESULT enemy::init()
{
	// 아이템 정보 초기화
	_item = new Item;
	_item->init();

	// 에너미 생성상태 초기화
	_blueStone.create = false;
	_darkBrownStone.create = false;
	_greenStone.create = false;
	_orangeStone.create = false;
	_fullColorStone.create = false;

	return S_OK;
}

void enemy::release()
{
	// 파란색 생성중일때 체력바 및 액션바 해제
	if (_blueStone.create)
	{
		if (_blueStone.hpBar != nullptr)
		{
			_blueStone.hpBar->release();
			SAFE_DELETE(_blueStone.hpBar);
		}
	
		if (_blueStone.actionBar != nullptr)
		{
			_blueStone.actionBar->release();
			SAFE_DELETE(_blueStone.actionBar);
		}
	}

	// 흑갈색 생성중일때 체력바 및 액션바 해제
	if (_darkBrownStone.create)
	{
		if (_darkBrownStone.hpBar != nullptr)
		{
			_darkBrownStone.hpBar->release();
			SAFE_DELETE(_darkBrownStone.hpBar);
		}
	
		if (_darkBrownStone.actionBar != nullptr)
		{
			_darkBrownStone.actionBar->release();
			SAFE_DELETE(_darkBrownStone.actionBar);
		}
	}
	
	// 녹색 생성중일때 체력바 및 액션바 해제
	if (_greenStone.create)
	{
		if (_greenStone.hpBar != nullptr)
		{
			_greenStone.hpBar->release();
			SAFE_DELETE(_greenStone.hpBar);
		}
	
		if (_greenStone.actionBar != nullptr)
		{
			_greenStone.actionBar->release();
			SAFE_DELETE(_greenStone.actionBar);
		}
	}
	
	// 주황색 생성중일때 체력바 및 액션바 해제
	if (_orangeStone.create)
	{
		if (_orangeStone.hpBar != nullptr)
		{
			_orangeStone.hpBar->release();
			SAFE_DELETE(_orangeStone.hpBar);
		}
	
		if (_orangeStone.actionBar != nullptr)
		{
			_orangeStone.actionBar->release();
			SAFE_DELETE(_orangeStone.actionBar);
		}
	}

	// 혼합색 생성중일때 체력바 및 액션바 해제
	if (_fullColorStone.create)
	{
		if (_fullColorStone.hpBar != nullptr)
		{
			_fullColorStone.hpBar->release();
			SAFE_DELETE(_fullColorStone.hpBar);
		}
	
		if (_fullColorStone.actionBar != nullptr)
		{
			_fullColorStone.actionBar->release();
			SAFE_DELETE(_fullColorStone.actionBar);
		}
	}

	// 아이템 해제
	_item->release();
	SAFE_DELETE(_item);
}

void enemy::update()
{
}

void enemy::render()
{
}

/* ↓↓↓↓↓ 각 에너미 정보 초기화 ↓↓↓↓↓ */
void enemy::blueStoneInit(int x, int y, int frameX, int frameY)
{
	_blueStone.create = true;
	_blueStone.img = IMAGEMANAGER->findImage("BlueStone");
	_blueStone.img->setX(x);
	_blueStone.img->setY(y);
	_blueStone.img->setFrameX(frameX);
	_blueStone.img->setFrameY(frameY);
	_blueStone.atk = 20;
	_blueStone.atkTimer = GetTickCount64();
	_blueStone.atkDelay = 2000;
	_blueStone.maxHp = 200;
	_blueStone.hp = _blueStone.maxHp;
	_blueStone.move = false;
	_blueStone.moveTimer = GetTickCount64();
	_blueStone.damaged = false;
	_blueStone.damagedImg = IMAGEMANAGER->findImage("StoneDamaged");
	_blueStone.alpha = 0;
	_blueStone.hpBar = nullptr;
	_blueStone.actionBar = nullptr;
	_blueStone.gold = rand() % 200 + 300;

	_item->randomItemSet(&_blueStone.itemType, &_blueStone.itemName);
}

void enemy::darkBrownStoneInit(int x, int y, int frameX, int frameY)
{
	_darkBrownStone.create = true;
	_darkBrownStone.img = IMAGEMANAGER->findImage("DarkBrownStone");
	_darkBrownStone.img->setX(x);
	_darkBrownStone.img->setY(y);
	_darkBrownStone.img->setFrameX(frameX);
	_darkBrownStone.img->setFrameY(frameY);
	_darkBrownStone.atk = 30;
	_darkBrownStone.atkTimer = GetTickCount64();
	_darkBrownStone.atkDelay = 1000;
	_darkBrownStone.maxHp = 200;
	_darkBrownStone.hp = _darkBrownStone.maxHp;
	_darkBrownStone.move = false;
	_darkBrownStone.moveTimer = GetTickCount64();
	_darkBrownStone.damaged = false;
	_darkBrownStone.damagedImg = IMAGEMANAGER->findImage("StoneDamaged");
	_darkBrownStone.alpha = 0;
	_darkBrownStone.hpBar = nullptr;
	_darkBrownStone.actionBar = nullptr;
	_darkBrownStone.gold = rand() % 200 + 500;

	_item->randomItemSet(&_darkBrownStone.itemType, &_darkBrownStone.itemName);
}

void enemy::greenStoneInit(int x, int y, int frameX, int frameY)
{
	_greenStone.create = true;
	_greenStone.img = IMAGEMANAGER->findImage("GreenStone");
	_greenStone.img->setX(x);
	_greenStone.img->setY(y);
	_greenStone.img->setFrameX(frameX);
	_greenStone.img->setFrameY(frameY);
	_greenStone.atk = 200;
	_greenStone.atkTimer = GetTickCount64();
	_greenStone.atkDelay = 5000;
	_greenStone.maxHp = 500;
	_greenStone.hp = _greenStone.maxHp;
	_greenStone.move = false;
	_greenStone.moveTimer = GetTickCount64();
	_greenStone.damaged = false;
	_greenStone.damagedImg = IMAGEMANAGER->findImage("StoneDamaged");
	_greenStone.alpha = 0;
	_greenStone.hpBar = nullptr;
	_greenStone.actionBar = nullptr;
	_greenStone.gold = rand() % 200 + 1000;

	_item->randomItemSet(&_greenStone.itemType, &_greenStone.itemName);
}

void enemy::orangeStoneInit(int x, int y, int frameX, int frameY)
{
	_orangeStone.create = true;
	_orangeStone.img = IMAGEMANAGER->findImage("OrangeStone");
	_orangeStone.img->setX(x);
	_orangeStone.img->setY(y);
	_orangeStone.img->setFrameX(frameX);
	_orangeStone.img->setFrameY(frameY);
	_orangeStone.atk = 30;
	_orangeStone.atkTimer = GetTickCount64();
	_orangeStone.atkDelay = 700;
	_orangeStone.maxHp = 1000;
	_orangeStone.hp = _orangeStone.maxHp;
	_orangeStone.move = false;
	_orangeStone.moveTimer = GetTickCount64();
	_orangeStone.damaged = false;
	_orangeStone.damagedImg = IMAGEMANAGER->findImage("StoneDamaged");
	_orangeStone.alpha = 0;
	_orangeStone.hpBar = nullptr;
	_orangeStone.actionBar = nullptr;
	_orangeStone.gold = rand() % 200 + 1500;

	_item->randomItemSet(&_orangeStone.itemType, &_orangeStone.itemName);
}

void enemy::fullColorStoneInit(int x, int y, int frameX, int frameY)
{
	_fullColorStone.create = true;
	_fullColorStone.img = IMAGEMANAGER->findImage("FullColorStone");
	_fullColorStone.img->setX(x);
	_fullColorStone.img->setY(y);
	_fullColorStone.img->setFrameX(frameX);
	_fullColorStone.img->setFrameY(frameY);
	_fullColorStone.atk = 100;
	_fullColorStone.atkTimer = GetTickCount64();
	_fullColorStone.atkDelay = 700;
	_fullColorStone.maxHp = 2000;
	_fullColorStone.hp = _fullColorStone.maxHp;
	_fullColorStone.move = false;
	_fullColorStone.moveTimer = GetTickCount64();
	_fullColorStone.damaged = false;
	_fullColorStone.damagedImg = IMAGEMANAGER->findImage("StoneDamaged");
	_fullColorStone.alpha = 0;
	_fullColorStone.hpBar = nullptr;
	_fullColorStone.actionBar = nullptr;
	_fullColorStone.gold = rand() % 200 + 10000;

	_item->randomItemSet(&_fullColorStone.itemType, &_fullColorStone.itemName);
}
/* ↑↑↑↑↑ 각 에너미 정보 초기화 ↑↑↑↑↑ */

// 체력바 초기화
void enemy::hpBarInit(tagStone* target, string keyNameFront, string keyNameBack, int x, int y)
{
	target->hpBar = new progressBar;
	target->hpBar->init(keyNameFront, "Img/UI/hpFront", x + 9, y + 3, 182, 14, keyNameBack, "Img/UI/hpBack", x, y, 200, 20);
	target->hpBar->setGauge(target->hp, target->maxHp);
}

// 액션바 초기화
void enemy::actionBarInit(tagStone* target, string keyNameFront, string keyNameBack, int x, int y)
{
	target->actionBar = new progressBar;
	target->actionBar->init(keyNameFront, "Img/UI/actionFront", x + 9, y + 3, 132, 14, keyNameBack, "Img/UI/actionBack", x, y, 150, 20);
	target->actionBar->setGauge(GetTickCount64() - target->atkTimer, target->atkDelay);
}

// 에너미 행동
bool enemy::stoneUpdate(tagStone* target)
{
	// 에너미 좌우 이동 모션
	if (GetTickCount64() - target->moveTimer >= 300)
	{
		if (target->move)
		{
			target->moveTimer = GetTickCount64();
			target->move = false;
			target->img->setX(target->img->getX() + 5);
		}
		else
		{
			target->moveTimer = GetTickCount64();
			target->move = true;
			target->img->setX(target->img->getX() - 5);
		}
	}

	// 에너미 액션바 가득 찼을때 공격하도록 true 리턴
	if (GetTickCount64() - target->atkTimer >= target->atkDelay)
	{
		target->atkTimer = GetTickCount64();
		target->img->setFrameX(1);
		return true;
	}
	else if (GetTickCount64() - target->atkTimer >= 500)
		target->img->setFrameX(0);

	return false;
}

// 에너미 피격
void enemy::damagedUpdate(tagStone* target)
{
	// 데미지를 받고 있는 중일때 빨간 이미지 알파값 조절
	if (target->damaged)
	{
		static int count = 0;
		count++;

		target->alpha += 15;

		if (count == 68)
		{
			target->damaged = false;
			target->alpha = 0;
			count = 0;
		}
	}
}

// 에너미 랜더
void enemy::stoneRender(tagStone* target)
{
	// 에너미 프레임 이미지
	target->img->frameRender(getMemDC(), target->img->getX(), target->img->getY());

	// 에너미 피격 이미지
	if (target->damaged)
	{
		target->damagedImg->alphaRender(getMemDC(), target->img->getX(), target->img->getY(), target->alpha);
	}

	// 체력바
	target->hpBar->setGauge(target->hp, target->maxHp);
	target->hpBar->render();

	// 액션바
	target->actionBar->setGauge(GetTickCount64() - target->atkTimer, target->atkDelay);
	target->actionBar->render();
}
