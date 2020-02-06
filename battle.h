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
	// �÷��̾�
	player* _player;
	bool _evasion;
	bool _attack;
	int _playerCenterX;

	// ��Ʈ����
	tetris* _tetris;

	// �ɼ�
	option* _option;

	// �κ��丮
	inventory* _inventory;

	// ��ų
	skill* _skill;

	// ���ʹ�
	enemy* _enemy;
	tagStone* _enemyUnit;
	int _enemyFrameX;
	int _enemyFrameY;

	// ������
	vector<tagDamage> _damage;
	int _atkBuff;
	int _atkDebuff;
	HBRUSH _red;

	// ��� UI
	image* _bg;

	// ����
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

	// ���� �̹���
	tagBuff _buff[4];

	// ȭ����ȯ
	image* _screenOut;
	bool _screenChange;

	// ����
	float _effectVolume;

	// ����
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