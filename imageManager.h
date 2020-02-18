#pragma once
#include "singletonBase.h"
#include "image.h"

class imageManager : public singletonBase <imageManager>
{
private:
	typedef map<string, image*> mapImageList;		//맵으로 만든 이미지목록
	typedef map<string, image*>::iterator mapImageIter;	//맵으로 만든 이미지목록의 반복자

private:
	mapImageList _mImageList;	//실제 이미지클래스를 담을 STL 맵

public:
	//이미지 매니져 초기화
	HRESULT init();
	//이미지 매니져 해제
	void release();

	//빈 비트맵 초기화
	image* addImage(string strKey, int width, int height);
	//이미지 파일 초기화
	image* addImage(string strKey, const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	image* addImage(string strKey, const char* fileName, float x, float y, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	//프레임 이미지 파일 초기화
	image* addFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool isTrans = TRUE, COLORREF transColor = RGB(255, 0, 255));
	image* addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans = TRUE, COLORREF transColor = RGB(255, 0, 255));

	//이미지 키값으로 찾기
	image* findImage(string strKey);
	//이미지 키값으로 삭제
	BOOL deleteImage(string strKey);
	//이미지 전체 삭제
	BOOL deleteAll();

	// 일반
	void render(string strKey, HDC hdc, int destX = 0, int destY = 0);
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	// 알파
	void alphaRender(string strKey, HDC hdc, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);
	void alphaFrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);

	// 프레임
	void frameRender(string strKey, HDC hdc, int destX, int destY);
	void frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	// 루프
	void loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

	// 스케일
	void scaleRender(string strKey, HDC hdc, int destX, int destY, float scale = 1.0f);
	void scaleFrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, float scale = 1.0f);

	// 로테이트
	void rotateRender(string strKey, HDC hdc, float destX, float destY, float angle);
	void rotateFrameRender(string strKey, HDC hdc, float destX, float destY, int currentFrameX, int currentFrameY, float angle);

	imageManager() {}
	~imageManager() {}
};
