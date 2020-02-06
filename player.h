#pragma once
#include "gameNode.h"
#include "skill.h"
#include "Item.h"
#include "progressBar.h"
#include "option.h"

class player : public gameNode
{
private:
	// 아이템 정보
	Item*		_item;

	// 캐릭터 이미지
	image*		_img;
	int			_count;
	bool		_frameTurn;
	ULONGLONG	_timer;
	image*		_damagedImg;
	BYTE		_damagedAlpha;

	// 체력바
	progressBar* _hpBar;

	// 소지금
	unsigned int _gold;

	// 스테이터스
	int			_hp;
	int			_maxHp;
	int			_atk;
	int			_def;
	bool		_damaged;

	// 장비
	tagItemData	_weapon;
	tagItemData	_helmet;
	tagItemData	_armor;
	tagItemData	_necklace;
	tagItemData	_shield;
	tagItemData	_belt;
	tagItemData	_shoes;

	// 옵션
	option* _option;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	// 체력바 초기화
	void hpBarInit(int x, int y);

	// 이미지 받기
	image* getImage() { return _img; }

	// 플레이어 이동
	void playerMove(tagDirection dir);

	// 플레이어 일반
	void playerIdle();

	// 플레이어 회피
	bool playerEvasion();

	// 플레이어 공격
	bool playerAttack();

	// 아이템 장착 및 해제
	tagItemData equipItem(tagType type, string name);
	void equitOffItem(tagType type);

	// 체력바 렌더
	void hpBarRender();

	// 타이머
	void setTimer(ULONGLONG timer) { _timer = timer; }

	// 스테이터스 주고 받기
	int getHp() { return _hp; }
	int getMaxHp() { return _maxHp + _belt.value; }
	int getAtk() { return _atk + _weapon.value + _necklace.value; }
	int getDef() { return _def + _armor.value + _helmet.value + _shield.value + _shoes.value; }
	void setHp(int hp) { _hp = hp; if (_hp > getMaxHp()) _hp = getMaxHp(); }
	void setDamaged(bool damaged) { _damaged = damaged; }

	// 소지금 주고 받기
	int getGold() { return _gold; }
	void setGold(int gold) { _gold = gold; }

	// 장비 받기
	tagItemData getWeapon() { return _weapon; }
	tagItemData getHelmet() { return _helmet; }
	tagItemData getArmor() { return _armor; }
	tagItemData getNecklace() { return _necklace; }
	tagItemData getShield() { return _shield; }
	tagItemData getBelt() { return _belt; }
	tagItemData getShoes() { return _shoes; }

	// 저장 & 불러오기
	void save();
	void saveEquip(tagItemData item);
	void load();
	void loadEquip(tagItemData* item);

	player() {}
	~player() {}
};