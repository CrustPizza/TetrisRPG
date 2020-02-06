#pragma once
#include "gameNode.h"
//=============================================================
//	## progressBar ## (���α׷����� == ü�¹�)
//=============================================================
class progressBar : public gameNode
{
private:
	image*	 _progressBarFront;	//ü�¹� �� �̹���
	image*	 _progressBarBack;	//ü�¹� �� �̹���

	int		_currentProgress;

public:
	//ü�¹� �ʱ�ȭ(���̹���Ű, ���̹���Ű, x, y, ���α���, ���α���)
	HRESULT init(string frontKey, const char* frontImageKey, int frontX, int frontY, int frontWidth, int frontHeight, string backKey, const char* backImageKey, int backX, int backY, int backWidth, int backHeight);
	void release();
	void update();
	void render();

	//ü�¹� ������ �����ϱ�
	void setGauge(float currentHp, float maxHp);

	progressBar() {}
	~progressBar() {}
};

