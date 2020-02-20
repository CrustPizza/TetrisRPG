#include "stdafx.h"
#include "player.h"

HRESULT player::init()
{
	// 플레이어 정보 등록
	_img = IMAGEMANAGER->findImage("Player");
	_damagedImg = IMAGEMANAGER->findImage("PlayerDamaged");
	_damagedAlpha = 0;
	_img->setFrameY(2);
	_count = 0;
	_frameTurn = true;

	// 스테이터스 초기화
	_hp = 100;
	_maxHp = 100;
	_atk = 10;
	_def = 5;
	_damaged = false;
	_hpBar = nullptr;

	// 소지금
	_gold = 10000;

	// 장비 초기화
	_weapon = { WEAPON, "Empty", 0 };
	_helmet = { HELMET, "Empty", 0 };
	_armor = { ARMOR, "Empty", 0 };
	_necklace = { NECKLACE, "Empty", 0 };
	_shield = { SHIELD, "Empty", 0 };
	_belt = { BELT, "Empty", 0 };
	_shoes = { SHOES, "Empty", 0 };

	// 아이템
	_item = new Item;
	_item->init();

	// 옵션
	_option = new option;
	_option->init();

	return S_OK;
}

void player::release()
{
	_item->release();
	SAFE_DELETE(_item);

	if (_hpBar != nullptr)
	{
		_hpBar->release();
		SAFE_DELETE(_hpBar);
	}

	_option->release();
	SAFE_DELETE(_option);
}

void player::update()
{
	// 피격시
	if (_damaged)
	{
		// 피격 이미지 알파값을 조절
		static int count = 0;
		count++;

		_damagedAlpha += 15;

		// 일정 카운트가 되면 종료
		if (count == 68)
		{
			_damaged = false;
			_damagedAlpha = 0;
			count = 0;
		}
	}
}

void player::render()
{
	// 플레이어 캐릭터 렌더
	_img->frameRender(getMemDC(), _img->getX(), _img->getY());

	// 피격시 출력
	if (_damaged)
		_damagedImg->alphaFrameRender(getMemDC(), _img->getX(), _img->getY(), _img->getFrameX(), _img->getFrameY(), _damagedAlpha);
}

void player::hpBarInit(int x, int y)
{
	// 체력바
	_hpBar = new progressBar;
	_hpBar->init("PlayerHp", "Img/UI/hpFront", x + 9, y + 3, 182, 14, "PlayerHpBack", "Img/UI/hpBack", x, y, 200, 20);
	_hpBar->setGauge(_hp, getMaxHp());
}

void player::playerMove(tagDirection dir)
{
	// 방향에 따른 플레이어 이동
	switch (dir)
	{
	case LEFT:
		if (KEYMANAGER->isStayKeyDown(_option->getLeft()))
		{
			_img->setFrameY(3);

			_img->setX(_img->getX() - 3);
		}
		break;
	case RIGHT:
		if (KEYMANAGER->isStayKeyDown(_option->getRight()))
		{
			_img->setFrameY(1);

			_img->setX(_img->getX() + 3);
		}
		break;
	case UP:
		if (KEYMANAGER->isStayKeyDown(_option->getUp()))
		{
			_img->setFrameY(0);

			_img->setY(_img->getY() - 3);
		}
		break;
	case DOWN:
		if (KEYMANAGER->isStayKeyDown(_option->getDown()))
		{
			_img->setFrameY(2);

			_img->setY(_img->getY() + 3);
		}
		break;
	}
}

void player::playerIdle()
{
	// 플레이어 프레임 조절
	_count++;

	if (_count % 15 == 0)
	{
		if (_img->getFrameX() == 1)
		{
			if (_frameTurn)
				_img->setFrameX(2);
			else
				_img->setFrameX(0);

			_frameTurn = !_frameTurn;
		}
		else
			_img->setFrameX(1);
	}
}

bool player::playerEvasion()
{
	// 회피 이미지 설정
	if (GetTickCount64() - _timer >= 160)
	{
		_img->setFrameX(_img->getFrameX() + 1);
		_img->setX(_img->getX() - 10);
		_timer = GetTickCount64();

		if (_img->getFrameX() == 12)
		{
			_img->setFrameY(1);
			_img->setFrameX(0);
			_img->setX(_img->getX() + 30);
			return false;
		}
	}

	return true;
}

bool player::playerAttack()
{
	// 공격 이미지 설정
	if (GetTickCount64() - _timer >= 40)
	{
		_img->setFrameX(_img->getFrameX() + 1);
		_img->setX(_img->getX() + 10);
		_timer = GetTickCount64();

		if (_img->getFrameX() == 5)
		{
			_img->setFrameY(1);
			_img->setFrameX(0);
			_img->setX(_img->getX() - 60);
			return false;
		}
	}
	return true;
}

