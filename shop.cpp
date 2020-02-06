#include "stdafx.h"
#include "shop.h"

HRESULT shop::init(int x, int y, int width, int height, inventory* inven)
{
	// ������
	_item = new Item;
	_item->init();

	// �κ��丮 ������ �ޱ�
	_inven = inven;

	// UI ���
	_buyCost = IMAGEMANAGER->findImage("Buy");
	_sellCost = IMAGEMANAGER->findImage("Sell");
	_gold = IMAGEMANAGER->findImage("Gold");

	// ����Ʈ ��� ���� ������
	_boardSize = RectMake(x, y, width, height);

	// ����Ʈ ��� �ʱ�ȭ
	for (int i = 0; i < LIST_SIZE; i++)
	{
		_listRc[i].rc = RectMake(_boardSize.left + 25 + 55 * (i % 5), _boardSize.top + 55 * (i / 5) + 20, 50, 50);
		_listRc[i].data = {};
		_listRc[i].data.name = "Empty";
	}

	// ���� �ʱ�ȭ
	_buySelect = false;
	_sellSelect = false;
	_selectCost = 0;

	return S_OK;
}

void shop::release()
{
	_item->release();
	SAFE_DELETE(_item);
}

void shop::update()
{
	// �κ��丮���� ������ ��ǰ�� ������ �޾ƿ´�
	_selectCost = _inven->getSelect().value.cost;
}

void shop::render()
{
	// ����Ʈ ���
	itemList(ARMOR);

	// ��ǰ ���ý�
	if (_buySelect)
	{
		_buyCost->render(getMemDC(), _boardSize.left + 10, (_boardSize.bottom + _boardSize.top) / 2 - 35);
		_gold->render(getMemDC(), _boardSize.left + 10 + _buyCost->getWidth(), (_boardSize.bottom + _boardSize.top) / 2 - 40);
		printNumber(_selectCost, _boardSize.left + 10 + _buyCost->getWidth() + 40, (_boardSize.bottom + _boardSize.top) / 2 - 33);
	}
	// �κ��丮 ������ ���ý�
	else if (_sellSelect)
	{
		_sellCost->render(getMemDC(), _boardSize.left + 10, (_boardSize.bottom + _boardSize.top) / 2 - 35);
		_gold->render(getMemDC(), _boardSize.left + 10 + _sellCost->getWidth(), (_boardSize.bottom + _boardSize.top) / 2 - 40);
		printNumber(_selectCost / 2, _boardSize.left + 10 + _sellCost->getWidth() + 40, (_boardSize.bottom + _boardSize.top) / 2 - 33);
	}
}

void shop::itemList(tagType type)
{
	// Item Ŭ������ ��ϵ� �������� ����Ʈ�� ����Ѵ�
	int count = 0;

	for (map<string, tagItemData>::iterator iter = _item->getDataMap(WEAPON)->begin(); iter != _item->getDataMap(WEAPON)->end(); iter++)
	{
		IMAGEMANAGER->render(iter->second.name, getMemDC(), _listRc[count].rc.left, _listRc[count].rc.top);
		_listRc[count].data = iter->second;
		count++;
	}

	for (map<string, tagItemData>::iterator iter = _item->getDataMap(HELMET)->begin(); iter != _item->getDataMap(HELMET)->end(); iter++)
	{
		IMAGEMANAGER->render(iter->second.name, getMemDC(), _listRc[count].rc.left, _listRc[count].rc.top);
		_listRc[count].data = iter->second;
		count++;
	}

	for (map<string, tagItemData>::iterator iter = _item->getDataMap(ARMOR)->begin(); iter != _item->getDataMap(ARMOR)->end(); iter++)
	{
		IMAGEMANAGER->render(iter->second.name, getMemDC(), _listRc[count].rc.left, _listRc[count].rc.top);
		_listRc[count].data = iter->second;
		count++;
	}

	for (map<string, tagItemData>::iterator iter = _item->getDataMap(NECKLACE)->begin(); iter != _item->getDataMap(NECKLACE)->end(); iter++)
	{
		IMAGEMANAGER->render(iter->second.name, getMemDC(), _listRc[count].rc.left, _listRc[count].rc.top);
		_listRc[count].data = iter->second;
		count++;
	}

	for (map<string, tagItemData>::iterator iter = _item->getDataMap(SHIELD)->begin(); iter != _item->getDataMap(SHIELD)->end(); iter++)
	{
		IMAGEMANAGER->render(iter->second.name, getMemDC(), _listRc[count].rc.left, _listRc[count].rc.top);
		_listRc[count].data = iter->second;
		count++;
	}

	for (map<string, tagItemData>::iterator iter = _item->getDataMap(BELT)->begin(); iter != _item->getDataMap(BELT)->end(); iter++)
	{
		IMAGEMANAGER->render(iter->second.name, getMemDC(), _listRc[count].rc.left, _listRc[count].rc.top);
		_listRc[count].data = iter->second;
		count++;
	}

	for (map<string, tagItemData>::iterator iter = _item->getDataMap(SHOES)->begin(); iter != _item->getDataMap(SHOES)->end(); iter++)
	{
		IMAGEMANAGER->render(iter->second.name, getMemDC(), _listRc[count].rc.left, _listRc[count].rc.top);
		_listRc[count].data = iter->second;
		count++;
	}

	for (map<string, tagItemData>::iterator iter = _item->getDataMap(POTION)->begin(); iter != _item->getDataMap(POTION)->end(); iter++)
	{
		IMAGEMANAGER->render(iter->second.name, getMemDC(), _listRc[count].rc.left, _listRc[count].rc.top);
		_listRc[count].data = iter->second;
		count++;
	}
}

tagList shop::selectList(POINT pt)
{
	// ��ǰ ����Ʈ���� �������� ������ ��� ���� bool���� true�� ���ش�.
	for (int i = 0; i < LIST_SIZE; i++)
	{
		if (PtInRect(&_listRc[i].rc, pt))
		{
			if (_listRc[i].data.name == "Empty")
				break;
			
			_sellSelect = false;
			_buySelect = true;
			return _listRc[i];
		}
	}

	// �κ��丮���� �������� �������� ��� �Ǹ� bool���� true�� ���ش�.
	if (_inven->getSelect().rc.left != 0 && _inven->getSelect().select)
		_sellSelect = true;
	else
		_sellSelect = false;

	_buySelect = false;
	return {};
}

void shop::printNumber(int num, int x, int y)
{
	// ���� �� �ǸŰ��� ����Ѵ�
	int digit = 1;

	while (num / digit >= 10)
		digit *= 10;

	for (int i = 0; ; i++, digit /= 10)
	{
		if (digit != 1)
			IMAGEMANAGER->frameRender("Number", getMemDC(), x + 12 * i, y, (num / digit) % 10, 0);
		else
		{
			IMAGEMANAGER->frameRender("Number", getMemDC(), x + 12 * i, y, num % 10, 0);
			break;
		}
	}
}