#include "stdafx.h"
#include "inventory.h"

HRESULT inventory::init(int x, int y, int width, int height)
{
	// 아이템 할당
	_item = new Item;
	_item->init();

	// 장착 UI 이미지
	_helmet = IMAGEMANAGER->findImage("EquipHelmet");
	_weapon = IMAGEMANAGER->findImage("EquipWeapon");
	_armor = IMAGEMANAGER->findImage("EquipArmor");
	_shield = IMAGEMANAGER->findImage("EquipShield");
	_belt = IMAGEMANAGER->findImage("EquipBelt");
	_shoes = IMAGEMANAGER->findImage("EquipShoes");
	_necklace = IMAGEMANAGER->findImage("EquipNecklace");

	// 스테이터스 UI 이미지
	_status = IMAGEMANAGER->findImage("Status");
	_hp = IMAGEMANAGER->findImage("HP");
	_atk = IMAGEMANAGER->findImage("Atk");
	_def = IMAGEMANAGER->findImage("Def");

	// 소지금
	_gold = IMAGEMANAGER->findImage("Gold");

	// 창 크기
	_boardSize = RectMake(x, y, width, height);

	// 이미지 출력 X값
	int leftX = _boardSize.left + EQUIP_BLANK;
	int centerX = leftX + _helmet->getWidth() + 5;
	int rightX = centerX + _helmet->getWidth() + 5;

	// 이미지 출력 Y값
	int topY = _boardSize.top + EQUIP_BLANK + 50;
	int centerY = topY + _helmet->getHeight() + 20;
	int bottomY = centerY + _helmet->getHeight() + 20;

	// 스테이터스
	int statusX = rightX + _helmet->getWidth() + 13;

	// 이미지 좌표 설정
	_helmet->setX(centerX);
	_helmet->setY(topY);

	_necklace->setX(rightX);
	_necklace->setY(topY);

	_weapon->setX(leftX);
	_weapon->setY(centerY);

	_armor->setX(centerX);
	_armor->setY(centerY);

	_shield->setX(rightX);
	_shield->setY(centerY);

	_belt->setX(leftX);
	_belt->setY(bottomY);

	_shoes->setX(centerX);
	_shoes->setY(bottomY);

	_hp->setX(statusX);
	_hp->setY(topY);

	_atk->setX(statusX);
	_atk->setY(centerY);

	_def->setX(statusX);
	_def->setY(bottomY);

	_status->setX(statusX - 3);
	_status->setY(topY);

	// 슬롯 초기화
	for (int i = 0; i < INVENTORY_SIZE; i++)
	{
		_slot[i].rc = RectMake(x + width - 54 * (i % (width / 54) + 1), y + height - 55 * (i / (width / 54) + 1), 50, 50);
		_slot[i].name = "Empty";
		_slot[i].type = TYPE_END;
	}

	// 포션 갯수 초기화
	_smallPotionAmount = 0;
	_largePotionAmount = 0;

	// 인벤토리 불러오기
	this->load("inventory.inv");

	// 빈칸이 없을경우 안내문구 출력을 위한 bool값
	_full = false;

	// 폰트
	SetBkMode(getMemDC(), TRANSPARENT);
	_font = CreateFont(60, 0, 0, 0, 500, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("배찌체"));

	return S_OK;
}

void inventory::release()
{
	_item->release();
	SAFE_DELETE(_item);
}

void inventory::update()
{
}

