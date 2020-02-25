#include "stdafx.h"
#include "shop.h"

HRESULT shop::init(int x, int y, int width, int height, inventory* inven)
{
	// 아이템
	_item = new Item;
	_item->init();

	// 인벤토리 포인터 받기
	_inven = inven;

	// UI 등록
	_buyCost = IMAGEMANAGER->findImage("Buy");
	_sellCost = IMAGEMANAGER->findImage("Sell");
	_gold = IMAGEMANAGER->findImage("Gold");

	// 리스트 출력 보드 사이즈
	_boardSize = RectMake(x, y, width, height);

	// 리스트 목록 초기화
	for (int i = 0; i < LIST_SIZE; i++)
	{
		_listRc[i].rc = RectMake(_boardSize.left + 25 + 55 * (i % 5), _boardSize.top + 55 * (i / 5) + 20, 50, 50);
		_listRc[i].data = {};
		_listRc[i].data.name = "Empty";
	}

	// 변수 초기화
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
	// 인벤토리에서 선택한 상품의 가격을 받아온다
	_selectCost = _inven->getSelect().value.cost;
}

void shop::render()
{
	// 리스트 등록
	itemList(ARMOR);

	// 상품 선택시 선택한 상품의 구매가 출력
	if (_buySelect)
	{
		_buyCost->render(getMemDC(), _boardSize.left + 10, (_boardSize.bottom + _boardSize.top) / 2 - 35);
		_gold->render(getMemDC(), _boardSize.left + 10 + _buyCost->getWidth(), (_boardSize.bottom + _boardSize.top) / 2 - 40);
		printNumber(_selectCost, _boardSize.left + 10 + _buyCost->getWidth() + 40, (_boardSize.bottom + _boardSize.top) / 2 - 33);
	}
	// 인벤토리 아이템 선택시 선택한 상품의 판매가 출력
	else if (_sellSelect)
	{
		_sellCost->render(getMemDC(), _boardSize.left + 10, (_boardSize.bottom + _boardSize.top) / 2 - 35);
		_gold->render(getMemDC(), _boardSize.left + 10 + _sellCost->getWidth(), (_boardSize.bottom + _boardSize.top) / 2 - 40);
		printNumber(_selectCost / 2, _boardSize.left + 10 + _sellCost->getWidth() + 40, (_boardSize.bottom + _boardSize.top) / 2 - 33);
	}
}

void shop::itemList(tagType type)
{
	// Item 클래스에 등록된 아이템을 리스트에 등록한다
	int count = 0;

	// 무기
	for (map<string, tagItemData>::iterator iter = _item->getDataMap(WEAPON)->begin(); iter != _item->getDataMap(WEAPON)->end(); iter++)
	{
		IMAGEMANAGER->render(iter->second.name, getMemDC(), _listRc[count].rc.left, _listRc[count].rc.top);
		_listRc[count].data = iter->second;
		count++;
	}

	// 헬멧
	for (map<string, tagItemData>::iterator iter = _item->getDataMap(HELMET)->begin(); iter != _item->getDataMap(HELMET)->end(); iter++)
	{
		IMAGEMANAGER->render(iter->second.name, getMemDC(), _listRc[count].rc.left, _listRc[count].rc.top);
		_listRc[count].data = iter->second;
		count++;
	}

	// 갑옷
	for (map<string, tagItemData>::iterator iter = _item->getDataMap(ARMOR)->begin(); iter != _item->getDataMap(ARMOR)->end(); iter++)
	{
		IMAGEMANAGER->render(iter->second.name, getMemDC(), _listRc[count].rc.left, _listRc[count].rc.top);
		_listRc[count].data = iter->second;
		count++;
	}

	// 목걸이
	for (map<string, tagItemData>::iterator iter = _item->getDataMap(NECKLACE)->begin(); iter != _item->getDataMap(NECKLACE)->end(); iter++)
	{
		IMAGEMANAGER->render(iter->second.name, getMemDC(), _listRc[count].rc.left, _listRc[count].rc.top);
		_listRc[count].data = iter->second;
		count++;
	}

	// 방패
	for (map<string, tagItemData>::iterator iter = _item->getDataMap(SHIELD)->begin(); iter != _item->getDataMap(SHIELD)->end(); iter++)
	{
		IMAGEMANAGER->render(iter->second.name, getMemDC(), _listRc[count].rc.left, _listRc[count].rc.top);
		_listRc[count].data = iter->second;
		count++;
	}

	// 벨트
	for (map<string, tagItemData>::iterator iter = _item->getDataMap(BELT)->begin(); iter != _item->getDataMap(BELT)->end(); iter++)
	{
		IMAGEMANAGER->render(iter->second.name, getMemDC(), _listRc[count].rc.left, _listRc[count].rc.top);
		_listRc[count].data = iter->second;
		count++;
	}

	// 신발
	for (map<string, tagItemData>::iterator iter = _item->getDataMap(SHOES)->begin(); iter != _item->getDataMap(SHOES)->end(); iter++)
	{
		IMAGEMANAGER->render(iter->second.name, getMemDC(), _listRc[count].rc.left, _listRc[count].rc.top);
		_listRc[count].data = iter->second;
		count++;
	}

	// 물약
	for (map<string, tagItemData>::iterator iter = _item->getDataMap(POTION)->begin(); iter != _item->getDataMap(POTION)->end(); iter++)
	{
		IMAGEMANAGER->render(iter->second.name, getMemDC(), _listRc[count].rc.left, _listRc[count].rc.top);
		_listRc[count].data = iter->second;
		count++;
	}
}

tagList shop::selectList(POINT pt)
{
	// 상품 리스트에서 아이템을 선택할 경우 구매 bool값을 true로 해준다.
	for (int i = 0; i < LIST_SIZE; i++)
	{
		if (PtInRect(&_listRc[i].rc, pt))
		{
			// 리스트가 비어있을 경우 Break
			if (_listRc[i].data.name == "Empty")
			{
				_buySelect = false;
				return {};
			}
			
			_sellSelect = false;
			_buySelect = true;
			return _listRc[i];
		}
	}

	// 인벤토리에서 아이템을 선택했을 경우 판매 bool값을 true로 해준다.
	if (_inven->getSelect().rc.left != 0 && _inven->getSelect().select)
		_sellSelect = true;
	else
		_sellSelect = false;

	_buySelect = false;
	return {};
}

void shop::printNumber(int num, int x, int y)
{
	// 구매 및 판매가를 출력하는 함수
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
