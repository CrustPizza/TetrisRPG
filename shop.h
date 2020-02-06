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
	// �ʿ� Ŭ���� ������0
	Item*		_item;
	inventory*	_inven;

	// ���� ����Ʈ ����� ������ ������
	RECT		_boardSize;

	// ��ǰ ����Ʈ
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

	// ������ ������ ����Ʈ�� �Է�����
	void itemList(tagType type);

	// ��ǰ ����Ʈ ���� Ȯ��
	tagList selectList(POINT pt);

	// ��ǰ ����
	void setBuySelect(bool buySelect) { _buySelect = buySelect; }

	// ���� ���
	void printNumber(int num, int x, int y);

	shop() {}
	~shop() {}
};