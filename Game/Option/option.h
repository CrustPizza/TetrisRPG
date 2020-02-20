#pragma once
#include "gameNode.h"

struct tagButton
{
	image* img;
	bool sound;
};

// 키 목록
struct tagKey
{
	int left;
	int right;
	int up;
	int down;
	int hold;
	int drop;
	int skillSlot1;
	int skillSlot2;
	int itemSlot1;
	int itemSlot2;
};

class option : public gameNode
{
private:
	tagKey _keySet;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	// 키값 바꿀때 쓰는 함수
	bool keyChange(int type);
	bool setKey(int type, int key);
	bool keyCheck(bool change, int key);
	void keyRender(int x, int y, int key);

	// 각 키값 받기
	int getLeft() { return _keySet.left; }
	int getRight() { return _keySet.right; }
	int getUp() { return _keySet.up; }
	int getDown() { return _keySet.down; }
	int getHold() { return _keySet.hold; }
	int getDrop() { return _keySet.drop; }
	int getSkillSlot1() { return _keySet.skillSlot1; }
	int getSkillSlot2() { return _keySet.skillSlot2; }
	int getItemSlot1() { return _keySet.itemSlot1; }
	int getItemSlot2() { return _keySet.itemSlot2; }

	// 키값 설정하기
	void setLeft(int key) { _keySet.left = key; }
	void setRight(int key) { _keySet.right = key; }
	void setUp(int key) { _keySet.up = key; }
	void setDown(int key) { _keySet.down = key; }
	void setHold(int key) { _keySet.hold = key; }
	void setDrop(int key) { _keySet.drop = key; }
	void setSkillSlot1(int _skill) { _keySet.skillSlot1 = _skill; }
	void setSkillSlot2(int _skill) { _keySet.skillSlot2 = _skill; }
	void setItemSlot1(int _item) { _keySet.itemSlot2 = _item; }
	void setItemSlot2(int _item) { _keySet.itemSlot2 = _item; }

	bool crushButton(tagButton* button, int activate, int deactivate);

	void save(string fileName);
	void load(string fileName);
};
