#pragma once
#include "gameNode.h"
#include "option.h"

#define WIDTH 12
#define HEIGHT 22
#define BOARD_SIZE (WIDTH * HEIGHT)
#define STAY_DELAY 400

#define SPECIAL_BLOCK_PERCENT 10

// 특수블럭
enum tagSpecial
{
	ATK_BUFF,
	ATK_DEBUFF,
	POISON,
	RECOVERY
};

// 테트리스 보드
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
	// 보드 2차원 배열
	tagBoard	_board[HEIGHT][WIDTH];

	// 조종중인 블럭값
	tagBlock	_controlBlock;
	int			_idx;
	int			_idy;
	int			_ghostY;

	// 콤보
	tagCombo	_combo;

	// 블럭 이미지들
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

	// 다음 블럭 및 고정 블럭
	tagBlock	_nextBlock;
	tagBlock	_holdBlock;
	bool		_hold;

	// 버프 타이머
	ULONGLONG	_atkBuffTimer;
	ULONGLONG	_atkDebuffTimer;
	ULONGLONG	_poisonTimer;
	ULONGLONG	_recoveryTimer;

	// 블럭 이동 타이머
	ULONGLONG	_timer;
	ULONGLONG	_downTimer;
	int			_stayCount;

	// 게임 오버
	bool		_gameover;
	int			_overLine;
	bool		_blockDown;
	ULONGLONG	_overTimer;
	int			_resetCount;
	float		_numberScale;

	// 옵션
	option* _option;

	// 스킬
	bool _skillOn;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	// 블럭 받기
	tagBlock getNextBlock() { return _nextBlock; }
	tagBlock getHoldBlock() { return _holdBlock; }
	tagCombo getCombo() { return _combo; }

	// 버프 유지 시간 넣어서 버프 유지 시간 이내일 경우 true반환
	bool getAtkBuff(int time);
	bool getAtkDebuff(int time);
	bool getPoison(int time);
	bool getRecovery(int time);

	// 버프 시간 확인
	int getAtkBuffTime() { return GetTickCount64() - _atkBuffTimer; }
	int getAtkDebuffTime() { return GetTickCount64() - _atkDebuffTimer; }
	int getPoisonTime() { return GetTickCount64() - _poisonTimer; }
	int getRecoveryTime() { return GetTickCount64() - _recoveryTimer; }

	// 버프 이미지
	image* getAtkBuffImg() { return _atkBuff; }
	image* getAtkDebuffImg() { return _atkDebuff; }
	image* getPoisonImg() { return _poison; }
	image* getRecoveryImg() { return _recovery; }

	// 블럭 생성
	void makeBlock();

	// 블럭 홀드
	void holdBlock();

	// 블럭별 색상그리기
	void blockColor(int x, int y, int color, BYTE alpha = 255);

	// 충돌 확인
	bool checkCrush(tagDirection dir);

	// 블럭 이동
	bool moveBlock(tagDirection dir);

	// 블럭 회전
	bool blockRotation();

	// 콤보
	void comboRender(int x, int y);

	void printNumber(int num, int x, int y, float scale = 1.0f);

	// 다음 블럭, 홀드 블럭 출력
	void nextBlockRender(int x, int y);
	void holdBlockRender(int x, int y);

	// 스킬On
	bool* getSkillOnPtr() { return &_skillOn; }

	tetris() : _option(nullptr) {}
	~tetris() {}
};