void inventory::render(player* _player)
{
	// 인벤토리 슬롯 출력
	for (int i = INVENTORY_SIZE - 1; i >= 0; i--)
	{
		IMAGEMANAGER->alphaRender("Slot", getMemDC(), _slot[i].rc.left, _slot[i].rc.top, 100);
		
		// 해당 슬롯에 있는 아이템 출력
		if (_slot[i].name != "Empty")
			IMAGEMANAGER->render(_slot[i].name, getMemDC(), _slot[i].rc.left, _slot[i].rc.top);
	}

	// 소지금 출력
	_gold->render(getMemDC(), (_boardSize.right + _boardSize.left) / 2 + 30, _slot[INVENTORY_SIZE - 1].rc.top - 35);
	printNumber(_player->getGold(), (_boardSize.right + _boardSize.left) / 2 + 65, _slot[INVENTORY_SIZE - 1].rc.top - 26);

	// 선택된 아이템 출력
	if (_select.select)
		IMAGEMANAGER->render("Selected", getMemDC(), _select.rc.left - 5, _select.rc.top - 5);

	// 인벤토리가 가득찬 경우
	if (_full)
	{
		// 0.5초간 출력
		if (GetTickCount64() - _timer >= 500)
			_full = false;

		// 빈칸이 없다는 문구 출력
		_oldFont = (HFONT)SelectObject(getMemDC(), _font);
		SetTextColor(getMemDC(), RGB(0, 0, 0));
		TextOut(getMemDC(), WINSIZEX / 2 - 10 * strlen("빈칸이 없습니다."), WINSIZEY / 2, "빈칸이 없습니다.", strlen("빈칸이 없습니다."));
		SetTextColor(getMemDC(), RGB(255, 0, 0));
		TextOut(getMemDC(), WINSIZEX / 2 - 10 * strlen("빈칸이 없습니다.") - 2, WINSIZEY / 2 - 2, "빈칸이 없습니다.", strlen("빈칸이 없습니다."));

		SelectObject(getMemDC(), _oldFont);
	}
}

bool inventory::setItem(string name, tagType type)
{
	// 빈 곳을 찾아서 인벤토리에 아이템을 추가한다.
	for (int i = INVENTORY_SIZE; i >= 0; i--)
	{
		if (_slot[i].name == "Empty")
		{
			// 빈 슬롯에 아이템 정보 저장
			_slot[i].name = name;
			_slot[i].type = type;
			_slot[i].value = _item->getData(type, name);

			// 포션은 갯수를 카운트해준다.
			if (_slot[i].name == "SmallPotion")
				_smallPotionAmount++;
			else if (_slot[i].name == "LargePotion")
				_largePotionAmount++;

			return true;
		}
	}

	// 빈칸이 없을경우 _full bool값을 true로 만들어준다
	_full = true;
	_timer = GetTickCount64();

	return false;
}

bool inventory::selectItem(POINT pt)
{
	for (int i = INVENTORY_SIZE - 1; i >= 0; i--)
	{
		// 슬롯 순회하며 마우스 좌표와 충돌중인 슬롯 체크
		if (PtInRect(&_slot[i].rc, pt))
		{
			// 기존 선택한 슬롯과 같은 슬롯일 경우 True값 반환하여 필요한 작업 수행
			if (_slot[i].rc.left == _select.rc.left && _slot[i].rc.top == _select.rc.top)
			{
				return true;
			}
			// 처음 선택한 슬롯이 빈칸이 아닌 경우 정보 저장
			else if (_slot[i].name != "Empty")
			{
				_select.name = _slot[i].name;
				_select.rc = _slot[i].rc;
				_select.select = true;
				_select.value = _slot[i].value;

				return false;
			}

			// 그 외 정보 초기화
			_select.rc = {};
			_select.select = false;
			return false;
		}
	}

	// 충돌한 곳이 없을때
	_select.select = false;
	return false;
}

bool inventory::useItem(POINT pt)
{
	for (int i = INVENTORY_SIZE - 1; i >= 0; i--)
	{
		// 슬롯 순회하며 마우스 좌표와 충돌중인 슬롯 체크
		if (PtInRect(&_slot[i].rc, pt))
		{
			// 기존 선택한 슬롯과 같은 슬롯일 경우
			if (_slot[i].rc.left == _select.rc.left && _slot[i].rc.top == _select.rc.top)
			{
				// 선택정보 초기화
				_select.select = false;
				_select.rc = {};

				// 아이템을 땡겨서 빈칸 매꾸기
				while (_slot[i].name != "Empty")
				{
					if (i == 0)
					{
						_slot[i].name = "Empty";
						_slot[i].type = TYPE_END;
						_slot[i].value = {};
						break;
					}

					_slot[i].name = _slot[i - 1].name;
					_slot[i].type = _slot[i - 1].type;
					_slot[i].value = _slot[i - 1].value;

					i--;
				}

				return true;
			}
		}
	}

	return false;
}

