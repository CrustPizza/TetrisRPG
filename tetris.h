#pragma once
#include "gameNode.h"
#include "option.h"

#define WIDTH 12
#define HEIGHT 22
#define BOARD_SIZE (WIDTH * HEIGHT)
#define STAY_DELAY 400

#define SPECIAL_BLOCK_PERCENT 10

// Ư����
enum tagSpecial
{
	ATK_BUFF,
	ATK_DEBUFF,
	POISON,
	RECOVERY
};

// ��Ʈ���� ����
struct tagBoard
{
	RECT rc;
	bool block;
	bool wall;
	int color;
	int special;
};

struct tagBlock
{
	vector<vector<bool>> block;
	int color;
	int rotationCount;
	int special;
	POINT specialIndex;
};

struct tagCombo
{
	int count;
	image* img;
	ULONGLONG timer;
	int line;
};

class tetris : public gameNode
{
private:
	// ���� 2���� �迭
	tagBoard	_board[HEIGHT][WIDTH];

	// �������� ����
	tagBlock	_controlBlock;
	int			_idx;
	int			_idy;
	int			_ghostY;

	// �޺�
	tagCombo	_combo;

	// �� �̹�����
	image*		_blue;
	image*		_red;
	image*		_grey;
	image*		_green;
	image*		_yellow;
	image*		_emerald;
	image*		_brown;
	image*		_pink;
	image*		_purple;
	image*		_atkBuff;
	image*		_atkDebuff;
	image*		_poison;
	image*		_recovery;

	// ���� �� �� ���� ��
	tagBlock	_nextBlock;
	tagBlock	_holdBlock;
	bool		_hold;

	// ���� Ÿ�̸�
	ULONGLONG	_atkBuffTimer;
	ULONGLONG	_atkDebuffTimer;
	ULONGLONG	_poisonTimer;
	ULONGLONG	_recoveryTimer;

	// �� �̵� Ÿ�̸�
	ULONGLONG	_timer;
	ULONGLONG	_downTimer;
	int			_stayCount;

	// ���� ����
	bool		_gameover;
	int			_overLine;
	bool		_blockDown;
	ULONGLONG	_overTimer;
	int			_resetCount;
	float		_numberScale;

	// �ɼ�
	option* _option;

	// ��ų
	bool _skillOn;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	// �� �ޱ�
	tagBlock getNextBlock() { return _nextBlock; }
	tagBlock getHoldBlock() { return _holdBlock; }
	tagCombo getCombo() { return _combo; }

	// ���� ���� �ð� �־ ���� ���� �ð� �̳��� ��� true��ȯ
	bool getAtkBuff(int time);
	bool getAtkDebuff(int time);
	bool getPoison(int time);
	bool getRecovery(int time);

	// ���� �ð� Ȯ��
	int getAtkBuffTime() { return GetTickCount64() - _atkBuffTimer; }
	int getAtkDebuffTime() { return GetTickCount64() - _atkDebuffTimer; }
	int getPoisonTime() { return GetTickCount64() - _poisonTimer; }
	int getRecoveryTime() { return GetTickCount64() - _recoveryTimer; }

	// ���� �̹���
	image* getAtkBuffImg() { return _atkBuff; }
	image* getAtkDebuffImg() { return _atkDebuff; }
	image* getPoisonImg() { return _poison; }
	image* getRecoveryImg() { return _recovery; }

	// �� ����
	void makeBlock();

	// �� Ȧ��
	void holdBlock();

	// ���� ����׸���
	void blockColor(int x, int y, int color, BYTE alpha = 255);

	// �浹 Ȯ��
	bool checkCrush(tagDirection dir);

	// �� �̵�
	bool moveBlock(tagDirection dir);

	// �� ȸ��
	bool blockRotation();

	// �޺�
	void comboRender(int x, int y);

	void printNumber(int num, int x, int y, float scale = 1.0f);

	// ���� ��, Ȧ�� �� ���
	void nextBlockRender(int x, int y);
	void holdBlockRender(int x, int y);

	// ��ųOn
	bool* getSkillOnPtr() { return &_skillOn; }

	tetris() : _option(nullptr) {}
	~tetris() {}
};