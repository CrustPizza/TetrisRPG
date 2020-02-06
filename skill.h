#pragma once
#include "gameNode.h"
#include "enemy.h"

enum tagSkillName
{
	SLOW,
	LONG_BLOCK
};

struct tagSkill
{
	tagSkillName name;
	image* img;
	bool activate;
	float value;
	ULONGLONG runTimer;
	ULONGLONG saveTimer;
	int cooltime;
	int runTime;
};

class skill : public gameNode
{
private:
	enemy* _enemy;

	tagSkill skill1;
	tagSkill skill2;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	tagSkill* getSkill1Ptr() { return &skill1; }
	tagSkill* getSkill2Ptr() { return &skill2; }

	void skillActivate(tagSkill* skill, tagStone* enemy, bool* tetris = nullptr);

	void skillRender(tagSkill skill, int x, int y);

	void setEnemy(enemy* enemy) { _enemy = enemy; }

	void setSkill(tagSkill* skill, tagSkillName name);

	skill() {}
	~skill() {}
};