bool inventory::usePotion(string name)
{
	for (int i = INVENTORY_SIZE - 1; i >= 0; i--)
	{
		// 해당 슬롯이 사용하고자하는 포션과 같은 이름일 경우 사용
		if (_slot[i].name == name)
		{
			// 선택정보 저장
			_select.name = _slot[i].name;
			_select.rc = _slot[i].rc;
			_select.value = _slot[i].value;

			// 아이템 사용 결과에 따라 분기
			if (useItem({ _slot[i].rc.left + 1, _slot[i].rc.top + 1 }))
			{
				if (_select.name == "SmallPotion")
					_smallPotionAmount--;
				else if (_select.name == "LargePotion")
					_largePotionAmount--;

				return true;
			}

			break;
		}
	}

	return false;
}

void inventory::printEquipment(player* _player)
{
	// 스테이터스 창
	_status->render(getMemDC(), _status->getX(), _status->getY());

	// 체력
	_hp->render(getMemDC(), _hp->getX(), _hp->getY());
	printNumber(_player->getMaxHp(), _hp->getX(), _hp->getY() + _hp->getHeight() + 10);
	
	// 공격력
	_atk->render(getMemDC(), _atk->getX(), _atk->getY());
	printNumber(_player->getAtk(), _atk->getX(), _atk->getY() + _hp->getHeight() + 10);
	
	// 방어력
	_def->render(getMemDC(), _def->getX(), _def->getY());
	printNumber(_player->getDef(), _def->getX(), _def->getY() + _hp->getHeight() + 10);

	// 각 장착칸 이미지 출력, 장착된 아이템 있으면 아이템까지 출력
	_helmet->render(getMemDC(), _helmet->getX(), _helmet->getY());

	if (_player->getHelmet().name != "Empty")
		IMAGEMANAGER->render(_player->getHelmet().name, getMemDC(), _helmet->getX(), _helmet->getY());

	_necklace->render(getMemDC(), _necklace->getX(), _necklace->getY());

	if (_player->getNecklace().name != "Empty")
		IMAGEMANAGER->render(_player->getNecklace().name, getMemDC(), _necklace->getX(), _necklace->getY());

	_weapon->render(getMemDC(), _weapon->getX(), _weapon->getY());

	if (_player->getWeapon().name != "Empty")
		IMAGEMANAGER->render(_player->getWeapon().name, getMemDC(), _weapon->getX(), _weapon->getY());

	_armor->render(getMemDC(), _armor->getX(), _armor->getY());

	if (_player->getArmor().name != "Empty")
		IMAGEMANAGER->render(_player->getArmor().name, getMemDC(), _armor->getX(), _armor->getY());

	_shield->render(getMemDC(), _shield->getX(), _shield->getY());

	if (_player->getShield().name != "Empty")
		IMAGEMANAGER->render(_player->getShield().name, getMemDC(), _shield->getX(), _shield->getY());

	_belt->render(getMemDC(), _belt->getX(), _belt->getY());

	if (_player->getBelt().name != "Empty")
		IMAGEMANAGER->render(_player->getBelt().name, getMemDC(), _belt->getX(), _belt->getY());

	_shoes->render(getMemDC(), _shoes->getX(), _shoes->getY());

	if (_player->getShoes().name != "Empty")
		IMAGEMANAGER->render(_player->getShoes().name, getMemDC(), _shoes->getX(), _shoes->getY());
}

