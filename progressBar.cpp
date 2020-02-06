#include "stdafx.h"
#include "progressBar.h"

HRESULT progressBar::init(string frontKey, const char* frontImageKey, int frontX, int frontY, int frontWidth, int frontHeight, string backKey, const char* backImageKey, int backX, int backY, int backWidth, int backHeight)
{
	//Ű������ �̹����̸�(~.bmp)�� �ٷ� �ʱ�ȭ
	char frontImage[128];
	char backImage[128] = { 0 };
	//�޸� ����ϰ� �о��ֱ�
	ZeroMemory(frontImage, sizeof(frontImage));
	//~.bmp�� �����
	sprintf(frontImage, "%s.bmp", frontImageKey);
	sprintf(backImage, "%s.bmp", backImageKey);

	//ü�¹� �̹��� �ʱ�ȭ
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
	//������ �Ǵ� ������ ���ؼ� ������ �Ǵϱ� ������� ���� ��Ų��
	_progressBarBack->render(getMemDC(), _progressBarBack->getX(), _progressBarBack->getY());
	//�տ� �������� ü�¹� �̹���
	_progressBarFront->render(getMemDC(), _progressBarFront->getX(), _progressBarFront->getY(),
		0, 0, _currentProgress, _progressBarFront->getHeight());
}

void progressBar::setGauge(float currentHp, float maxHp)
{
	_currentProgress = (currentHp / maxHp) * _progressBarFront->getWidth();
}
