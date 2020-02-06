#pragma once
#include "gameNode.h"
#include "loading.h"

#define BOARD_WIDTH 500
#define INVENTORY_IMAGE_SIZE 50

class gameLoading : public gameNode
{
private:
	loading*		_loading;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void imageList();
	void soundList();

	gameLoading() {}
	~gameLoading() {}
};