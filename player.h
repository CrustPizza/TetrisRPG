#pragma once
#include "gameNode.h"
#include "skill.h"
#include "Item.h"
#include "progressBar.h"
#include "option.h"

class player : public gameNode
{
private:
	// ������ ����
	Item*		_item;

	// ĳ���� �̹���
	image*		_img;
	int			_count;
	bool		_frameTurn;
	ULONGLONG	_timer;
	image*		_damagedImg;
	BYTE		_damagedAlpha;

	// ü�¹�
	progressBar* _hpBar;

	// ������
	unsigned int _gold;

	// �������ͽ�
	int			_hp;
	int			_maxHp;
	int			_atk;
	int			_def;
	bool		_damaged;

	// ���
	tagItemData	_weapon;
	tagItemData	_helmet;
	tagItemData	_armor;
	tagItemData	_necklace;
	tagItemData	_shield;
	tagItemData	_belt;
	tagItemData	_shoes;

	// �ɼ�
	option* _option;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	// ü�¹� �ʱ�ȭ
	void hpBarInit(int x, int y);

	// �̹��� �ޱ�
	image* getImage() { return _img; }

	// �÷��̾� �̵�
	void playerMove(tagDirection dir);

	// �÷��̾� �Ϲ�
	void playerIdle();

	// �÷��̾� ȸ��
	bool playerEvasion();

	// �÷��̾� ����
	bool playerAttack();

	// ������ ���� �� ����
	tagItemData equipItem(tagType type, string name);
	void equitOffItem(tagType type);

	// ü�¹� ����
	void hpBarRender();

	// Ÿ�̸�
	void setTimer(ULONGLONG timer) { _timer = timer; }

	// �������ͽ� �ְ� �ޱ�
	int getHp() { return _hp; }
	int getMaxHp() { return _maxHp + _belt.value; }
	int getAtk() { return _atk + _weapon.value + _necklace.value; }
	int getDef() { return _def + _armor.value + _helmet.value + _shield.value + _shoes.value; }
	void setHp(int hp) { _hp = hp; if (_hp > getMaxHp()) _hp = getMaxHp(); }
	void setDamaged(bool damaged) { _damaged = damaged; }

	// ������ �ְ� �ޱ�
	int getGold() { return _gold; }
	void setGold(int gold) { _gold = gold; }

	// ��� �ޱ�
	tagItemData getWeapon() { return _weapon; }
	tagItemData getHelmet() { return _helmet; }
	tagItemData getArmor() { return _armor; }
	tagItemData getNecklace() { return _necklace; }
	tagItemData getShield() { return _shield; }
	tagItemData getBelt() { return _belt; }
	tagItemData getShoes() { return _shoes; }

	// ���� & �ҷ�����
	void save();
	void saveEquip(tagItemData item);
	void load();
	void loadEquip(tagItemData* item);

	player() {}
	~player() {}
};