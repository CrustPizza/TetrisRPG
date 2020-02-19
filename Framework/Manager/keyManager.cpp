#include "stdafx.h"
#include "keyManager.h"

HRESULT keyManager::init()
{
	//키값 초기화
	for (int i = 0; i < KEYMAX; i++)
	{
		_keyUp[i] = false;
		_keyDown[i] = false;
	}

	return S_OK;
}

void keyManager::release()
{
}

bool keyManager::isOnceKeyDown(int key)
{
	// 키가 눌렸는지 확인
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!_keyDown[key])
		{
			_keyDown[key] = true;
			return true;
		}
	}
	else
	{
		_keyDown[key] = false;
	}

	return false;
}

bool keyManager::isOnceKeyUp(int key)
{
	// 키가 떼어졌는지 확인
	if (GetAsyncKeyState(key) & 0x8000)
	{
		_keyUp[key] = true;
	}
	else
	{
		if (_keyUp[key])
		{
			_keyUp[key] = false;
			return true;
		}
	}

	return false;
}

bool keyManager::isStayKeyDown(int key)
{
	// 키가 눌러진 상태인지 확인
	if (GetAsyncKeyState(key) & 0x8000)
	{
		return true;
	}

	return false;
}

bool keyManager::isToggleKey(int key)
{
	// 키 On/Off 확인
	if (GetKeyState(key) & 0x0001)
	{
		return true;
	}
	return false;
}
