#pragma once

#include <SDKDDKVer.h>

//디버깅용
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외
// Windows 헤더 파일
#include <Windows.h>
// C 런타임 헤더
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
// C++ 런타임 헤더
#include <iostream>
using namespace std;
// 자주사용하는 STL
#include <string>
#include <vector>
#include <map>
#include <list>

// 방향
namespace dir
{
	enum tagDirection
	{
		LEFT,
		RIGHT,
		UP,
		DOWN,
		DEFAULT
	};
}

// 커스텀 헤더
#include "commonMacroFunction.h"
#include "keyManager.h"
#include "randomFunction.h"
#include "imageManager.h"
#include "util.h"
using namespace MY_UTIL;
using namespace dir;
#include "playerData.h"
#include "txtData.h"
#include "iniData.h"
#include "sceneManager.h"
#include "soundManager.h"

// 싱글톤
#define KEYMANAGER keyManager::getSingleton()
#define RND randomFunction::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define TXTDATA	txtData::getSingleton()
#define INIDATA iniData::getSingleton()
#define SCENEMANAGER sceneManager::getSingleton()
#define SOUNDMANAGER soundManager::getSingleton()

// define문
#define WINNAME 	(LPTSTR)(TEXT("김지훈_TetrisRPG"))
#define WINSTARTX	600
#define WINSTARTY	10
#define WINSIZEX	540
#define WINSIZEY	960
#define WINSTYLE	WS_CAPTION | WS_SYSMENU

// 매크로함수
#define SAFE_DELETE(p)		{if(p) {delete (p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = NULL;}}

// 전역변수
extern HINSTANCE	_hInstance;
extern HWND		_hWnd;
extern POINT		_ptMouse;
