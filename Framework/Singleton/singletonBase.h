#pragma once

template <class T>
class singletonBase
{
protected:
	// 싱글톤 객체 선언
	static T* singleton;

	singletonBase() {}
	~singletonBase() {}
public:
	// 싱글톤 객체 가져오기
	static T* getSingleton();
	// 싱글톤 객체 해제하기
	void releaseSingleton();
};

// 초기화
template<class T>
T* singletonBase<T>::singleton = 0;

// 싱글톤 객체 가져오기
template<class T>
inline T * singletonBase<T>::getSingleton()
{
	// 싱글톤이 없으면 새로 생성
	if (!singleton) singleton = new T;
		return singleton;
}

// 싱글톤 객체 해제하기
template<class T>
inline void singletonBase<T>::releaseSingleton()
{
	// 싱글톤이 있다면 메모리에서 해제
	if (singleton)
	{
		delete singleton;
		singleton = NULL;
	}
}
