#pragma once
#include "gameNode.h"
#include "player.h"
#include "inventory.h"
#include "shop.h"
#include "option.h"

#define STAGE_MAX 5
#define KEY_Y 65
#define FUNCTION_KEY_AMOUNT 10

enum tagMenu
{
	OPTION,
	KEYPAD,
	QUIT
};

class main : public gameNode
{
private:
	// �÷��̾�
	player*			_player;

	// �κ��丮
	inventory*		_inventory;
	bool			_inventoryOpen;

	// ��� UI
	image*			_bg;
	int				_loopY;

	// ����
	image*			_tetrisBoard;
	image*			_fieldGlass;
	image*			_room;

	// ĳ����â
	tagButton		_character;

	// ����
	tagButton		_battleButton;
	vector<RECT>	_stageButton;
	bool			_battleOpen;
	image*			_stage;
	image*			_stageBoard;
	image*			_screenOut;
	bool            _screenChange;

	// ����
	tagButton		_shopButton;
	shop*			_shop;
	bool			_shopOpen;
	bool			_notEnoughGold;
	int				_goldTimer;

	// �ɼ�
	tagButton		_option;
	image*			_popUp;
	bool			_popOn;
	int				_popX;
	int				_popY;
	int				_popSpeed;
	tagButton		_bgmSound;
	tagButton		_effectSound;
	tagButton		_keypad;

	// Ű
	image*			_keyBoard;
	image*			_dirFront;
	image*			_dirBack;
	bool			_keyOn;
	int				_keyChange;
	int				_keyX;
	int				_keyY;
	int				_keySpeed;
	int				_keySave;
	RECT			_keyChangeRc[FUNCTION_KEY_AMOUNT];

	// ����
	option*			_optionClass;
	tagButton		_exit;
	image*			_ask;
	bool			_askOn;
	int				_askX;
	int				_askY;
	int				_askSpeed;
	tagButton		_okButton;
	tagButton		_closeButton;

	// ��Ʈ
	HFONT			_bigFont;
	HFONT			_smallFont;
	HFONT			_oldFont;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	// �޴� ������ �����ϴ� �Լ�
	void moveBoard(tagMenu menu);

	main() {}
	~main() {}
};