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
	// 플레이어
	player*			_player;

	// 인벤토리
	inventory*		_inventory;
	bool			_inventoryOpen;

	// 배경 UI
	image*			_bg;
	int			_loopY;

	// 보드
	image*			_tetrisBoard;
	image*			_fieldGlass;
	image*			_room;

	// 캐릭터창
	tagButton		_character;

	// 전투
	tagButton		_battleButton;
	vector<RECT>		_stageButton;
	bool			_battleOpen;
	image*			_stage;
	image*			_stageBoard;
	image*			_screenOut;
	bool         		_screenChange;

	// 상점
	tagButton		_shopButton;
	shop*			_shop;
	bool			_shopOpen;
	bool			_notEnoughGold;
	int			_goldTimer;

	// 옵션
	tagButton		_option;
	image*			_popUp;
	bool			_popOn;
	int			_popX;
	int			_popY;
	int			_popSpeed;
	tagButton		_bgmSound;
	tagButton		_effectSound;
	tagButton		_keypad;

	// 키
	image*			_keyBoard;
	image*			_dirFront;
	image*			_dirBack;
	bool			_keyOn;
	int			_keyChange;
	int			_keyX;
	int			_keyY;
	int			_keySpeed;
	int			_keySave;
	RECT			_keyChangeRc[FUNCTION_KEY_AMOUNT];

	// 종료
	option*			_optionClass;
	tagButton		_exit;
	image*			_ask;
	bool			_askOn;
	int			_askX;
	int			_askY;
	int			_askSpeed;
	tagButton		_okButton;
	tagButton		_closeButton;

	// 폰트
	HFONT			_bigFont;
	HFONT			_smallFont;
	HFONT			_oldFont;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	// 메뉴 등장모션 설정하는 함수
	void moveBoard(tagMenu menu);

	main() {}
	~main() {}
};
