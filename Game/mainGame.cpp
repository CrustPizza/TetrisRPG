#include "stdafx.h"
#include "mainGame.h"

HRESULT mainGame::init()
{
	gameNode::init();

	// 효과음용 볼륨크기
	SOUNDMANAGER->setEffectVolume(1.0f);
	
	// 씬 추가
	SCENEMANAGER->addScene("Loading", new gameLoading);
	SCENEMANAGER->addScene("Main", new main);
	SCENEMANAGER->addScene("Battle", new battle);

	// 현재 씬 설정
	SCENEMANAGER->loadScene("Loading");

	return S_OK;
}

void mainGame::release()
{
	gameNode::release();
}


void mainGame::update()
{
	gameNode::update();
	
	// 씬매니져 업데이트
	SCENEMANAGER->update();

	// 사운드매니져 업데이트
	SOUNDMANAGER->update();
}

void mainGame::render()
{
	//흰색 빈 비트맵
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

	//씬매니져 렌더
	SCENEMANAGER->render();

	//백버퍼의 내용을 HDC에 그린다
	this->getBackBuffer()->render(getHDC());
}
