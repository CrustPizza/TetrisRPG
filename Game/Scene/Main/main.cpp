#include "stdafx.h"
#include "main.h"

HRESULT main::init()
{
	// UI 이미지 등록
	_bg = IMAGEMANAGER->findImage("MenuBackGround");
	_tetrisBoard = IMAGEMANAGER->findImage("TetrisBoard");
	_fieldGlass = IMAGEMANAGER->findImage("FieldGlass");
	_room = IMAGEMANAGER->findImage("Room1");
	
	_character.img = IMAGEMANAGER->findImage("Character");
	_battleButton.img = IMAGEMANAGER->findImage("Battle");
	_shopButton.img = IMAGEMANAGER->findImage("Shop");
	_option.img = IMAGEMANAGER->findImage("Option");
	_exit.img = IMAGEMANAGER->findImage("Exit");

	_popUp = IMAGEMANAGER->findImage("PopUp");
	_bgmSound.img = IMAGEMANAGER->findImage("BgSound");
	_effectSound.img = IMAGEMANAGER->findImage("EffectSound");
	_keypad.img = IMAGEMANAGER->findImage("Keypad");

	_ask = IMAGEMANAGER->findImage("AskBoard");
	_okButton.img = IMAGEMANAGER->findImage("Ok");
	_closeButton.img = IMAGEMANAGER->findImage("Close");

	_keyBoard = IMAGEMANAGER->findImage("KeyBoard");
	_dirFront = IMAGEMANAGER->findImage("DirKeyFront");
	_dirBack = IMAGEMANAGER->findImage("DirKeyBack");

	_screenOut = IMAGEMANAGER->findImage("ScreenOut");

	// 플레이어
	_player = new player;
	_player->init();
	_player->load();

	// 인벤토리
	_inventory = new inventory;
	_inventory->init(_tetrisBoard->getX(), _tetrisBoard->getY(), _tetrisBoard->getWidth(), _tetrisBoard->getHeight());
	_inventoryOpen = true;

	// 전투
	_battleButton.img = IMAGEMANAGER->findImage("Battle");
	_stage = IMAGEMANAGER->findImage("Stage");
	_stageBoard = IMAGEMANAGER->findImage("StageBoard");
	_battleOpen = false;

	for (int i = 0; i < STAGE_MAX; i++)
	{
		_stageButton.push_back(RectMake(_tetrisBoard->getX() + 60, _tetrisBoard->getY() + 20 * (i + 1) + _stageBoard->getHeight() * i, _stageBoard->getWidth(), _stageBoard->getHeight()));
	}

	// 상점
	_shop = new shop;
	_shop->init(_tetrisBoard->getX(), _tetrisBoard->getY(), _tetrisBoard->getWidth(), _tetrisBoard->getHeight(), _inventory);
	_shopOpen = false;
	_notEnoughGold = false;
	_goldTimer = GetTickCount64();

	// 버튼 사운드 활성화
	_character.sound = true;
	_shopButton.sound = true;
	_option.sound = true;
	_exit.sound = true;

	_bgmSound.sound = true;
	_effectSound.sound = true;
	_keypad.sound = true;
	_okButton.sound = true;
	_closeButton.sound = true;

	// 루프
	_loopY = 0;

	// 옵션창 초기화
	_popOn = false;
	_popX = (WINSIZEX - _popUp->getWidth()) / 2;
	_popY = WINSIZEY;
	_popSpeed = 400;

	// 종료창 초기화
	_askOn = false;
	_askX = (WINSIZEX - _ask->getWidth()) / 2;
	_askY = WINSIZEY;
	_askSpeed = 400;

	// 키입력 초기화
	_keyOn = false;
	_keyX = (WINSIZEX - _keyBoard->getWidth()) / 2;
	_keyY = WINSIZEY;
	_keySpeed = 400;
	_keyChange = 0;

	// 화면전환
	_screenChange = false;

	// 배경음
	if (!SOUNDMANAGER->isPlaySound("MainBgm"))
		SOUNDMANAGER->play("MainBgm");

	if (SOUNDMANAGER->isPauseSound("BattleBgm"))
		SOUNDMANAGER->pause("MainBgm");

	SOUNDMANAGER->stop("BattleBgm");

	// 옵션
	_optionClass = new option;
	_optionClass->init();

	// 폰트
	SetBkMode(getMemDC(), TRANSPARENT);
	_bigFont = CreateFont(60, 0, 0, 0, 500, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("배찌체"));
	_smallFont = CreateFont(30, 0, 0, 0, 500, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("배찌체"));

	return S_OK;
}

