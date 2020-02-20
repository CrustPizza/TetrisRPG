#pragma once
#include "gameNode.h"
#include "gameLoading.h"
#include "main.h"
#include "battle.h"

class mainGame : public gameNode
{
public:
	HRESULT init();
	void release();
	void update();
	void render();

	mainGame() {}
	~mainGame() {}
};
