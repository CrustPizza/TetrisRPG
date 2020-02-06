#pragma once
#include "gameNode.h"
#include "player.h"
#include "inventory.h"
#include "tetris.h"
#include "enemy.h"
#include "option.h"
#include "skill.h"

#define ATK_BUFF 50

enum tagUnit
{
	NONE,
	PLAYER,
	STONE
};

struct tagDamage
{
	int damage;
	int x;
	int y;
	BYTE alpha;
};

struct tagBuff
{
	int x;
	int y;
	image* img;
	BYTE alpha;
	int count;
};

class battle : public gameNode
{
private:
	// 플레이어
	player* _player;
	bool _evasion;
	bool _attack;
	int _playerCenterX;

	// 테트리스
	tetris* _tetris;

	// 옵션
	option* _option;

	// 인벤토리
	inventory* _inventory;

	// 스킬
	skill* _skill;

	// 에너미
	enemy* _enemy;
	tagStone* _enemyUnit;
	int _enemyFrameX;
	int _enemyFrameY;

	// 데미지
	vector<tagDamage> _damage;
	int _atkBuff;
	int _atkDebuff;
	HBRUSH _red;

	// 배경 UI
	image* _bg;

	// 보드
	image* _tetrisBoard;
	image* _fieldGlass;
	image* _room;
	image* _nextBlock;
	image* _holdBlock;
	image* _activeSlot;

	image* _rewardBoard;
	image* _goldReward;
	image* _goldCoin;
	image* _itemReward;
	tagButton _home;
	tagButton _replay;
	int speed;

	// 버프 이미지
	tagBuff _buff[4];

	// 화면전환
	image* _screenOut;
	bool _screenChange;

	// 사운드
	float _effectVolume;

	// 종료
	bool _battleEnd;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void setPlayer(player* playerptr) { _player = playerptr; }

	void printNumber(int num, int x, int y, BYTE alpha);

	battle() : _player(nullptr), 
			_enemy(nullptr), 
			_tetris(nullptr), 
			_inventory(nullptr), 
			_option(nullptr), 
			_skill(nullptr) {}
	~battle() {}
};