void main::release()
{
	_player->save();
	_player->release();
	SAFE_DELETE(_player);

	_inventory->save("inventory.inv");
	_inventory->release();
	SAFE_DELETE(_inventory);

	_shop->release();
	SAFE_DELETE(_shop);

	_optionClass->release();
	SAFE_DELETE(_optionClass);

	DeleteObject(_smallFont);
	DeleteObject(_bigFont);
	DeleteObject(_oldFont);
}

void main::update()
{
	// 씬 전환하기 위해 이미지를 출력하고 작업이 끝나면 전투씬을 불러온다
	if (_screenChange)
	{
		_screenOut->setY(_screenOut->getY() + 50);

		if (_screenOut->getY() >= -539)
		{
			this->release();
			SCENEMANAGER->loadScene("Battle");
			
			return;
		}
	}
	else if (_screenOut->getY() > WINSIZEY)
	{
		// 각 클래스 업데이트
		_player->update();
		_player->playerIdle();
		_shop->update();

		// 마우스 충돌시 프레임 바꾸기
		_optionClass->crushButton(&_character, 1, 0);
		_optionClass->crushButton(&_battleButton, 1, 0);
		_optionClass->crushButton(&_shopButton, 1, 0);
		_optionClass->crushButton(&_option, 1, 0);
		_optionClass->crushButton(&_exit, 1, 0);

		// 플레이어 이동
		if (_player->getImage()->getX() > _room->getX())
			_player->playerMove(LEFT);
		if (_player->getImage()->getX() + _player->getImage()->getFrameWidth() < _room->getX() + _room->getWidth() - 2)
			_player->playerMove(RIGHT);
		if (_player->getImage()->getY() > _room->getY() + 135)
			_player->playerMove(UP);
		if (_player->getImage()->getY() + _player->getImage()->getFrameHeight() < _room->getY() + _room->getHeight() - 2)
			_player->playerMove(DOWN);

		// 키값 교체
		if (_keyChange)
		{
			if (_optionClass->keyChange(_keyChange))
				_keyChange = 0;
		}

		// 키 변경 창을 닫을때 키값이 없는 변수가 있다면 초기화 시키고 없다면 키값을 저장한다.
		if (!_keyOn)
		{
			if (_optionClass->keyCheck(false, 7))
				_optionClass->init();
			else
				_optionClass->release();
		}

		// ESC 버튼을 눌렀을 경우 창이 열려있다면 닫고 아닐 경우 
		if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
		{
			if (!_popOn && !_keyOn && !_askOn && (_askSpeed == 400 || _askSpeed <= -10))
				_askOn = true;
			else
			{
				_popOn = false;
				_askOn = false;
				_keyOn = false;
			}

			// 클릭 효과음
			SOUNDMANAGER->play("Click", SOUNDMANAGER->getEffectVolume());
		}

		// 좌클릭
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			// 캐릭터창 버튼 눌렀을시
			if (PtInRect(&_character.img->boudingBoxWithFrame(), _ptMouse) && (_askSpeed == 400 || _askSpeed <= -10) && (_popSpeed == 400 || _popSpeed <= -10))
			{
				// 캐릭터 창을 연다, 기타 메뉴는 닫아준다
				_inventoryOpen = true;
				_battleOpen = false;
				_popOn = false;
				_askOn = false;
				_keyOn = false;
				_shopOpen = false;
			}

			// 전투 버튼 눌렀을시
			if (PtInRect(&_battleButton.img->boudingBoxWithFrame(), _ptMouse) && (_askSpeed == 400 || _askSpeed <= -10) && (_popSpeed == 400 || _popSpeed <= -10))
			{
				// 전투 창을 연다, 기타 메뉴는 닫아준다
				_battleOpen = true;
				_inventoryOpen = false;
				_popOn = false;
				_askOn = false;
				_keyOn = false;
				_shopOpen = false;
			}

			// 상점 버튼 눌렀을시
			if (PtInRect(&_shopButton.img->boudingBoxWithFrame(), _ptMouse) && (_askSpeed == 400 || _askSpeed <= -10) && (_popSpeed == 400 || _popSpeed <= -10))
			{
				// 상점 창을 연다, 기타 메뉴는 닫아준다
				_shopOpen = true;
				_battleOpen = false;
				_inventoryOpen = false;
				_popOn = false;
				_askOn = false;
				_keyOn = false;
			}

			// 옵션 버튼을 눌렀을시
			if (PtInRect(&_option.img->boudingBoxWithFrame(), _ptMouse) && (_popSpeed == 400 || _popSpeed <= -10))
			{
				// 열려있다면 닫고 닫혀있다면 연다, 옵션 메뉴는 닫아준다
				_popOn = !_popOn;
				_askOn = false;
				_keyOn = false;
			}

			// 종료 버튼을 눌렀을시
			if (PtInRect(&_exit.img->boudingBoxWithFrame(), _ptMouse) && (_askSpeed == 400 || _askSpeed <= -10))
			{
				// 열려있다면 닫고 닫혀있다면 연다, 종료 메뉴는 닫아준다
				_askOn = !_askOn;
				_popOn = false;
				_keyOn = false;
			}

			// 옵션창이 떠있을때
			if (_popOn)
			{
				// 배경음 버튼과 충돌했다면 배경음 On/Off를 조작한다
				if (PtInRect(&_bgmSound.img->boudingBoxWithFrame(), _ptMouse))
				{
					if (SOUNDMANAGER->isPauseSound("MainBgm"))
					{
						_bgmSound.img->setFrameX(0);
						SOUNDMANAGER->resume("MainBgm");
					}
					else
					{
						_bgmSound.img->setFrameX(1);
						SOUNDMANAGER->pause("MainBgm");
					}
				}

				// 효과음 버튼과 충돌했다면 효과음 On/Off를 조작한다
				if (PtInRect(&_effectSound.img->boudingBoxWithFrame(), _ptMouse))
				{
					if (SOUNDMANAGER->getEffectVolume())
					{
						_effectSound.img->setFrameX(1);
						SOUNDMANAGER->setEffectVolume(0.0f);
					}
					else
					{
						_effectSound.img->setFrameX(0);
						SOUNDMANAGER->setEffectVolume(1.0f);
					}
				}

				// 키 변경
				if (PtInRect(&_keypad.img->boudingBoxWithFrame(), _ptMouse))
				{
					_popOn = false;
					_keyOn = true;
				}

				// 닫기 버튼
				if (PtInRect(&_closeButton.img->boudingBoxWithFrame(), _ptMouse))
					_popOn = false;
			}

			// 종료시 다시 한번 확인하여 종료할 것인지 물어본다
			else if (_askOn)
			{
				// 확인을 눌렀을 경우 종료
				if (PtInRect(&_okButton.img->boudingBoxWithFrame(), _ptMouse))
					PostMessage(_hWnd, WM_DESTROY, 0, 0);

				// 취소를 누를경우 창 닫음
				if (PtInRect(&_closeButton.img->boudingBoxWithFrame(), _ptMouse))
					_askOn = false;
			}
			else if (_keyOn)
			{
				// 취소를 누를경우 창 닫음
				if (PtInRect(&_closeButton.img->boudingBoxWithFrame(), _ptMouse))
				{
					_keyOn = false;
					_popOn = true;
				}

				// 변경할 키값을 선택
				for (int i = 0; i < FUNCTION_KEY_AMOUNT; i++)
				{
					if (PtInRect(&_keyChangeRc[i], _ptMouse))
					{
						_keyChange = i + 1;
						_optionClass->setKey(_keyChange, 7);
						break;
					}
				}
			}
			else
			{
				// 인벤토리에서 아이템을 고를시
				if (_inventoryOpen)
				{
					// 물약의 경우 메인메뉴에서 사용하지 못하므로 제외한다.
					if (_inventory->selectItem(_ptMouse))
					{
						if (_inventory->getSelect().value.type != POTION)
						{
							_inventory->useItem(_ptMouse);

							// 이미 선택한 상태일 경우 selectItem에서 true를 반환하여 if문 안으로 들어오고 아이템을 장착한다.
							tagItemData buf = _player->equipItem(_inventory->getSelect().value.type, _inventory->getSelect().name);

							// 플레이어가 아이템을 장착중인 경우 아이템을 교체후 장착중이던 아이템은 인벤토리로 되돌린다
							if (buf.name != "Empty")
								_inventory->setItem(buf.name, buf.type);
						}
					}

					// 인벤토리에서 장비 벗을시
					if (_inventory->equipOff(_ptMouse, _player))
					{
						_player->equitOffItem(_inventory->getSelect().value.type);
					}
				}

				// 상점 열렸을때
				if (_shopOpen)
				{
					// 인벤토리의 아이템을 선택하고 이미 선택한 상태라면 아이템을 판매한다
					if (_inventory->selectItem(_ptMouse) && _inventory->useItem(_ptMouse))
					{
						_player->setGold(_player->getGold() + _inventory->getSelect().value.cost / 2);
					}

					RECT rc = _shop->selectList(_ptMouse).rc;
					tagItemData dataBuf = _shop->selectList(_ptMouse).data;

					// 상점 상품을 선택한 상태라면 소지금을 확인하고 아이템을 구매처리한다
					if (rc.left != 0)
					{
						if (rc.left == _inventory->getSelect().rc.left && rc.top == _inventory->getSelect().rc.top)
						{
							if (_player->getGold() >= dataBuf.cost)
							{
								if (_inventory->setItem(dataBuf.name, dataBuf.type))
								{
									_player->setGold(_player->getGold() - dataBuf.cost);
									_inventory->getSelectPtr()->rc = {};
									_shop->setBuySelect(false);
								}
							}
							else
							{
								_notEnoughGold = true;
								_goldTimer = GetTickCount64();
								_inventory->getSelectPtr()->select = true;
							}
						}
						else
						{
							_inventory->getSelectPtr()->rc = rc;
							_inventory->getSelectPtr()->value = dataBuf;
							_inventory->getSelectPtr()->select = true;
						}
					}
				}

				// 전투창 열렸을때
				if (_battleOpen)
				{
					// 스테이지를 선택하면 씬전환으로 넘어간다.
					for (int i = 0; i < _stageButton.size(); i++)
					{
						if (PtInRect(&_stageButton[i], _ptMouse))
						{
							_screenOut->setX(_screenOut->getX() - (i + 1));
							_screenOut->setY(-_screenOut->getHeight() - (i + 1));
							_screenChange = true;
							break;
						}
					}
				}
			}

			// 클릭 효과음
			SOUNDMANAGER->play("Click", SOUNDMANAGER->getEffectVolume());
		}

		// 옵션 및 종료창의 등장 및 퇴장 모션
		moveBoard(OPTION);
		moveBoard(KEYPAD);
		moveBoard(QUIT);
	}
	else
		_screenOut->setY(_screenOut->getY() + 50);

	// 배경 루프
	_loopY--;
}

