#include "stdafx.h"
#include "soundManager.h"

HRESULT soundManager::init(void)
{
	// FMOD 시스템을 생성
	System_Create(&_system);

	// 사운드, 채널수 설정
	_system->init(SOUNDBUFFER, FMOD_INIT_NORMAL, 0);

	// 사운드, 채널 클래스 동적할당
	_sound = new Sound*[SOUNDBUFFER];
	_channel = new Channel*[SOUNDBUFFER];

	// 메모리 초기화
	memset(_sound, 0, sizeof(Sound*) * SOUNDBUFFER);
	memset(_channel, 0, sizeof(Channel*) * SOUNDBUFFER);

	return S_OK;
}

void soundManager::release(void)
{
	// 사운드 및 채널 삭제
	if (_sound != NULL || _channel != NULL)
	{
		for (int i = 0; i < SOUNDBUFFER; i++)
		{
			if (_channel != NULL)
			{
				if (_channel[i]) _channel[i]->stop();
			}
			if (_sound != NULL)
			{
				if (_sound[i]) _sound[i]->release();
			}
		}
	}

	// 메모리 지우기
	SAFE_DELETE_ARRAY(_sound);
	SAFE_DELETE_ARRAY(_channel);

	// 시스템 닫기
	if (_system != NULL)
	{
		_system->release();
		_system->close();
	}
}

void soundManager::update(void)
{
	_system->update();
}

void soundManager::addSound(string keyName, string soundName, bool bgm, bool loop)
{
	// 반복 여부
	if (loop)
	{
		// 용량이 큰 BGM의 경우 등록해놓고 사용하고 아닌 경우에는 매번 불러와서 쓴다
		if (bgm)
		{
			_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSound.size()]);
		}
		else
		{
			_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSound.size()]);
		}
	}
	else 
	{
		_system->createSound(soundName.c_str(), FMOD_DEFAULT, 0, &_sound[_mTotalSound.size()]);
	}

	// 맵에 정보 저장
	_mTotalSound.insert(make_pair(keyName, &_sound[_mTotalSound.size()]));

}

void soundManager::play(string keyName, float volume)
{
	int count = 0;
	arrSoundIter iter = _mTotalSound.begin();
	
	for (; iter != _mTotalSound.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//사운드 플레이
			_system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &_channel[count]);
			//볼륨세팅
			_channel[count]->setVolume(volume);
		}
	}
}

void soundManager::stop(string keyName)
{
	int count = 0;
	arrSoundIter iter = _mTotalSound.begin();

	for (; iter != _mTotalSound.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//사운드 정지
			_channel[count]->stop();
		}
	}
}

void soundManager::pause(string keyName)
{
	int count = 0;
	arrSoundIter iter = _mTotalSound.begin();

	for (; iter != _mTotalSound.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//사운드 일시정지
			_channel[count]->setPaused(true);
			break;
		}
	}
}

void soundManager::resume(string keyName)
{
	int count = 0;
	arrSoundIter iter = _mTotalSound.begin();

	for (iter; iter != _mTotalSound.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//사운드 다시재생
			_channel[count]->setPaused(false);
			break;
		}
	}
}

bool soundManager::isPlaySound(string keyName)
{
	bool isPlay;
	int count = 0;
	arrSoundIter iter = _mTotalSound.begin();

	for (iter; iter != _mTotalSound.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//사운드 플레이중인지 확인
			_channel[count]->isPlaying(&isPlay);
			break;
		}
	}

	return isPlay;
}

bool soundManager::isPauseSound(string keyName)
{
	bool isPause;
	int count = 0;
	arrSoundIter iter = _mTotalSound.begin();
	for (iter; iter != _mTotalSound.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//사운드 일시정지중인지 확인
			_channel[count]->getPaused(&isPause);
			break;
		}
	}

	return isPause;
}