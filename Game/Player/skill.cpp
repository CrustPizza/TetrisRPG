#include "stdafx.h"
#include "skill.h"

HRESULT skill::init()
{
	// 스킬 세팅
	setSkill(&skill1, SLOW);
	setSkill(&skill2, LONG_BLOCK);

	return S_OK;
}

void skill::release()
{
}

void skill::skillActivate(tagSkill* skill, tagStone* enemy, bool* tetris)
{
	// 스킬이 발동중일때 효과 적용시키는 함수
	if (skill->activate)
	{
		// 이름에 따라 다른 효과 주기
		switch (skill->name)
		{
		case SLOW:
			// 에너미의 공격속도 지연시키기
			enemy->atkTimer = skill->runTimer + (GetTickCount64() - skill->runTimer) / skill->value;

			// 스킬 지속시간이 다 되었을 경우 비활성화
			if (GetTickCount64() - skill->saveTimer >= skill->runTime)
			{
				skill->saveTimer = GetTickCount64();
				skill->activate = false;
			}
			break;
		case LONG_BLOCK:
			// Bool 변수 활성화
			*tetris = true;

			// 스킬 지속시간이 다 되었을 경우 비활성화
			if (GetTickCount64() - skill->saveTimer >= skill->runTime)
			{
				*tetris = false;
				skill->saveTimer = GetTickCount64();
				skill->activate = false;
			}
			break;
		}
	}
}

void skill::skillRender(tagSkill skill, int x, int y)
{
	// 스킬 아이콘 출력
	skill.img->render(getMemDC(), x, y);
}

void skill::setSkill(tagSkill* skill, tagSkillName name)
{
	// 스킬 이름에 따라 데이터 
	switch (name)
	{
	case SLOW:
		skill->img = IMAGEMANAGER->findImage("SlowSkill");
		skill->value = 2;
		skill->cooltime = 20000;
		skill->runTime = 10000;
		break;
	case LONG_BLOCK:
		skill->img = IMAGEMANAGER->findImage("LongBlockSkill");
		skill->value = 0;
		skill->cooltime = 30000;
		skill->runTime = 5000;
		break;
	}

	skill->name = name;
	skill->runTimer = GetTickCount64();
	skill->saveTimer = GetTickCount64() - skill->cooltime;
	skill->activate = false;
}
