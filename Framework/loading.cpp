#include "stdafx.h"
#include "loading.h"

HRESULT loadItem::init(string keyName, int width, int height)
{
	//로딩종류 초기화
	_kind = LOAD_KIND_IMAGE_0;

	//이미지 구조체 초기화
	_imageResource.keyName = keyName;
	_imageResource.widht = width;
	_imageResource.height = height;

	return S_OK;
}

HRESULT loadItem::init(string keyName, const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	//로딩종류 초기화
	_kind = LOAD_KIND_IMAGE_1;

	//이미지 구조체 초기화
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.widht = width;
	_imageResource.height = height;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::init(string keyName, const char * fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	//로딩종류 초기화
	_kind = LOAD_KIND_IMAGE_2;

	//이미지 구조체 초기화
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.widht = width;
	_imageResource.height = height;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::init(string keyName, const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//로딩종류 초기화
	_kind = LOAD_KIND_FRAMEIMAGE_0;

	//이미지 구조체 초기화
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.widht = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;
	
	return S_OK;
}

HRESULT loadItem::init(string keyName, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//로딩종류 초기화
	_kind = LOAD_KIND_FRAMEIMAGE_1;

	//이미지 구조체 초기화
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.widht = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::init(string keyName, const char* fileName, bool bgm, bool loop)
{
	//로딩종류 초기화
	_kind = LOAD_KIND_SOUND;
	
	//이미지 구조체 초기화
	_soundResource.keyName = keyName;
	_soundResource.fileName = fileName;
	_soundResource.bgm = bgm;
	_soundResource.loop = loop;

	return S_OK;
}

HRESULT loading::init()
{
	//로딩화면 UI
	_background = IMAGEMANAGER->addImage("BackGround", "Img/Loading/bg.bmp", WINSIZEX, WINSIZEY);
	_logo = IMAGEMANAGER->addImage("Logo", "Img/Loading/logoSize500.bmp", (WINSIZEX - 500) / 2, 100, 500, 316, true, RGB(255, 0, 255));
	_start = IMAGEMANAGER->addFrameImage("Start", "Img/Loading/start.bmp", (WINSIZEX - 504) / 2, WINSIZEY / 2 + 100, 504, 328, 1, 2, true, RGB(255, 0, 255));
	
	// 루프, 타이머 등 변수 초기화
	_loopX = 0;
	_loopY = 0;
	_startTimer = GetTickCount64();
	_done = false;

	//로딩바 클래스 초기화
	_loadingBar = new progressBar;
	_loadingBar->init("LoadingFront", "Img/Loading/loadingFront", (WINSIZEX - 320) / 2, WINSIZEY - 96, 320, 32, "LoadingBack", "Img/Loading/loadingBack", (WINSIZEX - 330) / 2, WINSIZEY - 100, 330, 40);
	_loadingBar->setGauge(0, 0);
	//현재 게이지
	_currentGauge = 0;

	return S_OK;
}

void loading::release()
{
	//로딩바 클래스 해제
	_loadingBar->release();
	SAFE_DELETE(_loadingBar);
}

void loading::update()
{
	// 로딩
	_done = loadingDone();
	_loadingBar->update();

	// 작업이 완료되면 Start 이미지의 프레임을 조절한다
	if (_done)
	{
		if (GetTickCount64() - _startTimer >= 500)
		{
			_startTimer = GetTickCount64();
			_start->setFrameY(!_start->getFrameY());
		}
	}

	// 루프 조절
	_loopX++;
	_loopY--;
}

void loading::render()
{
	// UI 렌더
	_background->loopAlphaRender(getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), _loopX, _loopY, 100);
	_logo->render(getMemDC(), _logo->getX(), _logo->getY());

	// 로딩바를 보여주다가 로딩이 끝나면 Start이미지를 띄운다
	if (_done)
		_start->frameRender(getMemDC(), _start->getX(), _start->getY());
	else
		_loadingBar->render();
}

// 이미지 정보에 따라 오버로딩으로 데이터 저장
void loading::loadImage(string keyName, int width, int height)
{
	loadItem* item = new loadItem;
	item->init(keyName, width, height);
	_vLoadItem.push_back(item);
}

void loading::loadImage(string keyName, const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->init(keyName, fileName, width, height, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadImage(string keyName, const char * fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->init(keyName, fileName, x, y, width, height, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadFrameImage(string keyName, const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->init(keyName, fileName, width, height, frameX, frameY, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadFrameImage(string keyName, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->init(keyName, fileName, x, y, width, height, frameX, frameY, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadSound(string keyName, const char* fileName, bool bgm, bool loop)
{
	loadItem* item = new loadItem;
	item->init(keyName, fileName, bgm, loop);
	_vLoadItem.push_back(item);
}

bool loading::loadingDone()
{
	// 로딩완료되면 True값 반환
	if (_currentGauge >= _vLoadItem.size())
	{
		return true;
	}
	
	loadItem* item = _vLoadItem[_currentGauge];

	tagImageResource img;

	// 데이터 타입에 따라 이미지 및 사운드를 로드한다.
	switch (item->getLoadingKind())
	{
	case LOAD_KIND_IMAGE_0:
		img = item->getImageResource();
		IMAGEMANAGER->addImage(img.keyName, img.widht, img.height);
		break;
	case LOAD_KIND_IMAGE_1:
		img = item->getImageResource();
		IMAGEMANAGER->addImage(img.keyName, img.fileName, img.widht, img.height, img.trans, img.transColor);
		break;
	case LOAD_KIND_IMAGE_2:
		img = item->getImageResource();
		IMAGEMANAGER->addImage(img.keyName, img.fileName, img.x, img.y, img.widht, img.height, img.trans, img.transColor);
		break;
	case LOAD_KIND_FRAMEIMAGE_0:
		img = item->getImageResource();
		IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.widht, img.height, img.frameX, img.frameY, img.trans, img.transColor);
		break;
	case LOAD_KIND_FRAMEIMAGE_1:
		img = item->getImageResource();
		IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.x, img.y, img.widht, img.height, img.frameX, img.frameY, img.trans, img.transColor);
		break;
	case LOAD_KIND_SOUND:
		SOUNDMANAGER->addSound(item->getSoundResource().keyName, item->getSoundResource().fileName, item->getSoundResource().bgm, item->getSoundResource().loop);
		break;
	}

	// 현재 게이지 증가
	_currentGauge++;

	// 로딩바 이미지 변경
	_loadingBar->setGauge(_currentGauge * 10 / _vLoadItem.size(), 10);

	return false;
}
