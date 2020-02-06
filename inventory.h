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
	// ���� ���� �̹���
	image*			_helmet;
	image*			_weapon;
	image*			_armor;
	image*			_shield;
	image*			_belt;
	image*			_shoes;
	image*			_necklace;

	// â ũ��
	RECT			_boardSize;

	// �������ͽ�
	image*			_status;
	image*			_hp;
	image*			_atk;
	image*			_def;

	// ������
	image*			_gold;

	// �κ��丮 ����
	tagSlot			_slot[INVENTORY_SIZE];
	bool			_full;
	ULONGLONG		_timer;

	// ������
	Item*			_item;

	// ������ ������
	tagSelect		_select;

	// ���� ����
	int				_smallPotionAmount;
	int				_largePotionAmount;

	// ��Ʈ
	HFONT			_font;
	HFONT			_oldFont;

public:
	HRESULT init(int x, int y, int width, int height);
	void release();
	void update();
	void render(player* _player);

	// ������ ����
	bool setItem(string name, tagType type);

	// ������ ���� �� ���
	bool selectItem(POINT pt);
	bool useItem(POINT pt);
	bool usePotion(string name);
	tagSelect* getSelectPtr() { return &_select; }

	// ���ǰ��� �ޱ�
	int getSmallPotionAmount() { return _smallPotionAmount; }
	int getLargePotionAmount() { return _largePotionAmount; }

	// ���õ� ������ �ޱ�
	tagSelect getSelect() { return _select; }

	// ���â ���
	void printEquipment(player* _player);

	// ���� ���
	void printNumber(int num, int x, int y, float scale = 1.0f);

	// ��� ����
	bool equipOff(POINT pt, player* _player);

	// ���� & �ҷ�����
	void save(string fileName);
	void load(string fileName);

	inventory() {}
	~inventory() {}
};