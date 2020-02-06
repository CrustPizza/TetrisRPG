#include "stdafx.h"
#include "main.h"

HRESULT main::init()
{
	// UI �̹��� ���
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

	// �÷��̾�
	_player = new player;
	_player->init();
	_player->load();

	// �κ��丮
	_inventory = new inventory;
	_inventory->init(_tetrisBoard->getX(), _tetrisBoard->getY(), _tetrisBoard->getWidth(), _tetrisBoard->getHeight());
	_inventoryOpen = true;

	// ����
	_battleButton.img = IMAGEMANAGER->findImage("Battle");
	_stage = IMAGEMANAGER->findImage("Stage");
	_stageBoard = IMAGEMANAGER->findImage("StageBoard");
	_battleOpen = false;

	for (int i = 0; i < STAGE_MAX; i++)
	{
		_stageButton.push_back(RectMake(_tetrisBoard->getX() + 60, _tetrisBoard->getY() + 20 * (i + 1) + _stageBoard->getHeight() * i, _stageBoard->getWidth(), _stageBoard->getHeight()));
	}

	// ����
	_shop = new shop;
	_shop->init(_tetrisBoard->getX(), _tetrisBoard->getY(), _tetrisBoard->getWidth(), _tetrisBoard->getHeight(), _inventory);
	_shopOpen = false;
	_notEnoughGold = false;
	_goldTimer = GetTickCount64();

	// ��ư ���� Ȱ��ȭ
	_character.sound = true;
	_shopButton.sound = true;
	_option.sound = true;
	_exit.sound = true;

	_bgmSound.sound = true;
	_effectSound.sound = true;
	_keypad.sound = true;
	_okButton.sound = true;
	_closeButton.sound = true;

	// ����
	_loopY = 0;

	// �ɼ�â �ʱ�ȭ
	_popOn = false;
	_popX = (WINSIZEX - _popUp->getWidth()) / 2;
	_popY = WINSIZEY;
	_popSpeed = 400;

	// ����â �ʱ�ȭ
	_askOn = false;
	_askX = (WINSIZEX - _ask->getWidth()) / 2;
	_askY = WINSIZEY;
	_askSpeed = 400;

	// Ű�Է� �ʱ�ȭ
	_keyOn = false;
	_keyX = (WINSIZEX - _keyBoard->getWidth()) / 2;
	_keyY = WINSIZEY;
	_keySpeed = 400;
	_keyChange = 0;

	// ȭ����ȯ
	_screenChange = false;

	// �����
	if (!SOUNDMANAGER->isPlaySound("MainBgm"))
		SOUNDMANAGER->play("MainBgm");

	if (SOUNDMANAGER->isPauseSound("BattleBgm"))
		SOUNDMANAGER->pause("MainBgm");

	SOUNDMANAGER->stop("BattleBgm");

	// �ɼ�
	_optionClass = new option;
	_optionClass->init();

	// ��Ʈ
	SetBkMode(getMemDC(), TRANSPARENT);
	_bigFont = CreateFont(60, 0, 0, 0, 500, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("����ü"));
	_smallFont = CreateFont(30, 0, 0, 0, 500, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("����ü"));

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
	// �� ��ȯ�ϱ� ���� �̹����� ����ϰ� �۾��� ������ �������� �ҷ��´�
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
		// �� Ŭ���� ������Ʈ
		_player->update();
		_player->playerIdle();
		_shop->update();

		// ���콺 �浹�� ������ �ٲٱ�
		_optionClass->crushButton(&_character, 1, 0);
		_optionClass->crushButton(&_battleButton, 1, 0);
		_optionClass->crushButton(&_shopButton, 1, 0);
		_optionClass->crushButton(&_option, 1, 0);
		_optionClass->crushButton(&_exit, 1, 0);

		// �÷��̾� �̵�
		if (_player->getImage()->getX() > _room->getX())
			_player->playerMove(LEFT);
		if (_player->getImage()->getX() + _player->getImage()->getFrameWidth() < _room->getX() + _room->getWidth() - 2)
			_player->playerMove(RIGHT);
		if (_player->getImage()->getY() > _room->getY() + 135)
			_player->playerMove(UP);
		if (_player->getImage()->getY() + _player->getImage()->getFrameHeight() < _room->getY() + _room->getHeight() - 2)
			_player->playerMove(DOWN);

		// Ű�� ��ü
		if (_keyChange)
		{
			if (_optionClass->keyChange(_keyChange))
				_keyChange = 0;
		}

		// Ű ���� â�� ������ Ű���� ���� ������ �ִٸ� �ʱ�ȭ ��Ű�� ���ٸ� Ű���� �����Ѵ�.
		if (!_keyOn)
		{
			if (_optionClass->keyCheck(false, 7))
				_optionClass->init();
			else
				_optionClass->release();
		}

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

			// Ŭ�� ȿ����
			SOUNDMANAGER->play("Click", SOUNDMANAGER->getEffectVolume());
		}

		// ��Ŭ��
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			// ĳ����â ��ư ��������
			if (PtInRect(&_character.img->boudingBoxWithFrame(), _ptMouse) && (_askSpeed == 400 || _askSpeed <= -10) && (_popSpeed == 400 || _popSpeed <= -10))
			{
				// ĳ���� â�� ����, ��Ÿ �޴��� �ݾ��ش�
				_inventoryOpen = true;
				_battleOpen = false;
				_popOn = false;
				_askOn = false;
				_keyOn = false;
				_shopOpen = false;
			}

			// ���� ��ư ��������
			if (PtInRect(&_battleButton.img->boudingBoxWithFrame(), _ptMouse) && (_askSpeed == 400 || _askSpeed <= -10) && (_popSpeed == 400 || _popSpeed <= -10))
			{
				// ���� â�� ����, ��Ÿ �޴��� �ݾ��ش�
				_battleOpen = true;
				_inventoryOpen = false;
				_popOn = false;
				_askOn = false;
				_keyOn = false;
				_shopOpen = false;
			}

			// ���� ��ư ��������
			if (PtInRect(&_shopButton.img->boudingBoxWithFrame(), _ptMouse) && (_askSpeed == 400 || _askSpeed <= -10) && (_popSpeed == 400 || _popSpeed <= -10))
			{
				// ���� â�� ����, ��Ÿ �޴��� �ݾ��ش�
				_shopOpen = true;
				_battleOpen = false;
				_inventoryOpen = false;
				_popOn = false;
				_askOn = false;
				_keyOn = false;
			}

			// �ɼ� ��ư�� ��������
			if (PtInRect(&_option.img->boudingBoxWithFrame(), _ptMouse) && (_popSpeed == 400 || _popSpeed <= -10))
			{
				// �����ִٸ� �ݰ� �����ִٸ� ����, �ɼ� �޴��� �ݾ��ش�
				_popOn = !_popOn;
				_askOn = false;
				_keyOn = false;
			}

			// ���� ��ư�� ��������
			if (PtInRect(&_exit.img->boudingBoxWithFrame(), _ptMouse) && (_askSpeed == 400 || _askSpeed <= -10))
			{
				// �����ִٸ� �ݰ� �����ִٸ� ����, ���� �޴��� �ݾ��ش�
				_askOn = !_askOn;
				_popOn = false;
				_keyOn = false;
			}

			// �ɼ�â�� ��������
			if (_popOn)
			{
				// ����� ��ư�� �浹�ߴٸ� ����� On/Off�� �����Ѵ�
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

				// ȿ���� ��ư�� �浹�ߴٸ� ȿ���� On/Off�� �����Ѵ�
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

				// Ű ����
				if (PtInRect(&_keypad.img->boudingBoxWithFrame(), _ptMouse))
				{
					_popOn = false;
					_keyOn = true;
				}

				// �ݱ� ��ư
				if (PtInRect(&_closeButton.img->boudingBoxWithFrame(), _ptMouse))
					_popOn = false;
			}

			// ����� �ٽ� �ѹ� Ȯ���Ͽ� ������ ������ �����
			else if (_askOn)
			{
				// Ȯ���� ������ ��� ����
				if (PtInRect(&_okButton.img->boudingBoxWithFrame(), _ptMouse))
					PostMessage(_hWnd, WM_DESTROY, 0, 0);

				// ��Ҹ� ������� â ����
				if (PtInRect(&_closeButton.img->boudingBoxWithFrame(), _ptMouse))
					_askOn = false;
			}
			else if (_keyOn)
			{
				// ��Ҹ� ������� â ����
				if (PtInRect(&_closeButton.img->boudingBoxWithFrame(), _ptMouse))
				{
					_keyOn = false;
					_popOn = true;
				}

				// ������ Ű���� ����
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
				// �κ��丮���� �������� ����
				if (_inventoryOpen)
				{
					// ������ ��� ���θ޴����� ������� ���ϹǷ� �����Ѵ�.
					if (_inventory->selectItem(_ptMouse))
					{
						if (_inventory->getSelect().value.type != POTION)
						{
							_inventory->useItem(_ptMouse);

							// �̹� ������ ������ ��� selectItem���� true�� ��ȯ�Ͽ� if�� ������ ������ �������� �����Ѵ�.
							tagItemData buf = _player->equipItem(_inventory->getSelect().value.type, _inventory->getSelect().name);

							// �÷��̾ �������� �������� ��� �������� ��ü�� �������̴� �������� �κ��丮�� �ǵ�����
							if (buf.name != "Empty")
								_inventory->setItem(buf.name, buf.type);
						}
					}

					// �κ��丮���� ��� ������
					if (_inventory->equipOff(_ptMouse, _player))
					{
						_player->equitOffItem(_inventory->getSelect().value.type);
					}
				}

				// ���� ��������
				if (_shopOpen)
				{
					// �κ��丮�� �������� �����ϰ� �̹� ������ ���¶�� �������� �Ǹ��Ѵ�
					if (_inventory->selectItem(_ptMouse) && _inventory->useItem(_ptMouse))
					{
						_player->setGold(_player->getGold() + _inventory->getSelect().value.cost / 2);
					}

					RECT rc = _shop->selectList(_ptMouse).rc;
					tagItemData dataBuf = _shop->selectList(_ptMouse).data;

					// ���� ��ǰ�� ������ ���¶�� �������� Ȯ���ϰ� �������� ����ó���Ѵ�
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

				// ����â ��������
				if (_battleOpen)
				{
					// ���������� �����ϸ� ����ȯ���� �Ѿ��.
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

			// Ŭ�� ȿ����
			SOUNDMANAGER->play("Click", SOUNDMANAGER->getEffectVolume());
		}

		// �ɼ� �� ����â�� ���� �� ���� ���
		moveBoard(OPTION);
		moveBoard(KEYPAD);
		moveBoard(QUIT);
	}
	else
		_screenOut->setY(_screenOut->getY() + 50);

	// ��� ����
	_loopY--;
}

