#include "stdafx.h"
#include "option.h"

HRESULT option::init()
{
	// 저장된 변경 키값 불러오기
	this->load("Key");

	return S_OK;
}

void option::release()
{
	// 변경된 키값 저장
	this->save("Key");
}

void option::update()
{
}

void option::render()
{
}

bool option::keyChange(int type)
{
	// 키가 눌러졌는지 확인하고 눌려진 키 값을 넣는다
	if (GetAsyncKeyState(VK_TAB) & 0x8000)
		return setKey(type, VK_TAB);

	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		return setKey(type, VK_RETURN);

	if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
		return setKey(type, VK_SHIFT);

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		return setKey(type, VK_SPACE);

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		return setKey(type, VK_LEFT);

	if (GetAsyncKeyState(VK_UP) & 0x8000)
		return setKey(type, VK_UP);

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		return setKey(type, VK_RIGHT);

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		return setKey(type, VK_DOWN);

	for (int i = 48; i < 58; i++)
	{
		if (GetAsyncKeyState(i) & 0x8000)
			return setKey(type, i);
	}

	for (int i = 65; i < 91; i++)
	{
		if (GetAsyncKeyState(i) & 0x8000)
			return setKey(type, i);
	}

	return false;
}

bool option::setKey(int type, int key)
{
	// 중복된 키값을 검사하고 중복된 값을 빈값으로 만든다
	keyCheck(true, key);

	// 해당 타입에 키값 입력
	switch (type)
	{
	case 1:
		_keySet.up = key;
		return true;
		break;
	case 2:
		_keySet.down = key;
		return true;
		break;
	case 3:
		_keySet.left = key;
		return true;
		break;
	case 4:
		_keySet.right = key;
		return true;
		break;
	case 5:
		_keySet.hold = key;
		return true;
		break;
	case 6:
		_keySet.drop = key;
		return true;
		break;
	case 7:
		_keySet.skillSlot1 = key;
		return true;
		break;
	case 8:
		_keySet.skillSlot2 = key;
		return true;
		break;
	case 9:
		_keySet.itemSlot1 = key;
		return true;
		break;
	case 10:
		_keySet.itemSlot2 = key;
		return true;
		break;
	}

	return false;
}

bool option::keyCheck(bool change, int key)
{
	// 키값 검사하고 change값이 true라면 빈값(7)을 넣는다.
	if (_keySet.up == key)
	{
		if (change)
			_keySet.up = 7;

		return true;
	}
	if (_keySet.down == key)
	{
		if (change)
			_keySet.down = 7;

		return true;
	}
	if (_keySet.left == key)
	{
		if (change)
			_keySet.left = 7;

		return true;
	}
	if (_keySet.right == key)
	{
		if (change)
			_keySet.right = 7;

		return true;
	}
	if (_keySet.hold == key)
	{
		if (change)
			_keySet.hold = 7;

		return true;
	}
	if (_keySet.drop == key)
	{
		if (change)
			_keySet.drop = 7;

		return true;
	}
	if (_keySet.skillSlot1 == key)
	{
		if (change)
			_keySet.skillSlot1 = 7;

		return true;
	}
	if (_keySet.skillSlot2 == key)
	{
		if (change)
			_keySet.skillSlot2 = 7;

		return true;
	}
	if (_keySet.itemSlot1 == key)
	{
		if (change)
			_keySet.itemSlot1 = 7;

		return true;
	}
	if (_keySet.itemSlot2 == key)
	{
		if (change)
			_keySet.itemSlot2 = 7;

		return true;
	}

	return false;
}

void option::keyRender(int x, int y, int key)
{
	// 키 설정창에서 무슨 키인지 출력하기 위한 함수
	char cBuf[10] = {};
	
	switch (key)
	{
	case VK_TAB:
		TextOut(getMemDC(), x - 22, y, "TAB", strlen("TAB"));
		break;
	case VK_RETURN:
		TextOut(getMemDC(), x - 36, y, "ENTER", strlen("ENTER"));
		break;
	case VK_SHIFT:
		TextOut(getMemDC(), x - 36, y, "SHIFT", strlen("SHIFT"));
		break;
	case VK_SPACE:
		TextOut(getMemDC(), x - 36, y, "SPACE", strlen("SPACE"));
		break;
	case VK_LEFT:
		TextOut(getMemDC(), x - 15, y, "←", strlen("←"));
		break;
	case VK_UP:
		TextOut(getMemDC(), x - 15, y, "↑", strlen("↑"));
		break;
	case VK_RIGHT:
		TextOut(getMemDC(), x - 15, y, "→", strlen("→"));
		break;
	case VK_DOWN:
		TextOut(getMemDC(), x - 15, y, "↓", strlen("↓"));
		break;
	default:
		if (key >= 48 && key <= 57)
		{
			sprintf(cBuf, "%c", key);
			TextOut(getMemDC(), x - 5, y, cBuf, strlen(cBuf));
		}
		else if (key >= 65 && key <= 90)
		{
			sprintf(cBuf, "%c", key);
			TextOut(getMemDC(), x - 5, y, cBuf, strlen(cBuf));
		}
		break;
	}
}

bool option::crushButton(tagButton* button, int activate, int deactivate)
{
	// 마우스와 충돌중인지 확인하고 충돌중일 경우 효과음 및 프레임을 전환한다
	if (PtInRect(&button->img->boudingBoxWithFrame(), _ptMouse))
	{
		// 버튼 사운드 bool값이 True일때만 사운드가 나게해서 사운드가 중복되지 않도록 설정
		if (button->sound)
		{
			button->sound = false;

			SOUNDMANAGER->play("MouseOver", SOUNDMANAGER->getEffectVolume());
		}

		button->img->setFrameX(activate);

		return true;
	}
	else
	{
		// 마우스와 충돌되지 않을때 다시 마우스 오버 사운드가 작동하도록 True로 변경
		button->sound = true;
		button->img->setFrameX(deactivate);

		return false;
	}
}

void option::save(string fileName)
{
	HANDLE file;
	DWORD write;

	// 파일 생성
	file = CreateFile(fileName.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	// 키 값 저장
	WriteFile(file, &_keySet, sizeof(_keySet), &write, NULL);

	// 파일 닫기
	CloseHandle(file);
}

void option::load(string fileName)
{
	HANDLE file;
	DWORD read;
	
	// 키 값 초기화
	ZeroMemory(&_keySet, sizeof(_keySet));

	// 읽기 전용 파일 생성
	file = CreateFile(fileName.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	// 키 값에 파일에 저장된 값 넣기
	ReadFile(file, &_keySet, sizeof(_keySet), &read, NULL);

	// 파일 닫기
	CloseHandle(file);
}