void inventory::printNumber(int num, int x, int y, float scale)
{
	// 자릿수에 따른 숫자이미지 출력하는 함수
	
	int digit = 1;

	while (num / digit >= 10)
		digit *= 10;

	for (int i = 0; ; i++, digit /= 10)
	{
		if (digit != 1)
			IMAGEMANAGER->scaleFrameRender("Number", getMemDC(), x + 12 * i, y, (num / digit) % 10, 0, scale);
		else
		{
			IMAGEMANAGER->scaleFrameRender("Number", getMemDC(), x + 12 * i , y, num % 10, 0, scale);
			break;
		}
	}
}

bool inventory::equipOff(POINT pt, player* _player)
{
	/*
	각 장착 부위별 이미지와 마우스 좌표가 충돌중인지 확인하고
	처음 클릭시 선택정보를 저장하며
	선택된 정보를 다시 클릭했을 경우
	인벤토리 빈공간이 존재할때 장착한 아이템을 벗어서 인벤토리 빈공간에 넣는다.
	*/
	
	// 헬멧
	if (PtInRect(&_helmet->boudingBox(), pt))
	{
		if (_helmet->boudingBox().left == _select.rc.left && _helmet->boudingBox().top == _select.rc.top)
		{
			for (int i = INVENTORY_SIZE - 1; i >= 0; i--)
			{
				if (_slot[i].name == "Empty")
				{
					_slot[i].name = _player->getHelmet().name;
					_slot[i].type = _player->getHelmet().type;
					_slot[i].value = _player->getHelmet();

					_select.select = false;
					_select.rc = {};

					return true;
				}
			}
		}
		else if (_player->getHelmet().name != "Empty")
		{
			_select.name = _player->getHelmet().name;
			_select.rc = _helmet->boudingBox();
			_select.value = _player->getHelmet();
			_select.select = true;

			return false;
		}
	}

	// 목걸이
	if (PtInRect(&_necklace->boudingBox(), pt))
	{
		if (_necklace->boudingBox().left == _select.rc.left && _necklace->boudingBox().top == _select.rc.top)
		{
			for (int i = INVENTORY_SIZE - 1; i >= 0; i--)
			{
				if (_slot[i].name == "Empty")
				{
					_slot[i].name = _player->getNecklace().name;
					_slot[i].type = _player->getNecklace().type;
					_slot[i].value = _player->getNecklace();

					_select.select = false;
					_select.rc = {};

					return true;
				}
			}
		}
		else if (_player->getNecklace().name != "Empty")
		{
			_select.name = _player->getNecklace().name;
			_select.rc = _necklace->boudingBox();
			_select.value = _player->getNecklace();
			_select.select = true;

			return false;
		}
	}

	// 무기
	if (PtInRect(&_weapon->boudingBox(), pt))
	{
		if (_weapon->boudingBox().left == _select.rc.left && _weapon->boudingBox().top == _select.rc.top)
		{
			for (int i = INVENTORY_SIZE - 1; i >= 0; i--)
			{
				if (_slot[i].name == "Empty")
				{
					_slot[i].name = _player->getWeapon().name;
					_slot[i].type = _player->getWeapon().type;
					_slot[i].value = _player->getWeapon();

					_select.select = false;
					_select.rc = {};

					return true;
				}
			}
		}
		else if (_player->getWeapon().name != "Empty")
		{
			_select.name = _player->getWeapon().name;
			_select.rc = _weapon->boudingBox();
			_select.value = _player->getWeapon();
			_select.select = true;

			return false;
		}
	}

	// 방어구
	if (PtInRect(&_armor->boudingBox(), pt))
	{
		if (_armor->boudingBox().left == _select.rc.left && _armor->boudingBox().top == _select.rc.top)
		{
			for (int i = INVENTORY_SIZE - 1; i >= 0; i--)
			{
				if (_slot[i].name == "Empty")
				{
					_slot[i].name = _player->getArmor().name;
					_slot[i].type = _player->getArmor().type;
					_slot[i].value = _player->getArmor();

					_select.select = false;
					_select.rc = {};

					return true;
				}
			}
		}
		else if (_player->getArmor().name != "Empty")
		{
			_select.name = _player->getArmor().name;
			_select.rc = _armor->boudingBox();
			_select.value = _player->getArmor();
			_select.select = true;

			return false;
		}
	}

	// 방패
	if (PtInRect(&_shield->boudingBox(), pt))
	{
		if (_shield->boudingBox().left == _select.rc.left && _shield->boudingBox().top == _select.rc.top)
		{
			for (int i = INVENTORY_SIZE - 1; i >= 0; i--)
			{
				if (_slot[i].name == "Empty")
				{
					_slot[i].name = _player->getShield().name;
					_slot[i].type = _player->getShield().type;
					_slot[i].value = _player->getShield();

					_select.select = false;
					_select.rc = {};

					return true;
				}
			}
		}
		else if (_player->getShield().name != "Empty")
		{
			_select.name = _player->getShield().name;
			_select.rc = _shield->boudingBox();
			_select.value = _player->getShield();
			_select.select = true;

			return false;
		}
	}

	// 벨트
	if (PtInRect(&_belt->boudingBox(), pt))
	{
		if (_belt->boudingBox().left == _select.rc.left && _belt->boudingBox().top == _select.rc.top)
		{
			for (int i = INVENTORY_SIZE - 1; i >= 0; i--)
			{
				if (_slot[i].name == "Empty")
				{
					_slot[i].name = _player->getBelt().name;
					_slot[i].type = _player->getBelt().type;
					_slot[i].value = _player->getBelt();

					_select.select = false;
					_select.rc = {};

					return true;
				}
			}
		}
		else if (_player->getBelt().name != "Empty")
		{
			_select.name = _player->getBelt().name;
			_select.rc = _belt->boudingBox();
			_select.value = _player->getBelt();
			_select.select = true;

			return false;
		}
	}

	// 신발
	if (PtInRect(&_shoes->boudingBox(), pt))
	{
		if (_shoes->boudingBox().left == _select.rc.left && _shoes->boudingBox().top == _select.rc.top)
		{
			for (int i = INVENTORY_SIZE - 1; i >= 0; i--)
			{
				if (_slot[i].name == "Empty")
				{
					_slot[i].name = _player->getShoes().name;
					_slot[i].type = _player->getShoes().type;
					_slot[i].value = _player->getShoes();

					_select.select = false;
					_select.rc = {};

					return true;
				}
			}
		}
		else if (_player->getShoes().name != "Empty")
		{
			_select.name = _player->getShoes().name;
			_select.rc = _shoes->boudingBox();
			_select.value = _player->getShoes();
			_select.select = true;

			return false;
		}
	}

	return false;
}