void main::render()
{
	// UI 렌더
	// 배경
	_bg->loopRender(getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), 0, _loopY);

	// 캐릭터창
	_room->render(getMemDC(), _room->getX(), _room->getY());
	_fieldGlass->alphaRender(getMemDC(), _fieldGlass->getX(), _fieldGlass->getY(), 150);
	_player->render();

	// 테트리스창
	_tetrisBoard->alphaRender(getMemDC(), _tetrisBoard->getX(), _tetrisBoard->getY(), 150);

	// 인벤토리
	if (_inventoryOpen)
	{
		_inventory->printEquipment(_player);
		_inventory->render(_player);
	}

	// 상점
	if (_shopOpen)
	{
		_shop->render();
		_inventory->render(_player);
	}

	// 전투
	if (_battleOpen)
	{
		for (int i = 0; i < STAGE_MAX; i++)
		{
			_stageBoard->render(getMemDC(), _stageButton[i].left, _stageButton[i].top);
			_stage->render(getMemDC(), _stageButton[i].left + 10, _stageButton[i].top + 15);
			_inventory->printNumber(i + 1, _stageButton[i].left + 10 + _stage->getWidth(), _stageButton[i].top + 17, 1.4f);
		}
	}

	// 메뉴
	_character.img->frameRender(getMemDC(), _character.img->getX(), _character.img->getY());
	_battleButton.img->frameRender(getMemDC(), _battleButton.img->getX(), _battleButton.img->getY());
	_shopButton.img->frameRender(getMemDC(), _shopButton.img->getX(), _shopButton.img->getY());
	_option.img->frameRender(getMemDC(), _option.img->getX(), _option.img->getY());
	_exit.img->frameRender(getMemDC(), _exit.img->getX(), _exit.img->getY());
	
	// 옵션 UI
	if (_popY < WINSIZEY)
	{
		_popUp->render(getMemDC(), _popX, _popY);
		_bgmSound.img->frameRender(getMemDC(), _bgmSound.img->getX(), _bgmSound.img->getY());
		_effectSound.img->frameRender(getMemDC(), _effectSound.img->getX(), _effectSound.img->getY());
		_keypad.img->frameRender(getMemDC(), _keypad.img->getX(), _keypad.img->getY());
	}
	
	// 종료 UI
	if (_askY < WINSIZEY)
	{
		_ask->render(getMemDC(), _askX, _askY);
		_okButton.img->frameRender(getMemDC(), _okButton.img->getX(), _okButton.img->getY());
	}

	// 키 변경
	if (_keyY < WINSIZEY)
	{
		// 폰트 변경
		_oldFont = (HFONT)SelectObject(getMemDC(), _bigFont);
		_keyBoard->render(getMemDC(), _keyX, _keyY);
		
		SetTextColor(getMemDC(), RGB(0, 0, 0));
		TextOut(getMemDC(), _keyX + 50, _keyY + KEY_Y, "방향키", strlen("방향키"));
		TextOut(getMemDC(), _keyX + 50, _keyY + KEY_Y + 250, "기능키", strlen("기능키"));

		SetTextColor(getMemDC(), RGB(255, 255, 255));
		TextOut(getMemDC(), _keyX + 48, _keyY + KEY_Y - 2, "방향키", strlen("방향키"));
		TextOut(getMemDC(), _keyX + 48, _keyY + KEY_Y + 248, "기능키", strlen("기능키"));

		SelectObject(getMemDC(), _oldFont);

		// 키를 변경할 창을 띄운다
		for (int i = 0; i < FUNCTION_KEY_AMOUNT; i++)
			_dirFront->alphaRender(getMemDC(), _keyX + 38, _keyChangeRc[i].top, 150);

		for (int i = 0; i < FUNCTION_KEY_AMOUNT; i++)
			_dirBack->alphaRender(getMemDC(), _keyChangeRc[i].left, _keyChangeRc[i].top, 150);

		_oldFont = (HFONT)SelectObject(getMemDC(), _smallFont);

		SetTextColor(getMemDC(), RGB(0, 0, 0));
		TextOut(getMemDC(), _keyX + 55, _keyY + KEY_Y + 66, "위쪽", strlen("위쪽"));
		_optionClass->keyRender(_keyX + _dirFront->getWidth() + 45 + _dirBack->getWidth() / 2 - 1, _keyY + KEY_Y + 66, _optionClass->getUp());
		TextOut(getMemDC(), _keyX + 55, _keyY + KEY_Y + 111, "아래쪽", strlen("아래쪽"));
		_optionClass->keyRender(_keyX + _dirFront->getWidth() + 45 + _dirBack->getWidth() / 2 - 1, _keyY + KEY_Y + 111, _optionClass->getDown());
		TextOut(getMemDC(), _keyX + 55, _keyY + KEY_Y + 156, "왼쪽", strlen("왼쪽"));
		_optionClass->keyRender(_keyX + _dirFront->getWidth() + 45 + _dirBack->getWidth() / 2 - 1, _keyY + KEY_Y + 156, _optionClass->getLeft());
		TextOut(getMemDC(), _keyX + 55, _keyY + KEY_Y + 201, "오른쪽", strlen("오른쪽"));
		_optionClass->keyRender(_keyX + _dirFront->getWidth() + 45 + _dirBack->getWidth() / 2 - 1, _keyY + KEY_Y + 201, _optionClass->getRight());
		TextOut(getMemDC(), _keyX + 55, _keyY + KEY_Y + 316, "홀드", strlen("홀드"));
		_optionClass->keyRender(_keyX + _dirFront->getWidth() + 45 + _dirBack->getWidth() / 2 - 1, _keyY + KEY_Y + 316, _optionClass->getHold());
		TextOut(getMemDC(), _keyX + 55, _keyY + KEY_Y + 361, "드랍", strlen("드랍"));
		_optionClass->keyRender(_keyX + _dirFront->getWidth() + 45 + _dirBack->getWidth() / 2 - 1, _keyY + KEY_Y + 361, _optionClass->getDrop());
		TextOut(getMemDC(), _keyX + 55, _keyY + KEY_Y + 406, "스킬슬롯1", strlen("스킬슬롯1"));
		_optionClass->keyRender(_keyX + _dirFront->getWidth() + 45 + _dirBack->getWidth() / 2 - 1, _keyY + KEY_Y + 406, _optionClass->getSkillSlot1());
		TextOut(getMemDC(), _keyX + 55, _keyY + KEY_Y + 451, "스킬슬롯2", strlen("스킬슬롯2"));
		_optionClass->keyRender(_keyX + _dirFront->getWidth() + 45 + _dirBack->getWidth() / 2 - 1, _keyY + KEY_Y + 451, _optionClass->getSkillSlot2());
		TextOut(getMemDC(), _keyX + 55, _keyY + KEY_Y + 499, "아이템슬롯1", strlen("아이템슬롯1"));
		_optionClass->keyRender(_keyX + _dirFront->getWidth() + 45 + _dirBack->getWidth() / 2 - 1, _keyY + KEY_Y + 499, _optionClass->getItemSlot1());
		TextOut(getMemDC(), _keyX + 55, _keyY + KEY_Y + 544, "아이템슬롯2", strlen("아이템슬롯2"));
		_optionClass->keyRender(_keyX + _dirFront->getWidth() + 45 + _dirBack->getWidth() / 2 - 1, _keyY + KEY_Y + 544, _optionClass->getItemSlot2());

		SetTextColor(getMemDC(), RGB(255, 255, 255));
		TextOut(getMemDC(), _keyX + 53, _keyY + KEY_Y + 65, "위쪽", strlen("위쪽"));
		_optionClass->keyRender(_keyX + _dirFront->getWidth() + 45 + _dirBack->getWidth() / 2 + 1, _keyY + KEY_Y + 65, _optionClass->getUp());
		TextOut(getMemDC(), _keyX + 53, _keyY + KEY_Y + 110, "아래쪽", strlen("아래쪽"));
		_optionClass->keyRender(_keyX + _dirFront->getWidth() + 45 + _dirBack->getWidth() / 2 + 1, _keyY + KEY_Y + 110, _optionClass->getDown());
		TextOut(getMemDC(), _keyX + 53, _keyY + KEY_Y + 155, "왼쪽", strlen("왼쪽"));
		_optionClass->keyRender(_keyX + _dirFront->getWidth() + 45 + _dirBack->getWidth() / 2 + 1, _keyY + KEY_Y + 155, _optionClass->getLeft());
		TextOut(getMemDC(), _keyX + 53, _keyY + KEY_Y + 200, "오른쪽", strlen("오른쪽"));
		_optionClass->keyRender(_keyX + _dirFront->getWidth() + 45 + _dirBack->getWidth() / 2 + 1, _keyY + KEY_Y + 200, _optionClass->getRight());
		TextOut(getMemDC(), _keyX + 53, _keyY + KEY_Y + 315, "홀드", strlen("홀드"));
		_optionClass->keyRender(_keyX + _dirFront->getWidth() + 45 + _dirBack->getWidth() / 2 + 1, _keyY + KEY_Y + 315, _optionClass->getHold());
		TextOut(getMemDC(), _keyX + 53, _keyY + KEY_Y + 360, "드랍", strlen("드랍"));
		_optionClass->keyRender(_keyX + _dirFront->getWidth() + 45 + _dirBack->getWidth() / 2 + 1, _keyY + KEY_Y + 360, _optionClass->getDrop());
		TextOut(getMemDC(), _keyX + 55, _keyY + KEY_Y + 405, "스킬슬롯1", strlen("스킬슬롯1"));
		_optionClass->keyRender(_keyX + _dirFront->getWidth() + 45 + _dirBack->getWidth() / 2 - 1, _keyY + KEY_Y + 405, _optionClass->getSkillSlot1());
		TextOut(getMemDC(), _keyX + 55, _keyY + KEY_Y + 450, "스킬슬롯2", strlen("스킬슬롯2"));
		_optionClass->keyRender(_keyX + _dirFront->getWidth() + 45 + _dirBack->getWidth() / 2 - 1, _keyY + KEY_Y + 450, _optionClass->getSkillSlot2());
		TextOut(getMemDC(), _keyX + 55, _keyY + KEY_Y + 495, "아이템슬롯1", strlen("아이템슬롯1"));
		_optionClass->keyRender(_keyX + _dirFront->getWidth() + 45 + _dirBack->getWidth() / 2 - 1, _keyY + KEY_Y + 495, _optionClass->getItemSlot1());
		TextOut(getMemDC(), _keyX + 55, _keyY + KEY_Y + 540, "아이템슬롯2", strlen("아이템슬롯2"));
		_optionClass->keyRender(_keyX + _dirFront->getWidth() + 45 + _dirBack->getWidth() / 2 - 1, _keyY + KEY_Y + 540, _optionClass->getItemSlot2());

		SelectObject(getMemDC(), _oldFont);
	}

	// 닫기 버튼
	_closeButton.img->frameRender(getMemDC(), _closeButton.img->getX(), _closeButton.img->getY());

	// 골드가 부족한 경우
	if (_notEnoughGold)
	{
		if (GetTickCount64() - _goldTimer >= 500)
			_notEnoughGold = false;

		_oldFont = (HFONT)SelectObject(getMemDC(), _bigFont);
		SetTextColor(getMemDC(), RGB(0, 0, 0));
		TextOut(getMemDC(), WINSIZEX / 2 - 10 * strlen("골드가 부족합니다."), WINSIZEY / 2, "골드가 부족합니다.", strlen("골드가 부족합니다."));
		SetTextColor(getMemDC(), RGB(255, 0, 0));
		TextOut(getMemDC(), WINSIZEX / 2 - 10 * strlen("골드가 부족합니다.") - 2, WINSIZEY / 2 - 2, "골드가 부족합니다.", strlen("골드가 부족합니다."));

		SelectObject(getMemDC(), _oldFont);
	}

	if (_screenOut->getY() < WINSIZEY)
		_screenOut->render(getMemDC(), _screenOut->getX(), _screenOut->getY());
}