void main::render()
{
	// UI ����
	// ���
	_bg->loopRender(getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), 0, _loopY);

	// ĳ����â
	_room->render(getMemDC(), _room->getX(), _room->getY());
	_fieldGlass->alphaRender(getMemDC(), _fieldGlass->getX(), _fieldGlass->getY(), 150);
	_player->render();

	// ��Ʈ����â
	_tetrisBoard->alphaRender(getMemDC(), _tetrisBoard->getX(), _tetrisBoard->getY(), 150);

	// �κ��丮
	if (_inventoryOpen)
	{
		_inventory->printEquipment(_player);
		_inventory->render(_player);
	}

	// ����
	if (_shopOpen)
	{
		_shop->render();
		_inventory->render(_player);
	}

	// ����
	if (_battleOpen)
	{
		for (int i = 0; i < STAGE_MAX; i++)
		{
			_stageBoard->render(getMemDC(), _stageButton[i].left, _stageButton[i].top);
			_stage->render(getMemDC(), _stageButton[i].left + 10, _stageButton[i].top + 15);
			_inventory->printNumber(i + 1, _stageButton[i].left + 10 + _stage->getWidth(), _stageButton[i].top + 17, 1.4f);
		}
	}

	// �޴�
	_character.img->frameRender(getMemDC(), _character.img->getX(), _character.img->getY());
	_battleButton.img->frameRender(getMemDC(), _battleButton.img->getX(), _battleButton.img->getY());
	_shopButton.img->frameRender(getMemDC(), _shopButton.img->getX(), _shopButton.img->getY());
	_option.img->frameRender(getMemDC(), _option.img->getX(), _option.img->getY());
	_exit.img->frameRender(getMemDC(), _exit.img->getX(), _exit.img->getY());
	
	// �ɼ� UI
	if (_popY < WINSIZEY)
	{
		_popUp->render(getMemDC(), _popX, _popY);
		_bgmSound.img->frameRender(getMemDC(), _bgmSound.img->getX(), _bgmSound.img->getY());
		_effectSound.img->frameRender(getMemDC(), _effectSound.img->getX(), _effectSound.img->getY());
		_keypad.img->frameRender(getMemDC(), _keypad.img->getX(), _keypad.img->getY());
	}
	
	// ���� UI
	if (_askY < WINSIZEY)
	{
		_ask->render(getMemDC(), _askX, _askY);
		_okButton.img->frameRender(getMemDC(), _okButton.img->getX(), _okButton.img->getY());
	}

	// Ű ����
	if (_keyY < WINSIZEY)
	{
		// ��Ʈ ����
		_oldFont = (HFONT)SelectObject(getMemDC(), _bigFont);
		_keyBoard->render(getMemDC(), _keyX, _keyY);
		
		SetTextColor(getMemDC(), RGB(0, 0, 0));
		TextOut(getMemDC(), _keyX + 50, _keyY + KEY_Y, "����Ű", strlen("����Ű"));
		TextOut(getMemDC(), _keyX + 50, _keyY + KEY_Y + 250, "���Ű", strlen("���Ű"));

		SetTextColor(getMemDC(), RGB(255, 255, 255));
		TextOut(getMemDC(), _keyX + 48, _keyY + KEY_Y - 2, "����Ű", strlen("����Ű"));
		TextOut(getMemDC(), _keyX + 48, _keyY + KEY_Y + 248, "���Ű", strlen("���Ű"));

		SelectObject(getMemDC(), _oldFont);

		// Ű�� ������ â�� ����
		for (int i = 0; i < FUNCTION_KEY_AMOUNT; i++)
			_dirFront->alphaRender(getMemDC(), _keyX + 38, _keyChangeRc[i].top, 150);

		for (int i = 0; i < FUNCTION_KEY_AMOUNT; i++)
			_dirBack->alphaRender(getMemDC(), _keyChangeRc[i].left, _keyChangeRc[i].top, 150);

		_oldFont = (HFONT)SelectObject(getMemDC(), _smallFont);

		SetTextColor(getMemDC(), RGB(0, 0, 0));
		TextOut(getMemDC(), _keyX + 55, _keyY + KEY_Y + 66, "����", strlen("����"));
		_optionClass->keyRender(_keyX + _dirFront->getWidth() + 45 + _dirBack->getWidth() / 2 - 1, _keyY + KEY_Y + 66, _optionClass->getUp());
		TextOut(getMemDC(), _keyX + 55, _keyY + KEY_Y + 111, "�Ʒ���", strlen("�Ʒ���"));
		_optionClass->keyRender(_keyX + _dirFront->getWidth() + 45 + _dirBack->getWidth() / 2 - 1, _keyY + KEY_Y + 111, _optionClass->getDown());
		TextOut(getMemDC(), _keyX + 55, _keyY + KEY_Y + 156, "����", strlen("����"));
		_optionClass->keyRender(_keyX + _dirFront->getWidth() + 45 + _dirBack->getWidth() / 2 - 1, _keyY + KEY_Y + 156, _optionClass->getLeft());
		TextOut(getMemDC(), _keyX + 55, _keyY + KEY_Y + 201, "������", strlen("������"));
		_optionClass->keyRender(_keyX + _dirFront->getWidth() + 45 + _dirBack->getWidth() / 2 - 1, _keyY + KEY_Y + 201, _optionClass->getRight());
		TextOut(getMemDC(), _keyX + 55, _keyY + KEY_Y + 316, "Ȧ��", strlen("Ȧ��"));
		_optionClass->keyRender(_keyX + _dirFront->getWidth() + 45 + _dirBack->getWidth() / 2 - 1, _keyY + KEY_Y + 316, _optionClass->getHold());
		TextOut(getMemDC(), _keyX + 55, _keyY + KEY_Y + 361, "���", strlen("���"));
		_optionClass->keyRender(_keyX + _dirFront->getWidth() + 45 + _dirBack->getWidth() / 2 - 1, _keyY + KEY_Y + 361, _optionClass->getDrop());
		TextOut(getMemDC(), _keyX + 55, _keyY + KEY_Y + 406, "��ų����1", strlen("��ų����1"));
		_optionClass->keyRender(_keyX + _dirFront->getWidth() + 45 + _dirBack->getWidth() / 2 - 1, _keyY + KEY_Y + 406, _optionClass->getSkillSlot1());
		TextOut(getMemDC(), _keyX + 55, _keyY + KEY_Y + 451, "��ų����2", strlen("��ų����2"));
		_optionClass->keyRender(_keyX + _dirFront->getWidth() + 45 + _dirBack->getWidth() / 2 - 1, _keyY + KEY_Y + 451, _optionClass->getSkillSlot2());
		TextOut(getMemDC(), _keyX + 55, _keyY + KEY_Y + 499, "�����۽���1", strlen("�����۽���1"));
		_optionClass->keyRender(_keyX + _dirFront->getWidth() + 45 + _dirBack->getWidth() / 2 - 1, _keyY + KEY_Y + 499, _optionClass->getItemSlot1());
		TextOut(getMemDC(), _keyX + 55, _keyY + KEY_Y + 544, "�����۽���2", strlen("�����۽���2"));
		_optionClass->keyRender(_keyX + _dirFront->getWidth() + 45 + _dirBack->getWidth() / 2 - 1, _keyY + KEY_Y + 544, _optionClass->getItemSlot2());

		SetTextColor(getMemDC(), RGB(255, 255, 255));
		TextOut(getMemDC(), _keyX + 53, _keyY + KEY_Y + 65, "����", strlen("����"));
		_optionClass->keyRender(_keyX + _dirFront->getWidth() + 45 + _dirBack->getWidth() / 2 + 1, _keyY + KEY_Y + 65, _optionClass->getUp());
		TextOut(getMemDC(), _keyX + 53, _keyY + KEY_Y + 110, "�Ʒ���", strlen("�Ʒ���"));
		_optionClass->keyRender(_keyX + _dirFront->getWidth() + 45 + _dirBack->getWidth() / 2 + 1, _keyY + KEY_Y + 110, _optionClass->getDown());
		TextOut(getMemDC(), _keyX + 53, _keyY + KEY_Y + 155, "����", strlen("����"));
		_optionClass->keyRender(_keyX + _dirFront->getWidth() + 45 + _dirBack->getWidth() / 2 + 1, _keyY + KEY_Y + 155, _optionClass->getLeft());
		TextOut(getMemDC(), _keyX + 53, _keyY + KEY_Y + 200, "������", strlen("������"));
		_optionClass->keyRender(_keyX + _dirFront->getWidth() + 45 + _dirBack->getWidth() / 2 + 1, _keyY + KEY_Y + 200, _optionClass->getRight());
		TextOut(getMemDC(), _keyX + 53, _keyY + KEY_Y + 315, "Ȧ��", strlen("Ȧ��"));
		_optionClass->keyRender(_keyX + _dirFront->getWidth() + 45 + _dirBack->getWidth() / 2 + 1, _keyY + KEY_Y + 315, _optionClass->getHold());
		TextOut(getMemDC(), _keyX + 53, _keyY + KEY_Y + 360, "���", strlen("���"));
		_optionClass->keyRender(_keyX + _dirFront->getWidth() + 45 + _dirBack->getWidth() / 2 + 1, _keyY + KEY_Y + 360, _optionClass->getDrop());
		TextOut(getMemDC(), _keyX + 55, _keyY + KEY_Y + 405, "��ų����1", strlen("��ų����1"));
		_optionClass->keyRender(_keyX + _dirFront->getWidth() + 45 + _dirBack->getWidth() / 2 - 1, _keyY + KEY_Y + 405, _optionClass->getSkillSlot1());
		TextOut(getMemDC(), _keyX + 55, _keyY + KEY_Y + 450, "��ų����2", strlen("��ų����2"));
		_optionClass->keyRender(_keyX + _dirFront->getWidth() + 45 + _dirBack->getWidth() / 2 - 1, _keyY + KEY_Y + 450, _optionClass->getSkillSlot2());
		TextOut(getMemDC(), _keyX + 55, _keyY + KEY_Y + 495, "�����۽���1", strlen("�����۽���1"));
		_optionClass->keyRender(_keyX + _dirFront->getWidth() + 45 + _dirBack->getWidth() / 2 - 1, _keyY + KEY_Y + 495, _optionClass->getItemSlot1());
		TextOut(getMemDC(), _keyX + 55, _keyY + KEY_Y + 540, "�����۽���2", strlen("�����۽���2"));
		_optionClass->keyRender(_keyX + _dirFront->getWidth() + 45 + _dirBack->getWidth() / 2 - 1, _keyY + KEY_Y + 540, _optionClass->getItemSlot2());

		SelectObject(getMemDC(), _oldFont);
	}

	// �ݱ� ��ư
	_closeButton.img->frameRender(getMemDC(), _closeButton.img->getX(), _closeButton.img->getY());

	// ��尡 ������ ���
	if (_notEnoughGold)
	{
		if (GetTickCount64() - _goldTimer >= 500)
			_notEnoughGold = false;

		_oldFont = (HFONT)SelectObject(getMemDC(), _bigFont);
		SetTextColor(getMemDC(), RGB(0, 0, 0));
		TextOut(getMemDC(), WINSIZEX / 2 - 10 * strlen("��尡 �����մϴ�."), WINSIZEY / 2, "��尡 �����մϴ�.", strlen("��尡 �����մϴ�."));
		SetTextColor(getMemDC(), RGB(255, 0, 0));
		TextOut(getMemDC(), WINSIZEX / 2 - 10 * strlen("��尡 �����մϴ�.") - 2, WINSIZEY / 2 - 2, "��尡 �����մϴ�.", strlen("��尡 �����մϴ�."));

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

	// ������� �޴��� ������ �Է� �޴´�
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

	// â�� ��� �����̰� �ٸ� â�� ȭ�� �ۿ� �ִٸ�
	if (on && other == WINSIZEY)
	{
		// ���ǵ尡 ���� ���������ϰ� 1���� �۾����� ���̳ʽ��� �ݵ����� ���ƿ��� ������ �ش�.
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
		// �Ʒ��� �������Բ� ����� �ش�
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

	// �޴��� ������ ��ȯ�Ѵ�.
	switch (menu)
	{
	case OPTION:
		_popSpeed = speed;
		_popX = x;
		_popY = y;

		// BackGround Sound�� ��ġ
		_bgmSound.img->setX(_popX + 50);
		_bgmSound.img->setY(_popY + 100);

		// Effect Sound�� ��ġ
		_effectSound.img->setX(_bgmSound.img->getX() + _bgmSound.img->getFrameWidth() + 10);
		_effectSound.img->setY(_popY + 100);

		// Keypad�� ��ġ
		_keypad.img->setX(_effectSound.img->getX() + _effectSound.img->getFrameWidth() + 10);
		_keypad.img->setY(_popY + 100);

		if (other == WINSIZEY)
		{
			// closeButton�� ��ġ
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
			// closeButton�� ��ġ
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
			// ok��ư�� ��ġ
			_okButton.img->setX(_askX + 60);
			_okButton.img->setY(_askY + _ask->getHeight() - 100);

			// closeButton�� ��ġ
			_closeButton.img->setX(_askX + _ask->getWidth() - 120 - _closeButton.img->getFrameWidth() / 2);
			_closeButton.img->setY(_askY + _ask->getHeight() - 100);
		}
		break;
	}
}