#include "stdafx.h"
#include "skill.h"

HRESULT skill::init()
{
	setSkill(&skill1, SLOW);
	setSkill(&skill2, LONG_BLOCK);

	return S_OK;
}

void skill::release()
{
}

void skill::update()
{
}

void skill::render()
{
}

void skill::skillActivate(tagSkill* skill, tagStone* enemy, bool* tetris)
{
	if (skill->activate)
	{
		switch (skill->name)
		{
		case SLOW:
			enemy->atkTimer = skill->runTimer + (GetTickCount64() - skill->runTimer) / skill->value;

			if (GetTickCount64() - skill->saveTimer >= skill->runTime)
			{
				skill->saveTimer = GetTickCount64();
				skill->activate = false;
			}
			break;
		case LONG_BLOCK:
			*tetris = true;

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
	skill.img->render(getMemDC(), x, y);

	if (!skill.activate)
	{

	}
}

void skill::setSkill(tagSkill* skill, tagSkillName name)
{
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