#include "stdafx.h"
#include "sceneManager.h"
#include "gameNode.h"

HRESULT sceneManager::init()
{
	return S_OK;
}

void sceneManager::release()
{
	// 맵에 담긴 씬 메모리 해제
	for (miSceneList iter = _mSceneList.begin(); iter != _mSceneList.end();)
	{
		if (iter->second != NULL)
		{
			if (iter->second == _currentScene) iter->second->release();
				SAFE_DELETE(iter->second);
			
			iter = _mSceneList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
	_mSceneList.clear();
}

void sceneManager::update()
{
	// 현재씬이 존재하면 해당하는 현재씬을 업데이트
	if (_currentScene) _currentScene->update();
}

void sceneManager::render()
{
	//현재씬이 존재하면 해당하는 현재씬을 렌더해라
	if (_currentScene) _currentScene->render();
}

gameNode * sceneManager::addScene(string sceneName, gameNode * scene)
{
	// 씬이 없으면 Null값 반환
	if (!scene) return NULL;

	// 씬이 있으면 맵에 담기
	_mSceneList.insert(make_pair(sceneName, scene));
	return scene;
}

HRESULT sceneManager::loadScene(string sceneName)
{
	miSceneList find = _mSceneList.find(sceneName);

	// 못찾았다면 E_FAIL
	if (find == _mSceneList.end()) return E_FAIL;

	// 바꾸려는 씬과 현재씬이 같다면 E_FAIL
	if (find->second == _currentScene) return E_FAIL;

	// 씬 변경
	if (SUCCEEDED(find->second->init()))
	{
		_currentScene = find->second;
		return S_OK;
	}

	return E_FAIL;
}
