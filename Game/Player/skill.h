#pragma once
#include "gameNode.h"
#include "enemy.h"

// 스킬이름 명시
enum tagSkillName
{
	SLOW,
	LONG_BLOCK
};

// 스킬 데이터 구조체
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
	// 에너미
	enemy* _enemy;

	// 스킬 슬롯번호
	tagSkill skill1;
	tagSkill skill2;

public:
	HRESULT init();
	void release();

	// 스킬 게터
	tagSkill* getSkill1Ptr() { return &skill1; }
	tagSkill* getSkill2Ptr() { return &skill2; }

	// 스킬 발동
	void skillActivate(tagSkill* skill, tagStone* enemy, bool* tetris = nullptr);

	// 스킬 렌더
	void skillRender(tagSkill skill, int x, int y);

	// 상호참조용 에너미 셋 함수
	void setEnemy(enemy* enemy) { _enemy = enemy; }

	// 스킬 셋
	void setSkill(tagSkill* skill, tagSkillName name);

	skill() {}
	~skill() {}
};
