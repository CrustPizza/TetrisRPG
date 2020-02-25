#pragma once
#include "singletonBase.h"

class gameNode;

class sceneManager : public singletonBase <sceneManager>
{
private:
	// 씬 메모리 주소를 Map에 저장
	map<string, gameNode*> _mSceneList;
	typedef map<string, gameNode*>::iterator miSceneList;

	// 현재 씬
	gameNode* _currentScene;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	// 씬추가
	gameNode* addScene(string sceneName, gameNode* scene);
	// 씬변경
	HRESULT loadScene(string sceneName);

	sceneManager() : _currentScene(NULL) {}
	~sceneManager() {}
};

