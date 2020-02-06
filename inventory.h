#pragma once
#include "gameNode.h"
#include "Item.h"
#include "player.h"

#define INVENTORY_SIZE 36
#define EQUIP_BLANK 10

struct tagSlot
{
	RECT rc;
	string name;
	tagType type;
	tagItemData value;
};

struct tagSelect
{
	RECT rc;
	bool select;
	string name;
	tagItemData value;
};

class inventory : public gameNode
{
private:
	// 장착 파츠 이미지
	image*			_helmet;
	image*			_weapon;
	image*			_armor;
	image*			_shield;
	image*			_belt;
	image*			_shoes;
	image*			_necklace;

	// 창 크기
	RECT			_boardSize;

	// 스테이터스
	image*			_status;
	image*			_hp;
	image*			_atk;
	image*			_def;

	// 소지금
	image*			_gold;

	// 인벤토리 슬롯
	tagSlot			_slot[INVENTORY_SIZE];
	bool			_full;
	ULONGLONG		_timer;

	// 아이템
	Item*			_item;

	// 선택한 아이템
	tagSelect		_select;

	// 포션 갯수
	int				_smallPotionAmount;
	int				_largePotionAmount;

	// 폰트
	HFONT			_font;
	HFONT			_oldFont;

public:
	HRESULT init(int x, int y, int width, int height);
	void release();
	void update();
	void render(player* _player);

	// 아이템 저장
	bool setItem(string name, tagType type);

	// 아이템 선택 및 사용
	bool selectItem(POINT pt);
	bool useItem(POINT pt);
	bool usePotion(string name);
	tagSelect* getSelectPtr() { return &_select; }

	// 포션갯수 받기
	int getSmallPotionAmount() { return _smallPotionAmount; }
	int getLargePotionAmount() { return _largePotionAmount; }

	// 선택된 아이템 받기
	tagSelect getSelect() { return _select; }

	// 장비창 출력
	void printEquipment(player* _player);

	// 숫자 출력
	void printNumber(int num, int x, int y, float scale = 1.0f);

	// 장비 해제
	bool equipOff(POINT pt, player* _player);

	// 저장 & 불러오기
	void save(string fileName);
	void load(string fileName);

	inventory() {}
	~inventory() {}
};