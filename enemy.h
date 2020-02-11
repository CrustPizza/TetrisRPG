#pragma once
#include "gameNode.h"
#include "progressBar.h"
#include "Item.h"

// 에너미 정보 구조체
struct tagStone
{
	bool create;
	image* img;
	int hp;
	int maxHp;
	int atk;
	ULONGLONG atkTimer;
	int atkDelay;
	bool move;
	ULONGLONG moveTimer;
	progressBar* hpBar;
	progressBar* actionBar;
	bool damaged;
	image* damagedImg;
	BYTE alpha;
	tagType itemType;
	string itemName;
	int gold;
};

class enemy : public gameNode
{
private:
	// 에너미들
	tagStone _blueStone;
	tagStone _darkBrownStone;
	tagStone _greenStone;
	tagStone _orangeStone;
	tagStone _fullColorStone;

	// 아이템 클래스
	Item* _item;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	// 각 에너미 및 Bar 초기화 함수
	void blueStoneInit(int x, int y, int frameX, int frameY);
	void darkBrownStoneInit(int x, int y, int frameX, int frameY);
	void greenStoneInit(int x, int y, int frameX, int frameY);
	void orangeStoneInit(int x, int y, int frameX, int frameY);
	void fullColorStoneInit(int x, int y, int frameX, int frameY);
	void hpBarInit(tagStone* target, string keyNameFront, string keyNameBack, int x, int y);
	void actionBarInit(tagStone* target, string keyNameFront, string keyNameBack, int x, int y);

	// 에너미 정보 받아오는 함수
	tagStone* getBlueStone() { return &_blueStone; }
	tagStone* getDarkBrownStone() { return &_darkBrownStone; }
	tagStone* getGreenStone() { return &_greenStone; }
	tagStone* getOrangeStone() { return &_orangeStone; }
	tagStone* getFullColorStone() { return &_fullColorStone; }
	
	// 공격력 받기
	int getEnemyAtk(tagStone* target) { return target->atk; }
	
	// Hp 변경
	void setEnemyHp(tagStone* target, int hp) { if (hp < 0) hp = 0; target->hp = hp; }
	
	// 에너미 및 피격 업데이트
	bool stoneUpdate(tagStone* target);
	void damagedUpdate(tagStone* target);

	// 에너미 랜더
	void stoneRender(tagStone* target);

	enemy() {}
	~enemy() {}
};

