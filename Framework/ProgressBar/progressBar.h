#pragma once
#include "gameNode.h"

class progressBar : public gameNode
{
private:
	image*	 _progressBarFront;	// 바 앞 이미지
	image*	 _progressBarBack;	// 바 뒤 이미지

	int	_currentProgress;

public:
	// 바 초기화(앞이미지키, 백이미지키, x, y, 가로길이, 세로길이)
	HRESULT init(string frontKey, const char* frontImageKey, int frontX, int frontY, int frontWidth, int frontHeight, string backKey, const char* backImageKey, int backX, int backY, int backWidth, int backHeight);
	void release();
	void update();
	void render();

	// 바 게이지 세팅하기
	void setGauge(float currentHp, float maxHp);

	progressBar() {}
	~progressBar() {}
};

