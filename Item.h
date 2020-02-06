#pragma once
#include "gameNode.h"

enum tagType
{
	WEAPON,
	ARMOR,
	HELMET,
	NECKLACE,
	SHIELD,
	BELT,
	SHOES,
	POTION,
	TYPE_END
};

struct tagItemData
{
	tagType type;
	string name;
	int value;
	int cost;
};

class Item : public gameNode
{
private:
	// ������ ������ ������
	map<string, tagItemData> _weapon;
	map<string, tagItemData> _armor;
	map<string, tagItemData> _helmet;
	map<string, tagItemData> _necklace;
	map<string, tagItemData> _shield;
	map<string, tagItemData> _belt;
	map<string, tagItemData> _shoes;
	map<string, tagItemData> _potion;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	// ������ ������ �ޱ�
	tagItemData getData(tagType type, string name);
	map<string, tagItemData>* getDataMap(tagType type);

	// ������ ������ ����
	void setData(tagType type, string name, int value, int cost);

	void randomItemSet(tagType* type, string* name);

	Item() {}
	~Item() {}
};

