#pragma once
#include "gameNode.h"
#include "progressBar.h"
#include "Item.h"

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
	tagStone _blueStone;
	tagStone _darkBrownStone;
	tagStone _greenStone;
	tagStone _orangeStone;
	tagStone _fullColorStone;

	Item* _item;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void blueStoneInit(int x, int y, int frameX, int frameY);
	void darkBrownStoneInit(int x, int y, int frameX, int frameY);
	void greenStoneInit(int x, int y, int frameX, int frameY);
	void orangeStoneInit(int x, int y, int frameX, int frameY);
	void fullColorStoneInit(int x, int y, int frameX, int frameY);
	void hpBarInit(tagStone* target, string keyNameFront, string keyNameBack, int x, int y);
	void actionBarInit(tagStone* target, string keyNameFront, string keyNameBack, int x, int y);

	tagStone* getBlueStone() { return &_blueStone; }
	tagStone* getDarkBrownStone() { return &_darkBrownStone; }
	tagStone* getGreenStone() { return &_greenStone; }
	tagStone* getOrangeStone() { return &_orangeStone; }
	tagStone* getFullColorStone() { return &_fullColorStone; }
	int getEnemyAtk(tagStone* target) { return target->atk; }

	bool stoneUpdate(tagStone* target);
	void damagedUpdate(tagStone* target);

	void stoneRender(tagStone* target);
	void setEnemyHp(tagStone* target, int hp) { target->hp = hp; }

	enemy() {}
	~enemy() {}
};

