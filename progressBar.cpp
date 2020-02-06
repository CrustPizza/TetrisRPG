#include "stdafx.h"
#include "progressBar.h"

HRESULT progressBar::init(string frontKey, const char* frontImageKey, int frontX, int frontY, int frontWidth, int frontHeight, string backKey, const char* backImageKey, int backX, int backY, int backWidth, int backHeight)
{
	//키값으로 이미지이름(~.bmp)로 바로 초기화
	char frontImage[128];
	char backImage[128] = { 0 };
	//메모리 깔끔하게 밀어주기
	ZeroMemory(frontImage, sizeof(frontImage));
	//~.bmp로 만들기
	sprintf(frontImage, "%s.bmp", frontImageKey);
	sprintf(backImage, "%s.bmp", backImageKey);

	//체력바 이미지 초기화
	_progressBarFront = IMAGEMANAGER->addImage(frontKey, frontImage, frontX, frontY, frontWidth, frontHeight, true, RGB(255, 0, 255));
	_progressBarBack = IMAGEMANAGER->addImage(backKey, backImage, backX, backY, backWidth, backHeight, true, RGB(255, 0, 255));

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
	//렌더링 되는 순서에 의해서 렌더가 되니까 피통부터 렌더 시킨다
	_progressBarBack->render(getMemDC(), _progressBarBack->getX(), _progressBarBack->getY());
	//앞에 보여지는 체력바 이미지
	_progressBarFront->render(getMemDC(), _progressBarFront->getX(), _progressBarFront->getY(),
		0, 0, _currentProgress, _progressBarFront->getHeight());
}

void progressBar::setGauge(float currentHp, float maxHp)
{
	_currentProgress = (currentHp / maxHp) * _progressBarFront->getWidth();
}
