#include "stdafx.h"
#include "player.h"

HRESULT player::init()
{
	// �÷��̾� ���� ���
	_img = IMAGEMANAGER->findImage("Player");
	_damagedImg = IMAGEMANAGER->findImage("PlayerDamaged");
	_damagedAlpha = 0;
	_img->setFrameY(2);
	_count = 0;
	_frameTurn = true;

	// �������ͽ� �ʱ�ȭ
	_hp = 100;
	_maxHp = 100;
	_atk = 10;
	_def = 5;
	_damaged = false;
	_hpBar = nullptr;

	// ������
	_gold = 10000;

	// ��� �ʱ�ȭ
	_weapon = { WEAPON, "Empty", 0 };
	_helmet = { HELMET, "Empty", 0 };
	_armor = { ARMOR, "Empty", 0 };
	_necklace = { NECKLACE, "Empty", 0 };
	_shield = { SHIELD, "Empty", 0 };
	_belt = { BELT, "Empty", 0 };
	_shoes = { SHOES, "Empty", 0 };

	// ������
	_item = new Item;
	_item->init();

	// �ɼ�
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
	if (_damaged)
	{
		static int count = 0;
		count++;

		_damagedAlpha += 15;

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
	// �÷��̾� ĳ���� ����
	_img->frameRender(getMemDC(), _img->getX(), _img->getY());

	if (_damaged)
		_damagedImg->alphaFrameRender(getMemDC(), _img->getX(), _img->getY(), _img->getFrameX(), _img->getFrameY(), _damagedAlpha);
}

void player::hpBarInit(int x, int y)
{
	// ü�¹�
	_hpBar = new progressBar;
	_hpBar->init("PlayerHp", "Img/UI/hpFront", x + 9, y + 3, 182, 14, "PlayerHpBack", "Img/UI/hpBack", x, y, 200, 20);
	_hpBar->setGauge(_hp, getMaxHp());
}

void player::playerMove(tagDirection dir)
{
	// ���⿡ ���� �÷��̾� �̵�
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
	// �÷��̾� ������ ����
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
	// ������ ������ ����
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
	tagItemData buf;

	buf.name = "Empty";
	buf.value = {};
	buf.cost = 0;

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
	_hpBar->setGauge(_hp, getMaxHp());

	_hpBar->render();
}

void player::save()
{
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
	char cBuf[100];
	char cBuf3[100];
	char cBuf4[100];
	ZeroMemory(cBuf, 100);
	ZeroMemory(cBuf3, 100);
	ZeroMemory(cBuf4, 100);
	itoa(item.type, cBuf, 10);
	itoa(item.cost, cBuf3, 10);
	itoa(item.value, cBuf4, 10);
	INIDATA->addData(cBuf, "Name", item.name.c_str());
	INIDATA->addData(cBuf, "Cost", cBuf3);
	INIDATA->addData(cBuf, "Value", cBuf4);

	INIDATA->saveINI("PlayerData");
}

void player::load()
{
	loadEquip(&_weapon);
	loadEquip(&_helmet);
	loadEquip(&_armor);
	loadEquip(&_necklace);
	loadEquip(&_shield);
	loadEquip(&_belt);
	loadEquip(&_shoes);

	_maxHp = INIDATA->loadDataInteger("PlayerData", "Status", "MaxHp");
	_hp = getMaxHp();
	_atk = INIDATA->loadDataInteger("PlayerData", "Status", "Atk");
	_def = INIDATA->loadDataInteger("PlayerData", "Status", "Def");
	_gold = INIDATA->loadDataInteger("PlayerData", "Status", "Gold");
}

void player::loadEquip(tagItemData* item)
{
	char cBuf[100];
	ZeroMemory(cBuf, 100);
	itoa(item->type, cBuf, 10);
	char cBuf2[100] = {};
	ZeroMemory(cBuf2, 100);
	wsprintf(cBuf2, "%s", INIDATA->loadDataString("PlayerData", cBuf, "Name"));
	item->name = cBuf2;
	item->cost = INIDATA->loadDataInteger("PlayerData", cBuf, "Cost");
	item->value = INIDATA->loadDataInteger("PlayerData", cBuf, "Value");
}