#include "stdafx.h"
#include "gameNode.h"

//=============================================================
//	## 초기화 ## init()
//=============================================================
HRESULT gameNode::init()
{
	//HDC 얻기
	_hdc = GetDC(_hWnd);

	SetTimer(_hWnd, 1, 10, NULL);		//타이머 초기화
	KEYMANAGER->init();					//키매니져 초기화
	RND->init();						//랜덤펑션 초기화
	IMAGEMANAGER->init();				//이미지매니져 초기화
	PLAYERDATA->init();					//플레이어데이터 초기화
	TXTDATA->init();					//TXT데이터 초기화
	INIDATA->init();					//INI데이터 초기화
	SCENEMANAGER->init();				//씬매니져 초기화
	SOUNDMANAGER->init();				//사운드매니져 초기화

	return S_OK;
}


//=============================================================
//	## 해제 ## release()
//=============================================================
void gameNode::release()
{
	//타이머 해제
	KillTimer(_hWnd, 1);
	//키매니져 싱글톤 해제
	KEYMANAGER->release();
	KEYMANAGER->releaseSingleton();
	//랜덤펑션 싱글톤 해제
	RND->release();
	RND->releaseSingleton();
	//이미지매니져 싱글톤 해제
	IMAGEMANAGER->release();
	IMAGEMANAGER->releaseSingleton();
	//플레이어데이터 싱글톤 해제
	PLAYERDATA->release();
	PLAYERDATA->releaseSingleton();
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

//=============================================================
//	## 업데이트 ## update()
//=============================================================
void gameNode::update()
{
	//새로고침 (나중에 고성능 타이머를 만든 후에는 사용하지 않는다)
	//더블버퍼링 이후 사용하지 않는다 (true => false)
	InvalidateRect(_hWnd, NULL, false);
}

//=============================================================
//	## 렌더 ## render(HDC hdc)
//=============================================================
void gameNode::render()
{
}

//=============================================================
//	## 메인프로시져 ## MainProc()
//=============================================================
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
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