void inventory::save(string fileName)
{
	HANDLE file;
	DWORD write;

	// 파일 생성
	file = CreateFile(fileName.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	// 인벤토리 슬롯 크기만큼 데이터 저장
	WriteFile(file, _slot, sizeof(tagSlot) * INVENTORY_SIZE, &write, NULL);

	// 파일 닫기
	CloseHandle(file);
}

void inventory::load(string fileName)
{
	HANDLE file;
	DWORD read;
	
	// 버퍼 사용전 초기화
	tagSlot buf[INVENTORY_SIZE];
	ZeroMemory(buf, sizeof(tagSlot) * INVENTORY_SIZE);

	// 파일 열기
	file = CreateFile(fileName.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	// 인벤토리 슬롯 크기만큼 데이터 받기
	ReadFile(file, buf, sizeof(tagSlot) * INVENTORY_SIZE, &read, NULL);

	// 저장된 데이터를 슬롯에 등록
	for (int i = 0; i < INVENTORY_SIZE; i++)
	{
		_slot[i].name = buf[i].name;
		_slot[i].type = buf[i].type;
		_slot[i].value = _item->getData(_slot[i].type, _slot[i].name);

		if (_slot[i].name == "SmallPotion")
			_smallPotionAmount++;
		else if (_slot[i].name == "LargePotion")
			_largePotionAmount++;
	}

	// 버퍼 초기화
	ZeroMemory(buf, sizeof(tagSlot)* INVENTORY_SIZE);

	// 파일 닫기
	CloseHandle(file);
}
