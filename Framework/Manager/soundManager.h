#pragma once
#include "singletonBase.h"
/*FMOD 사용하기 위해 라이브러리 추가*/
#include "SOUND/inc/fmod.hpp"
#pragma comment (lib, "SOUND/lib/fmodex_vc.lib")
using namespace FMOD;

// 사용할 사운드 버퍼수
#define SOUNDBUFFER 100

class soundManager : public singletonBase<soundManager>
{
private:
	typedef map<string, Sound**> arrSound;
	typedef map<string, Sound**>::iterator arrSoundIter;

private:
	System*		_system;		// 시스템 클래스
	Sound** 	_sound;			// 사운드 클래스
	Channel**	_channel;		// 채널 클래스

	arrSound	_mTotalSound;	// 사운드 담을 맵

	float		_effectVolume;	// 효과음 볼륨

public:
	HRESULT init(void);
	void release(void);
	void update(void);

	// 사운드 추가
	void addSound(string keyName, string soundName, bool bgm = false, bool loop = false);
	// 사운드 재생
	void play(string keyName, float volume = 1.0f); //0.0f(Min) ~ 1.0f(Max)
	// 사운드 정지
	void stop(string keyName);
	// 사운드 일시정지
	void pause(string keyName);
	// 사운드 다시재생
	void resume(string keyName);
	// 플레이중인가
	bool isPlaySound(string keyName);
	// 일시정지중인가
	bool isPauseSound(string keyName);

	// 볼륨 겟 셋
	void setEffectVolume(float volume) { _effectVolume = volume; }
	float getEffectVolume() { return _effectVolume; }

	soundManager() : _system(NULL), _sound(NULL), _channel(NULL) {}
	~soundManager() {}
};