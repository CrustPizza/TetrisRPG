#include "stdafx.h"
#include "gameNode.h"

HRESULT gameNode::init()
{
	//HDC 얻기
	_hdc = GetDC(_hWnd);

	SetTimer(_hWnd, 1, 10, NULL);		//타이머 초기화
	KEYMANAGER->init();			//키매니져 초기화
	IMAGEMANAGER->init();			//이미지매니져 초기화
	TXTDATA->init();			//TXT데이터 초기화
	INIDATA->init();			//INI데이터 초기화
	SCENEMANAGER->init();			//씬매니져 초기화
	SOUNDMANAGER->init();			//사운드매니져 초기화

	return S_OK;
}

void gameNode::release()
{
	//타이머 해제
	KillTimer(_hWnd, 1);
	
	//키매니져 싱글톤 해제
	KEYMANAGER->release();
	KEYMANAGER->releaseSingleton();
	
	//이미지매니져 싱글톤 해제
	IMAGEMANAGER->release();
	IMAGEMANAGER->releaseSingleton();
	
	//TXT데이터 싱글톤 해제
	TXTDATA->release();
	TXTDATA->releaseSingleton();
	
	//INI데이터 싱글톤 해제
	INIDATA->release();
	INIDATA->releaseSingleton();
	
	//씬매니져 싱글톤 해제
	SCENEMANAGER->release();
	SCENEMANAGER->releaseSingleton();
	
	//사운드매니져 싱글톤 해제
	SOUNDMANAGER->release();
	SOUNDMANAGER->releaseSingleton();

	//HDC 해제
	ReleaseDC(_hWnd, _hdc);
}

void gameNode::update()
{
	InvalidateRect(_hWnd, NULL, false);
}

void gameNode::render()
{
	
}

LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;		 
	PAINTSTRUCT ps; 

	switch (iMessage)
	{
	case WM_TIMER:
		this->update();
		break;
	case WM_PAINT:	
		hdc = BeginPaint(hWnd, &ps);
		this->render();
		EndPaint(hWnd, &ps);
		break;
	case WM_MOUSEMOVE:
		// 마우스 좌표
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
