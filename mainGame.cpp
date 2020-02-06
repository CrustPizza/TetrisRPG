#include "stdafx.h"
#include "mainGame.h"

//=============================================================
//	## 초기화 ## init()
//=============================================================
HRESULT mainGame::init()
{
	gameNode::init();
	//이곳에서 초기화를 한다

	/*앞으로 메엔게임은 각각의 씬들만 관리를 한다*/
	//각각의 씬들이 메인게임 역할을 하면 된다

	SOUNDMANAGER->setEffectVolume(1.0f);
	
	/*씬추가*/
	SCENEMANAGER->addScene("Loading", new gameLoading);
	SCENEMANAGER->addScene("Main", new main);
	SCENEMANAGER->addScene("Battle", new battle);

	//현재씬 설정
	SCENEMANAGER->loadScene("Loading");

	return S_OK;
}

//=============================================================
//	## 해제 ## release()
//=============================================================
void mainGame::release()
{
	gameNode::release();
	//이미지 클래스를 나갈때까진 사용할 일 없다
	//동적할당 new를 사용했다면 이곳에서 SAFE_DELETE() 사용한다
}


//=============================================================
//	## 업데이트 ## update()
//=============================================================
void mainGame::update()
{
	gameNode::update();
	//이곳에서 계산식, 키보드, 마우스등등 업데이트를 한다
	//간단하게 이곳에서 코딩한다고 생각하면 된다
	
	//씬매니져 업데이트
	SCENEMANAGER->update();

	//사운드매니져 업데이트(이놈안해주면 사운드가 정상작동안함)
	SOUNDMANAGER->update();
}

//=============================================================
//	## 렌더 ## render(HDC hdc)
//=============================================================
void mainGame::render()
{
	//흰색 빈 비트맵 (이것도 렌더에 그냥 두기)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
//=============================================================

	//씬매니져 렌더
	SCENEMANAGER->render();

//=============================================================
	//백버퍼의 내용을 HDC에 그린다 (이것도 렌더에 그냥 두기)
	this->getBackBuffer()->render(getHDC());
}