tagItemData player::equipItem(tagType type, string name)
{
	// 종류별 아이템 장착
	tagItemData buf;

	switch (type)
	{
	case WEAPON:
		buf = _weapon;
		_weapon = _item->getData(type, name);
		break;
	case ARMOR:
		buf = _armor;
		_armor = _item->getData(type, name);
		break;
	case HELMET:
		buf = _helmet;
		_helmet = _item->getData(type, name);
		break;
	case NECKLACE:
		buf = _necklace;
		_necklace = _item->getData(type, name);
		break;
	case SHIELD:
		buf = _shield;
		_shield = _item->getData(type, name);
		break;
	case BELT:
		buf = _belt;
		_belt = _item->getData(type, name);
		break;
	case SHOES:
		buf = _shoes;
		_shoes = _item->getData(type, name);
		break;
	case POTION:
		break;
	}

	return buf;
}

void player::equitOffItem(tagType type)
{
	// 장착 아이템 변수 초기화시킬 버퍼
	tagItemData buf;

	buf.name = "Empty";
	buf.value = {};
	buf.cost = 0;

	// 타입에 맞게 초기화
	switch (type)
	{
	case WEAPON:
		buf.type = _weapon.type;
		_weapon = buf;
		break;
	case ARMOR:
		buf.type = _armor.type;
		_armor = buf;
		break;
	case HELMET:
		buf.type = _helmet.type;
		_helmet = buf;
		break;
	case NECKLACE:
		buf.type = _necklace.type;
		_necklace = buf;
		break;
	case SHIELD:
		buf.type = _shield.type;
		_shield = buf;
		break;
	case BELT:
		buf.type = _belt.type;
		_belt = buf;
		break;
	case SHOES:
		buf.type = _shoes.type;
		_shoes = buf;
		break;
	case POTION:
		break;
	}
}

void player::hpBarRender()
{
	// Hp바
	_hpBar->setGauge(_hp, getMaxHp());
	_hpBar->render();
}

void player::save()
{
	// 캐릭터의 스테이터스를 INI형식의 데이터로 저장시킨다.
	
	char cBuf[100];
	ZeroMemory(cBuf, 100);
	itoa(_maxHp, cBuf, 10);
	INIDATA->addData("Status", "MaxHp", cBuf);

	char cBuf2[100];
	ZeroMemory(cBuf2, 100);
	itoa(_atk, cBuf2, 10);
	INIDATA->addData("Status", "Atk", cBuf2);

	char cBuf3[100];
	ZeroMemory(cBuf3, 100);
	itoa(_def, cBuf3, 10);
	INIDATA->addData("Status", "Def", cBuf3);

	char cBuf4[100];
	ZeroMemory(cBuf4, 100);
	itoa(_gold, cBuf4, 10);
	INIDATA->addData("Status", "Gold", cBuf4);

	// 장착 아이템도 INI데이터로 저장
	saveEquip(_weapon);
	saveEquip(_helmet);
	saveEquip(_armor);
	saveEquip(_necklace);
	saveEquip(_shield);
	saveEquip(_belt);
	saveEquip(_shoes);

	INIDATA->saveINI("PlayerData");
}

void player::saveEquip(tagItemData item)
{
	// 버퍼 초기화
	char cBuf[100];
	char cBuf2[100];
	char cBuf3[100];
	ZeroMemory(cBuf, 100);
	ZeroMemory(cBuf2, 100);
	ZeroMemory(cBuf3, 100);
	
	// 아이템 정보들 버퍼에 저장
	itoa(item.type, cBuf, 10);
	itoa(item.cost, cBuf2, 10);
	itoa(item.value, cBuf3, 10);
	
	// INI데이터로 아이템 정보 저장
	INIDATA->addData(cBuf, "Name", item.name.c_str());
	INIDATA->addData(cBuf, "Cost", cBuf2);
	INIDATA->addData(cBuf, "Value", cBuf3);

	INIDATA->saveINI("PlayerData");
}

void player::load()
{
	// 장착할 아이템 불러오기
	loadEquip(&_weapon);
	loadEquip(&_helmet);
	loadEquip(&_armor);
	loadEquip(&_necklace);
	loadEquip(&_shield);
	loadEquip(&_belt);
	loadEquip(&_shoes);

	// 각 스테이터스 불러와서 입력
	_maxHp = INIDATA->loadDataInteger("PlayerData", "Status", "MaxHp");
	_hp = getMaxHp();
	_atk = INIDATA->loadDataInteger("PlayerData", "Status", "Atk");
	_def = INIDATA->loadDataInteger("PlayerData", "Status", "Def");
	_gold = INIDATA->loadDataInteger("PlayerData", "Status", "Gold");
}

void player::loadEquip(tagItemData* item)
{
	// 버퍼 초기화
	char cBuf[100];
	char cBuf2[100] = {};
	ZeroMemory(cBuf, 100);
	ZeroMemory(cBuf2, 100);
	
	// 타입에 맞는 아이템 읽어오기
	itoa(item->type, cBuf, 10);
	wsprintf(cBuf2, "%s", INIDATA->loadDataString("PlayerData", cBuf, "Name"));
	
	// 버퍼에 저장된 아이템 입력
	item->name = cBuf2;
	item->cost = INIDATA->loadDataInteger("PlayerData", cBuf, "Cost");
	item->value = INIDATA->loadDataInteger("PlayerData", cBuf, "Value");
}
