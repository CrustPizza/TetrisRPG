#include "stdafx.h"
#include "iniData.h"

HRESULT iniData::init()
{
	return S_OK;
}

void iniData::release()
{
}

void iniData::addData(const char * section, const char * key, const char * value)
{
	//ini데이터 구조체 선언후 초기화
	tagIniData data;

	// 데이터 정보 담기
	data.section = (char*)section;
	data.key = (char*)key;
	data.data = (char*)value;

	//벡터에 ini데이터 구조체 저장
	_vIniData.push_back(data);
}

void iniData::saveINI(const char * fileName)
{
	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));
	
	// 폴더주소 + 파일명
	sprintf(str, "\\%s.ini", fileName);
	GetCurrentDirectory(256, dir);
	strcat(dir, str);

	// 벡터에 등록된 정보 파일로 저장
	for (int i = 0; i < _vIniData.size(); i++)
	{
		WritePrivateProfileString(_vIniData[i].section, _vIniData[i].key, _vIniData[i].data, dir);
	}

	_vIniData.clear();
}

const char * iniData::loadDataString(const char * fileName, const char * section, const char * key)
{
	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));
	
	// 폴더주소 + 파일명
	sprintf(str, "\\%s.ini", fileName);
	GetCurrentDirectory(256, dir);
	strcat(dir, str);

	// 문자열로 데이터 불러오기
	char data[64] = { NULL };
	GetPrivateProfileString(section, key, "", data, 64, dir);

	return data;
}

int iniData::loadDataInteger(const char * fileName, const char * section, const char * key)
{
	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));
	
	// 폴더주소 + 파일명
	sprintf(str, "\\%s.ini", fileName);
	GetCurrentDirectory(256, dir);
	strcat(dir, str);

	// 인트형으로 데이터 불러오기
	return GetPrivateProfileInt(section, key, 0, dir);
}
