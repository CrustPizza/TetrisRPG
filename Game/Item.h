#pragma once
#include "gameNode.h"

// 아이템 타입
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

// 아이템 정보
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
	// 아이템 종류별 데이터
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

	// 아이템 데이터 받기
	tagItemData getData(tagType type, string name);
	map<string, tagItemData>* getDataMap(tagType type);

	// 아이템 데이터 저장
	void setData(tagType type, string name, int value, int cost);
	void randomItemSet(tagType* type, string* name);

	Item() {}
	~Item() {}
};

