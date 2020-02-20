#pragma once
#include "singletonBase.h"

#define KEYMAX 256

class keyManager : public singletonBase <keyManager>
{
private:
	bool _keyUp[KEYMAX];
	bool _keyDown[KEYMAX];

public:
	//키매니져 초기화
	HRESULT init();
	//키매니져 해제
	void release();

	bool isOnceKeyDown(int key);
	bool isOnceKeyUp(int key);
	bool isStayKeyDown(int key);
	bool isToggleKey(int key);

	keyManager() {}
	~keyManager() {}
};

