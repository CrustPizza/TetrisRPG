#include "stdafx.h"
#include "imageManager.h"

HRESULT imageManager::init()
{
	return S_OK;
}

void imageManager::release()
{
	this->deleteAll();
}

image * imageManager::addImage(string strKey, int width, int height)
{
	//추가하려는 이미지가 존재한다면 키값으로 확인
	image* img = findImage(strKey);

	//추가하려는 이미지가 이미 존재한다면 새로 만들지 않고 해당이미지를 리턴
	if (img) return img;

	//키값으로 찾았는데 없으니까 새로 생성
	img = new image;
	if (FAILED(img->init(width, height)))
	{
		img->release();
		SAFE_DELETE(img);
		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::addImage(string strKey, const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	//추가하려는 이미지가 존재한다면 키값으로 확인
	image* img = findImage(strKey);

	//추가하려는 이미지가 이미 존재한다면 새로 만들지 않고 해당이미지를 리턴
	if (img) return img;

	//키값으로 찾았는데 없으니까 새로 생성
	img = new image;
	if (FAILED(img->init(fileName, width, height, isTrans, transColor)))
	{
		img->release();
		SAFE_DELETE(img);
		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::addImage(string strKey, const char * fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	//추가하려는 이미지가 존재한다면 키값으로 확인
	image* img = findImage(strKey);

	//추가하려는 이미지가 이미 존재한다면 새로 만들지 않고 해당이미지를 리턴
	if (img) return img;

	//키값으로 찾았는데 없으니까 새로 생성
	img = new image;
	if (FAILED(img->init(fileName, x, y, width, height, isTrans, transColor)))
	{
		img->release();
		SAFE_DELETE(img);
		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::addFrameImage(string strKey, const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//추가하려는 이미지가 존재한다면 키값으로 확인
	image* img = findImage(strKey);

	//추가하려는 이미지가 이미 존재한다면 새로 만들지 않고 해당이미지를 리턴
	if (img) return img;

	//키값으로 찾았는데 없으니까 새로 생성
	img = new image;
	if (FAILED(img->init(fileName, width, height, frameX, frameY, isTrans, transColor)))
	{
		img->release();
		SAFE_DELETE(img);
		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::addFrameImage(string strKey, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//추가하려는 이미지가 존재한다면 키값으로 확인
	image* img = findImage(strKey);

	//추가하려는 이미지가 이미 존재한다면 새로 만들지 않고 해당이미지를 리턴
	if (img) return img;

	//키값으로 찾았는데 없으니까 새로 생성
	img = new image;
	if (FAILED(img->init(fileName, x, y, width, height, frameX, frameY, isTrans, transColor)))
	{
		img->release();
		SAFE_DELETE(img);
		return NULL;
	}
	
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::findImage(string strKey)
{
	//해당 키 검색
	mapImageIter key = _mImageList.find(strKey);

	//검색한 키를 찾았다면 값 리턴
	if (key != _mImageList.end())
	{
		return key->second;
	}

	//검색한 키로 이미지를 찾지 못했다면 NULL리턴
	return nullptr;
}

BOOL imageManager::deleteImage(string strKey)
{
	//해당 키 검색
	mapImageIter key = _mImageList.find(strKey);

	//검색한 키를 찾았다면 해당 이미지 삭제
	if (key != _mImageList.end())
	{
		//이미지 해제
		key->second->release();
		//메모리 해제
		SAFE_DELETE(key->second);
		//맵의 반복자 해제
		_mImageList.erase(key);

		return TRUE;
	}

	//검색한 키로 이미지를 찾지 못했다면 NULL리턴
	return FALSE;
}

BOOL imageManager::deleteAll()
{
	//맵전체를 돌면서 하나씩 전부 지운다
	mapImageIter iter = _mImageList.begin();
	//for(;;) => while(true)
	for (; iter != _mImageList.end();)
	{
		//이미지가 있으니 이미지 클래스 삭제
		if (iter->second != NULL)
		{
			iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
		}
		else//이미지 없으면
		{
			++iter;
		}
	}

	//맵 전체를 삭제
	_mImageList.clear();

	return TRUE;
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY)
{
	//이미지를 찾아서 그냥 이미지클래스의 함수를 실행
	image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY);
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	//이미지를 찾아서 그냥 이미지클래스의 함수를 실행
	image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
}

void imageManager::alphaRender(string strKey, HDC hdc, BYTE alpha)
{
	//이미지를 찾아서 그냥 이미지클래스의 함수를 실행
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, alpha);
}

void imageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha)
{
	//이미지를 찾아서 그냥 이미지클래스의 함수를 실행
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, alpha);
}

void imageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	//이미지를 찾아서 그냥 이미지클래스의 함수를 실행
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight, alpha);
}

void imageManager::alphaFrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	image* img = findImage(strKey);
	if (img) img->alphaFrameRender(hdc, destX, destY, currentFrameX, currentFrameY, alpha);
}

void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY)
{
	//이미지를 찾아서 그냥 이미지클래스의 함수를 실행
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY);
}

void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	//이미지를 찾아서 그냥 이미지클래스의 함수를 실행
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}

void imageManager::loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	//이미지를 찾아서 그냥 이미지클래스의 함수를 실행
	image* img = findImage(strKey);
	if (img) img->loopRender(hdc, drawArea, offsetX, offsetY);
}

void imageManager::loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{
	//이미지를 찾아서 그냥 이미지클래스의 함수를 실행
	image* img = findImage(strKey);
	if (img) img->loopAlphaRender(hdc, drawArea, offsetX, offsetY, alpha);
}

void imageManager::scaleRender(string strKey, HDC hdc, int destX, int destY, float scale)
{
	//이미지를 찾아서 그냥 이미지클래스의 함수를 실행
	image* img = findImage(strKey);
	if (img) img->scaleRender(hdc, destX, destY, scale);
}

void imageManager::scaleFrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, float scale)
{
	//이미지를 찾아서 그냥 이미지클래스의 함수를 실행
	image* img = findImage(strKey);
	if (img) img->scaleFrameRender(hdc, destX, destY, currentFrameX, currentFrameY, scale);
}

void imageManager::rotateRender(string strKey, HDC hdc, float destX, float destY, float angle)
{
	//이미지를 찾아서 그냥 이미지클래스의 함수를 실행
	image* img = findImage(strKey);
	if (img) img->rotateRender(hdc, destX, destY, angle);
}

void imageManager::rotateFrameRender(string strKey, HDC hdc, float destX, float destY, int currentFrameX, int currentFrameY, float angle)
{
	//이미지를 찾아서 그냥 이미지클래스의 함수를 실행
	image* img = findImage(strKey);
	if (img) img->rotateFrameRender(hdc, destX, destY, currentFrameX, currentFrameY, angle);
}
