#include "stdafx.h"
#include "progressBar.h"

HRESULT progressBar::init(string frontKey, const char* frontImageKey, int frontX, int frontY, int frontWidth, int frontHeight, string backKey, const char* backImageKey, int backX, int backY, int backWidth, int backHeight)
{
	// 버퍼 초기화
	char frontImage[128];
	char backImage[128] = { 0 };
	ZeroMemory(frontImage, sizeof(frontImage));
	// 이미지이름.bmp로 만들기
	sprintf(frontImage, "%s.bmp", frontImageKey);
	sprintf(backImage, "%s.bmp", backImageKey);

	//체력바 이미지 초기화
	_progressBarFront = IMAGEMANAGER->addImage(frontKey, frontImage, frontX, frontY, frontWidth, frontHeight, true, RGB(255, 0, 255));
	_progressBarBack = IMAGEMANAGER->addImage(backKey, backImage, backX, backY, backWidth, backHeight, true, RGB(255, 0, 255));

	// 진행상태 초기화
	_currentProgress = 0;

	return S_OK;
}

void progressBar::release()
{
}

void progressBar::update()
{
}

void progressBar::render()
{
	// Hp바 Back 이미지
	_progressBarBack->render(getMemDC(), _progressBarBack->getX(), _progressBarBack->getY());
	// Hp바 front 이미지
	_progressBarFront->render(getMemDC(), _progressBarFront->getX(), _progressBarFront->getY(), 0, 0, _currentProgress, _progressBarFront->getHeight());
}

void progressBar::setGauge(float currentHp, float maxHp)
{
	// 진행상태 설정
	_currentProgress = (currentHp / maxHp) * _progressBarFront->getWidth();
}
