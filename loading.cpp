#include "stdafx.h"
#include "loading.h"

//=============================================================
//	## loadItem ## (�ε������)
//=============================================================
HRESULT loadItem::init(string keyName, int width, int height)
{
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_IMAGE_0;

	//�̹��� ����ü �ʱ�ȭ
	_imageResource.keyName = keyName;
	_imageResource.widht = width;
	_imageResource.height = height;

	return S_OK;
}

HRESULT loadItem::init(string keyName, const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_IMAGE_1;

	//�̹��� ����ü �ʱ�ȭ
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
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_IMAGE_2;

	//�̹��� ����ü �ʱ�ȭ
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
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_FRAMEIMAGE_0;

	//�̹��� ����ü �ʱ�ȭ
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
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_FRAMEIMAGE_1;

	//�̹��� ����ü �ʱ�ȭ
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
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_SOUND;
	
	//�̹��� ����ü �ʱ�ȭ
	_soundResource.keyName = keyName;
	_soundResource.fileName = fileName;
	_soundResource.bgm = bgm;
	_soundResource.loop = loop;

	return S_OK;
}

//=============================================================
//	## loading ## (�ε�Ŭ����)
//=============================================================
HRESULT loading::init()
{
	//�ε�ȭ�� UI
	_background = IMAGEMANAGER->addImage("BackGround", "Img/Loading/bg.bmp", WINSIZEX, WINSIZEY);
	_logo = IMAGEMANAGER->addImage("Logo", "Img/Loading/logoSize500.bmp", (WINSIZEX - 500) / 2, 100, 500, 316, true, RGB(255, 0, 255));
	_start = IMAGEMANAGER->addFrameImage("Start", "Img/Loading/start.bmp", (WINSIZEX - 504) / 2, WINSIZEY / 2 + 100, 504, 328, 1, 2, true, RGB(255, 0, 255));
	
	// ����, Ÿ�̸� �� ���� �ʱ�ȭ
	_loopX = 0;
	_loopY = 0;
	_startTimer = GetTickCount64();
	_done = false;

	//�ε��� Ŭ���� �ʱ�ȭ
	_loadingBar = new progressBar;
	_loadingBar->init("LoadingFront", "Img/Loading/loadingFront", (WINSIZEX - 320) / 2, WINSIZEY - 96, 320, 32, "LoadingBack", "Img/Loading/loadingBack", (WINSIZEX - 330) / 2, WINSIZEY - 100, 330, 40);
	_loadingBar->setGauge(0, 0);
	//���� ������
	_currentGauge = 0;

	return S_OK;
}

void loading::release()
{
	//�ε��� Ŭ���� ����
	_loadingBar->release();
	SAFE_DELETE(_loadingBar);
}

void loading::update()
{
	// �ε�
	_done = loadingDone();
	_loadingBar->update();

	// �۾��� �Ϸ�Ǹ� Start �̹����� �������� �����Ѵ�
	if (_done)
	{
		if (GetTickCount64() - _startTimer >= 500)
		{
			_startTimer = GetTickCount64();
			_start->setFrameY(!_start->getFrameY());
		}
	}

	// ���� ����
	_loopX++;
	_loopY--;
}

void loading::render()
{
	// UI ����
	_background->loopAlphaRender(getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), _loopX, _loopY, 100);
	_logo->render(getMemDC(), _logo->getX(), _logo->getY());

	// �ε��ٸ� �����ִٰ� �ε��� ������ Start�̹����� ����
	if (_done)
		_start->frameRender(getMemDC(), _start->getX(), _start->getY());
	else
		_loadingBar->render();
}

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
	//�ε��Ϸ��
	if (_currentGauge >= _vLoadItem.size())
	{
		return true;
	}
	
	loadItem* item = _vLoadItem[_currentGauge];

	tagImageResource img;

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
	//�� ���� ���� ���� �˾Ƽ�...
	case LOAD_KIND_SOUND:
		SOUNDMANAGER->addSound(item->getSoundResource().keyName, item->getSoundResource().fileName, item->getSoundResource().bgm, item->getSoundResource().loop);
		break;
	}

	//���� ������ ����
	_currentGauge++;

	//�ε��� �̹��� ����
	_loadingBar->setGauge(_currentGauge * 10 / _vLoadItem.size(), 10);

	return false;
}