#pragma once
#include "gameNode.h"
#include "Item.h"
#include "inventory.h"

#define LIST_SIZE 25

struct tagList
{
	RECT rc;
	tagItemData data;
};

class shop : public gameNode
{
private:
	// 필요 클래스 포인터0
	Item*		_item;
	inventory*	_inven;

	// 상점 리스트 출력할 보드의 사이즈
	RECT		_boardSize;

	// 상품 리스트
	tagList		_listRc[LIST_SIZE];

	// UI
	image*		_buyCost;
	image*		_sellCost;
	image*		_gold;
	bool		_buySelect;
	bool		_sellSelect;
	int			_selectCost;

public:
	HRESULT init(int x, int y, int width, int height, inventory* inven);
	void release();
	void update();
	void render();

	// 아이템 정보를 리스트에 입력해줌
	void itemList(tagType type);

	// 상품 리스트 선택 확인
	tagList selectList(POINT pt);

	// 상품 구매
	void setBuySelect(bool buySelect) { _buySelect = buySelect; }

	// 숫자 출력
	void printNumber(int num, int x, int y);

	shop() {}
	~shop() {}
};