void main::moveBoard(tagMenu menu)
{
	int speed = 0;
	int x = 0;
	int y = 0;
	int other = 0;
	bool on = false;

	// 띄워야할 메뉴의 정보를 입력 받는다
	switch (menu)
	{
	case OPTION:
		speed = _popSpeed;
		x = _popX;
		y = _popY;
		other = _askY < _keyY ? _askY : _keyY;
		on = _popOn;
		break;
	case KEYPAD:
		speed = _keySpeed;
		x = _keyX;
		y = _keyY;
		other = _askY < _popY ? _askY : _popY;
		on = _keyOn;
		break;
	case QUIT:
		speed = _askSpeed;
		x = _askX;
		y = _askY;
		other = _popY < _keyY ? _popY : _keyY;
		on = _askOn;
		break;
	}

	// 창이 출력 상태이고 다른 창이 화면 밖에 있다면
	if (on && other == WINSIZEY)
	{
		// 스피드가 점점 느려지게하고 1보다 작아지면 마이너스로 반동으로 돌아오는 느낌을 준다.
		if (speed >= 1)
		{
			y -= speed;

			speed /= 2;
		}
		else if (speed > -10)
		{
			y -= speed;

			speed -= 3;
		}
		else
		{
			_optionClass->crushButton(&_okButton, 1, 0);
			_optionClass->crushButton(&_closeButton, 1, 0);
		}
	}
	else
	{
		// 아래로 떨어지게끔 모션을 준다
		if (speed < 1)
		{
			y += speed;

			speed += 3;
		}
		else if (y < WINSIZEY)
		{
			y += speed;

			speed *= 2;
		}
		else
		{
			y = WINSIZEY;

			speed = 400;
		}
	}

	// 메뉴의 정보를 반환한다.
	switch (menu)
	{
	case OPTION:
		_popSpeed = speed;
		_popX = x;
		_popY = y;

		// BackGround Sound의 위치
		_bgmSound.img->setX(_popX + 50);
		_bgmSound.img->setY(_popY + 100);

		// Effect Sound의 위치
		_effectSound.img->setX(_bgmSound.img->getX() + _bgmSound.img->getFrameWidth() + 10);
		_effectSound.img->setY(_popY + 100);

		// Keypad의 위치
		_keypad.img->setX(_effectSound.img->getX() + _effectSound.img->getFrameWidth() + 10);
		_keypad.img->setY(_popY + 100);

		if (other == WINSIZEY)
		{
			// closeButton의 위치
			_closeButton.img->setX(_popX + _popUp->getWidth() - _closeButton.img->getFrameWidth() * 0.75);
			_closeButton.img->setY(_popY - _closeButton.img->getFrameHeight() / 4);
		}
		break;
	case KEYPAD:
		_keySpeed = speed;
		_keyX = x;
		_keyY = y;

		for (int i = 0; i < FUNCTION_KEY_AMOUNT; i++)
			_keyChangeRc[i] = RectMake(_keyX + _dirFront->getWidth() + 45, _keyY + KEY_Y + 60 + 45 * i + 70 * (i / 4 - i / 8) , _dirBack->getWidth(), _dirBack->getHeight());

		if (other == WINSIZEY)
		{
			// closeButton의 위치
			_closeButton.img->setX(_keyX + _keyBoard->getWidth() - _closeButton.img->getFrameWidth() * 0.75);
			_closeButton.img->setY(_keyY - _closeButton.img->getFrameHeight() / 4);
		}
		break;
	case QUIT:
		_askSpeed = speed;
		_askX = x;
		_askY = y;

		if (other == WINSIZEY)
		{
			// ok버튼의 위치
			_okButton.img->setX(_askX + 60);
			_okButton.img->setY(_askY + _ask->getHeight() - 100);

			// closeButton의 위치
			_closeButton.img->setX(_askX + _ask->getWidth() - 120 - _closeButton.img->getFrameWidth() / 2);
			_closeButton.img->setY(_askY + _ask->getHeight() - 100);
		}
		break;
	}
}
