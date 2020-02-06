#include "stdafx.h"
#include "tetris.h"

HRESULT tetris::init()
{
	// 鷺薫 戚耕走 去系
	_blue = IMAGEMANAGER->findImage("BlueBlock");
	_red = IMAGEMANAGER->findImage("RedBlock");
	_grey = IMAGEMANAGER->findImage("GreyBlock");
	_green = IMAGEMANAGER->findImage("GreenBlock");
	_yellow = IMAGEMANAGER->findImage("YellowBlock");
	_emerald = IMAGEMANAGER->findImage("EmeraldBlock");
	_brown = IMAGEMANAGER->findImage("BrownBlock");
	_pink = IMAGEMANAGER->findImage("PinkBlock");
	_purple = IMAGEMANAGER->findImage("PurpleBlock");

	_atkBuff = IMAGEMANAGER->findImage("AtkBuff");
	_atkDebuff = IMAGEMANAGER->findImage("AtkDebuff");
	_poison = IMAGEMANAGER->findImage("Poison");
	_recovery = IMAGEMANAGER->findImage("Recovery");

	// 壕伸 段奄鉢
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			_board[i][j].rc = RectMake(j * 32 - 8, WINSIZEY - 6 - 32 * i, 32, 32);

			if (i == 0 || j % WIDTH == 0 || j % WIDTH == WIDTH - 1)
				_board[i][j].wall = true;
			else
				_board[i][j].wall = false;

			_board[i][j].block = false;
		}
	}

	// 鷺薫 段奄鉢
	vector<bool> buf;

	buf.push_back(0);
	buf.push_back(0);
	buf.push_back(0);
	buf.push_back(0);

	_controlBlock = {};
	_nextBlock = {};
	_holdBlock = {};

	_controlBlock.block.push_back(buf);
	_controlBlock.block.push_back(buf);
	_controlBlock.block.push_back(buf);
	_controlBlock.block.push_back(buf);
	_nextBlock.block.push_back(buf);
	_nextBlock.block.push_back(buf);
	_nextBlock.block.push_back(buf);
	_nextBlock.block.push_back(buf);
	_holdBlock.block.push_back(buf);
	_holdBlock.block.push_back(buf);
	_holdBlock.block.push_back(buf);
	_holdBlock.block.push_back(buf);
	_holdBlock.color = -1;
	_skillOn = false;

	buf.~vector();

	// 段奄葵 竺舛
	_idx = (WIDTH - 4) / 2;
	_idy = HEIGHT - 4;
	_ghostY = _idy;
	_hold = true;

	makeBlock();
	makeBlock();

	while (moveBlock(DEFAULT));

	// 戚疑 展戚袴
	_timer = GetTickCount64();
	_downTimer = GetTickCount64();
	_stayCount = STAY_DELAY;

	// 獄覗 展戚袴
	_atkBuffTimer = GetTickCount64() - 10000;
	_atkDebuffTimer = GetTickCount64() - 10000;
	_poisonTimer = GetTickCount64() - 10000;
	_recoveryTimer = GetTickCount64() - 10000;

	// 惟績 曽戟
	_gameover = false;
	_overLine = 1;
	_overTimer = GetTickCount64();
	_resetCount = 4;
	_numberScale = 3.0f;

	// 爪左
	_combo.img = IMAGEMANAGER->findImage("Combo");
	_combo.count = 0;

	// 辛芝
	if (_option == nullptr)
	{
		_option = new option;

		_option->init();
	}

	return S_OK;
}

void tetris::release()
{
	_option->release();
	SAFE_DELETE(_option);
}

void tetris::update()
{
	// 惟績 神獄
	if (_gameover)
	{
		// 繕曽 鷺薫戚 赤聖 井酔 左球拭 蓄亜馬壱 搾趨層陥.
		if (!_controlBlock.block.empty())
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					if (_controlBlock.block[j][i])
					{
						_board[j + _idy][i + _idx].block = true;
						_board[j + _idy][i + _idx].color = _controlBlock.color;
					}
				}
			}

			_controlBlock.block.clear();
		}
		
		// 左球拭 赤澗 鷺薫級税 事聖 噺事生稽 嘘端
		for (int j = 1; j < WIDTH - 1; j++)
		{
			_board[_overLine][j].color = 7;
		}

		// 廃匝梢 嘘端馬奄是背 痕呪 竺舛
		if (_overLine < 20)
			_overLine++;
		else if (GetTickCount64() - _overTimer >= 1000)
		{
			_resetCount--;
			_overTimer = GetTickCount64();

			if (_resetCount == 0)
				_overTimer -= 500;

			_numberScale = 3.0f;
		}
		else
		{
			if (_numberScale > 1.0f)
				_numberScale -= 0.1f;
		}

		if (_resetCount == -1)
			init();
	}
	else
	{
		if (KEYMANAGER->isOnceKeyDown(_option->getHold()))
			holdBlock();

		if (KEYMANAGER->isOnceKeyDown(_option->getUp()))
			blockRotation();

		if (KEYMANAGER->isStayKeyDown(_option->getLeft()))
		{
			_stayCount /= 1.1f;

			if (GetTickCount64() - _timer >= _stayCount)
			{
				if (moveBlock(LEFT))
					SOUNDMANAGER->play("BlockMove", SOUNDMANAGER->getEffectVolume());
			}
		}
		
		if (KEYMANAGER->isStayKeyDown(_option->getRight()))
		{
			_stayCount /= 1.1f;

			if (GetTickCount64() - _timer >= _stayCount)
			{
				if (moveBlock(RIGHT))
					SOUNDMANAGER->play("BlockMove", SOUNDMANAGER->getEffectVolume());
			}
		}

		if (KEYMANAGER->isStayKeyDown(_option->getDown()))
		{
			_stayCount /= 1.1f;

			if (GetTickCount64() - _timer >= _stayCount)
			{
				moveBlock(DOWN);
				_timer = GetTickCount64();
			}
		}

		if (KEYMANAGER->isOnceKeyUp(_option->getLeft()))
		{
			_stayCount = STAY_DELAY;
			_timer -= STAY_DELAY;
		}

		if (KEYMANAGER->isOnceKeyUp(_option->getRight()))
		{
			_stayCount = STAY_DELAY;
			_timer -= STAY_DELAY;
		}

		if (KEYMANAGER->isOnceKeyUp(_option->getDown()))
		{
			_stayCount = STAY_DELAY;
			_timer -= STAY_DELAY;
		}

		if (KEYMANAGER->isOnceKeyDown(_option->getDrop()))
		{
			SOUNDMANAGER->play("BlockDrop", SOUNDMANAGER->getEffectVolume());

			while (moveBlock(DOWN));
		}

		if (GetTickCount64() - _downTimer >= 500)
			moveBlock(DOWN);
	}
}

void tetris::render()
{
	for (int i = 0; i < 21; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (_board[i][j].block)
			{
				blockColor(_board[i][j].rc.left, _board[i][j].rc.top, _board[i][j].color);
				
				if (_board[i][j].special)
					blockColor(_board[i][j].rc.left, _board[i][j].rc.top, _board[i][j].special);
			}
		}
	}
	
	int line = 4;

	if (_idy == 18)
		line--;

	if (_gameover)
	{
		if (_overLine == 20)
		{
			printNumber(_resetCount, (_board[0][0].rc.left + _board[0][WIDTH - 1].rc.right) / 2 - IMAGEMANAGER->findImage("BigNumber")->getFrameWidth() * _numberScale / 2, (_board[0][0].rc.bottom + _board[HEIGHT - 1][0].rc.top) / 2 - IMAGEMANAGER->findImage("BigNumber")->getFrameHeight() * _numberScale / 2, _numberScale);
		}
	}
	else
	{
		for (int i = 0; i < line; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (_controlBlock.block[i][j])
				{
					blockColor(_board[i + _idy][j + _idx].rc.left, _board[i + _idy][j + _idx].rc.top, _controlBlock.color);

					if (_controlBlock.special != 0 && j == _controlBlock.specialIndex.x && i == _controlBlock.specialIndex.y)
						blockColor(_board[i + _idy][j + _idx].rc.left, _board[i + _idy][j + _idx].rc.top, _controlBlock.special);
				}
			}
		}

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (_controlBlock.block[i][j])
				{
					blockColor(_board[i + _ghostY][j + _idx].rc.left, _board[i + _ghostY][j + _idx].rc.top, _controlBlock.color, 150);

					if (_controlBlock.special != 0 && j == _controlBlock.specialIndex.x && i == _controlBlock.specialIndex.y)
						blockColor(_board[i + _ghostY][j + _idx].rc.left, _board[i + _ghostY][j + _idx].rc.top, _controlBlock.special, 150);
				}
			}
		}
	}
}

bool tetris::getAtkBuff(int time)
{
	if (GetTickCount() - _atkBuffTimer <= time)
		return true;

	return false;
}

bool tetris::getAtkDebuff(int time)
{
	if (GetTickCount() - _atkDebuffTimer <= time)
		return true;

	return false;
}

bool tetris::getPoison(int time)
{
	if (GetTickCount() - _poisonTimer <= time)
		return true;

	return false;
}

bool tetris::getRecovery(int time)
{
	if (GetTickCount() - _recoveryTimer <= time)
		return true;

	return false;
}

void tetris::makeBlock()
{
	_controlBlock.block.clear();
	_controlBlock.block.push_back(_nextBlock.block[0]);
	_controlBlock.block.push_back(_nextBlock.block[1]);
	_controlBlock.block.push_back(_nextBlock.block[2]);
	_controlBlock.block.push_back(_nextBlock.block[3]);
	_controlBlock.color = _nextBlock.color;
	_controlBlock.special = _nextBlock.special;
	_controlBlock.specialIndex = _nextBlock.specialIndex;
	_controlBlock.rotationCount = _nextBlock.rotationCount;

	int rnd = _nextBlock.color;

	while (rnd == _nextBlock.color) 
		rnd = rand() % 7;

	_nextBlock.color = rnd;

	if (_skillOn)
		_nextBlock.color = 0;

	_nextBlock.rotationCount = 0;

	if ((rand() * 100) / RAND_MAX < SPECIAL_BLOCK_PERCENT)
		_nextBlock.special = rand() % 4 + 8;
	else
		_nextBlock.special = 0;

	switch (_nextBlock.color)
	{
	case 0:
		// けけけけ 鷺薫
		_nextBlock.block[3] = { 0, 0, 0, 0 };
		_nextBlock.block[2] = { 1, 1, 1, 1 };
		_nextBlock.block[1] = { 0, 0, 0, 0 };
		_nextBlock.block[0] = { 0, 0, 0, 0 };
		break;
	case 1:
		//    け
		// けけけ 鷺薫
		_nextBlock.block[3] = { 0, 0, 0, 0 };
		_nextBlock.block[2] = { 0, 0, 1, 0 };
		_nextBlock.block[1] = { 1, 1, 1, 0 };
		_nextBlock.block[0] = { 0, 0, 0, 0 };
		break;
	case 2:
		// け
		// けけけ 鷺薫
		_nextBlock.block[3] = { 0, 0, 0, 0 };
		_nextBlock.block[2] = { 1, 0, 0, 0 };
		_nextBlock.block[1] = { 1, 1, 1, 0 };
		_nextBlock.block[0] = { 0, 0, 0, 0 };
		break;
	case 3:
		//   け
		// けけけ 鷺薫
		_nextBlock.block[3] = { 0, 0, 0, 0 };
		_nextBlock.block[2] = { 0, 1, 0, 0 };
		_nextBlock.block[1] = { 1, 1, 1, 0 };
		_nextBlock.block[0] = { 0, 0, 0, 0 };
		break;
	case 4:
		// けけ
		//   けけ 鷺薫
		_nextBlock.block[3] = { 0, 0, 0, 0 };
		_nextBlock.block[2] = { 1, 1, 0, 0 };
		_nextBlock.block[1] = { 0, 1, 1, 0 };
		_nextBlock.block[0] = { 0, 0, 0, 0 };
		break;
	case 5:
		//   けけ
		// けけ 鷺薫
		_nextBlock.block[3] = { 0, 0, 0, 0 };
		_nextBlock.block[2] = { 0, 1, 1, 0 };
		_nextBlock.block[1] = { 1, 1, 0, 0 };
		_nextBlock.block[0] = { 0, 0, 0, 0 };
		break;
	case 6:
		// けけ
		// けけ 鷺薫
		_nextBlock.block[3] = { 0, 0, 0, 0 };
		_nextBlock.block[2] = { 0, 1, 1, 0 };
		_nextBlock.block[1] = { 0, 1, 1, 0 };
		_nextBlock.block[0] = { 0, 0, 0, 0 };
		break;
	}

	if (_nextBlock.special)
	{
		int specialCount = rand() % 4;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (_nextBlock.block[i][j])
				{
					if (specialCount == 0)
					{
						_nextBlock.specialIndex = { j, i };
						break;
					}

					specialCount--;
				}
			}
		}
	}
	
	if (!checkCrush(DOWN))
		_gameover = true;
}

void tetris::holdBlock()
{
	if (_hold)
	{
		tagBlock blockBuf;

		blockBuf.color = _holdBlock.color;
		blockBuf.special = _holdBlock.special;
		blockBuf.specialIndex = _holdBlock.specialIndex;
		blockBuf.block.push_back(_holdBlock.block[0]);
		blockBuf.block.push_back(_holdBlock.block[1]);
		blockBuf.block.push_back(_holdBlock.block[2]);
		blockBuf.block.push_back(_holdBlock.block[3]);

		_holdBlock.color = _controlBlock.color;
		_holdBlock.special = _controlBlock.special;

		vector<vector<bool>> vvBuffer;

		while (_controlBlock.rotationCount != 0)
		{
			vvBuffer.push_back(_controlBlock.block[0]);
			vvBuffer.push_back(_controlBlock.block[1]);
			vvBuffer.push_back(_controlBlock.block[2]);
			vvBuffer.push_back(_controlBlock.block[3]);

			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					vvBuffer[j][3 - i] = _controlBlock.block[i][j];
				}
			}

			_controlBlock.block.clear();
			_controlBlock.block.push_back(vvBuffer[0]);
			_controlBlock.block.push_back(vvBuffer[1]);
			_controlBlock.block.push_back(vvBuffer[2]);
			_controlBlock.block.push_back(vvBuffer[3]);
			_controlBlock.specialIndex = { 3 - _controlBlock.specialIndex.y, _controlBlock.specialIndex.x };

			if (_controlBlock.rotationCount < 3)
				_controlBlock.rotationCount++;
			else
				_controlBlock.rotationCount = 0;
		}

		vvBuffer.~vector();

		_holdBlock.specialIndex = _controlBlock.specialIndex;
		_holdBlock.block.clear();
		_holdBlock.block.push_back(_controlBlock.block[0]);
		_holdBlock.block.push_back(_controlBlock.block[1]);
		_holdBlock.block.push_back(_controlBlock.block[2]);
		_holdBlock.block.push_back(_controlBlock.block[3]);

		if (blockBuf.color == -1)
		{
			_idx = (WIDTH - 4) / 2;
			_idy = HEIGHT - 4;
			_ghostY = _idy;

			makeBlock();

			while (moveBlock(DEFAULT));
		}
		else
		{
			_idx = (WIDTH - 4) / 2;
			_idy = HEIGHT - 4;
			_ghostY = _idy;

			_controlBlock.block.clear();
			_controlBlock.block.push_back(blockBuf.block[0]);
			_controlBlock.block.push_back(blockBuf.block[1]);
			_controlBlock.block.push_back(blockBuf.block[2]);
			_controlBlock.block.push_back(blockBuf.block[3]);
			_controlBlock.color = blockBuf.color;
			_controlBlock.special = blockBuf.special;
			_controlBlock.specialIndex = blockBuf.specialIndex;

			while (moveBlock(DEFAULT));
		}

		_hold = false;
		blockBuf.block.~vector();
	}
}

void tetris::blockColor(int x, int y, int color, BYTE alpha)
{
	switch (color)
	{
	case 0:
		_blue->alphaRender(getMemDC(), x, y, alpha);
		break;
	case 1:
		_green->alphaRender(getMemDC(), x, y, alpha);
		break;
	case 2:
		_pink->alphaRender(getMemDC(), x, y, alpha);
		break;
	case 3:
		_purple->alphaRender(getMemDC(), x, y, alpha);
		break;
	case 4:
		_red->alphaRender(getMemDC(), x, y, alpha);
		break;
	case 5:
		_emerald->alphaRender(getMemDC(), x, y, alpha);
		break;
	case 6:
		_yellow->alphaRender(getMemDC(), x, y, alpha);
		break;
	case 7:
		_grey->alphaRender(getMemDC(), x, y, alpha);
		break;
	case 8:
		_atkBuff->alphaRender(getMemDC(), x, y, alpha);
		break;
	case 9:
		_atkDebuff->alphaRender(getMemDC(), x, y, alpha);
		break;
	case 10:
		_poison->alphaRender(getMemDC(), x, y, alpha);
		break;
	case 11:
		_recovery->alphaRender(getMemDC(), x, y, alpha);
		break;
	}
}

bool tetris::checkCrush(tagDirection dir)
{
	switch (dir)
	{
	case LEFT:
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (_controlBlock.block[i][j])
				{
					if (_board[i + _idy][j + _idx - 1].block || _board[i + _idy][j + _idx - 1].wall)
						return false;
					else
						break;
				}
			}
		}
		break;
	case RIGHT:
		for (int i = 0; i < 4; i++)
		{
			for (int j = 3; j >= 0; j--)
			{
				if (_controlBlock.block[i][j])
				{
					if (_board[i + _idy][j + _idx + 1].block || _board[i + _idy][j + _idx + 1].wall)
						return false;
					else
						break;
				}
			}
		}
		break;
	case DOWN:
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (_controlBlock.block[j][i])
				{
					if (_board[j + _idy - 1][i + _idx].block || _board[j + _idy - 1][i + _idx].wall)
						return false;
					else
						break;
				}
			}
		}
		break;
	case DEFAULT:
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (_controlBlock.block[j][i])
				{
					if (_board[j + _ghostY][i + _idx].block || _board[j + _ghostY][i + _idx].wall)
						return false;
					else
						break;
				}
			}
		}
		break;
	}

	return true;
}

bool tetris::moveBlock(tagDirection dir)
{
	switch (dir)
	{
	case LEFT:
		if (checkCrush(dir))
		{
			_idx--;
			_ghostY = _idy;
			while (moveBlock(DEFAULT));
			_timer = GetTickCount64();

			return true;
		}
		break;
	case RIGHT:
		if (checkCrush(dir))
		{
			_idx++;
			_ghostY = _idy;
			while (moveBlock(DEFAULT));
			_timer = GetTickCount64();

			return true;
		}
		break;
	case DOWN:
		if (checkCrush(dir))
		{
			_idy--;
			_downTimer = GetTickCount64();

			return true;
		}
		else
		{
			SOUNDMANAGER->play("BlockDrop", SOUNDMANAGER->getEffectVolume());

			int erase = 0;

			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					if (_controlBlock.block[i][j])
					{
						_board[i + _idy][j + _idx].block = true;
						_board[i + _idy][j + _idx].color = _controlBlock.color;

						if (j == _controlBlock.specialIndex.x && i == _controlBlock.specialIndex.y)
							_board[i + _idy][j + _idx].special = _controlBlock.special;
					}
				}
			}

			for (int i = 1; i < 21; i++)
			{
				int count = 0;

				for (int j = 1; j < WIDTH - 1; j++)
				{
					if (_board[i][j].block)
						count++;
				}

				if (count == WIDTH - 2)
				{
					for (int k = i; k < HEIGHT - 1; k++)
					{
						for (int l = 1; l < WIDTH - 1; l++)
						{
							if (k == i)
							{
								switch (_board[i][l].special)
								{
								case 8:
									_atkBuffTimer = GetTickCount64();
									break;
								case 9:
									_atkDebuffTimer = GetTickCount64();
									break;
								case 10:
									_poisonTimer = GetTickCount64();
									break;
								case 11:
									_recoveryTimer = GetTickCount64();
									break;
								}
							}
							
							_board[k][l].block = _board[k + 1][l].block;
							_board[k][l].color = _board[k + 1][l].color;
							_board[k][l].special = _board[k + 1][l].special;
						}
					}

					erase++;
					i--;

					SOUNDMANAGER->play("BlockErase", SOUNDMANAGER->getEffectVolume());
				}
			}

			if (erase)
			{
				_combo.count++;
				_combo.line = erase + 1;
			}
			else
			{
				_combo.count = 0;
				_combo.line = 0;
			}

			_combo.timer = GetTickCount64();

			_idx = (WIDTH - 4) / 2;
			_idy = HEIGHT - 4;
			_ghostY = _idy;
			_hold = true;

			makeBlock();

			while (moveBlock(DEFAULT));

			return false;
		}
		break;
	case DEFAULT:
		if (checkCrush(dir))
		{
			_ghostY--;

			return true;
		}
		else
		{
			_ghostY++;

			return false;
		}
		break;
	}

	return false;
}

bool tetris::blockRotation()
{
	vector<vector<bool>> vvBuffer;
	int count = 0;

	vvBuffer.push_back(_controlBlock.block[0]);
	vvBuffer.push_back(_controlBlock.block[1]);
	vvBuffer.push_back(_controlBlock.block[2]);
	vvBuffer.push_back(_controlBlock.block[3]);

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (_board[j + _idy][3 - i + _idx + count].block)
				return false;
			else if (_board[j + _idy][3 - i + _idx + count].wall)
			{
				if (3 - i + _idx + count == 0)
				{
					i = -1;
					count++;
					break;
				}
				else if (3 - i + _idx + count == WIDTH - 1)
				{
					i = -1;
					count--;
					break;
				}
				else
					return false;
			}
			else
				vvBuffer[j][3 - i] = _controlBlock.block[i][j];
		}
	}

	_idx += count;

	_controlBlock.block.clear();
	_controlBlock.block.push_back(vvBuffer[0]);
	_controlBlock.block.push_back(vvBuffer[1]);
	_controlBlock.block.push_back(vvBuffer[2]);
	_controlBlock.block.push_back(vvBuffer[3]);
	_controlBlock.specialIndex = { 3 - _controlBlock.specialIndex.y, _controlBlock.specialIndex.x };

	if (_controlBlock.rotationCount < 3)
		_controlBlock.rotationCount++;
	else
		_controlBlock.rotationCount = 0;

	vvBuffer.~vector();

	_ghostY = _idy;
	while (moveBlock(DEFAULT));

	return true;
}

void tetris::comboRender(int x, int y)
{
	if (_combo.count > 1 && GetTickCount64() - _combo.timer <= 500)
	{
		int _x = x;
		int _y = y;

		int digitCount = 1;

		if (_combo.count > 9)
			digitCount++;

		_x -= _combo.img->getWidth() / 2 + digitCount * IMAGEMANAGER->findImage("BigNumber")->getFrameWidth() / 2;
		_y -= _combo.img->getHeight() / 2;

		_combo.img->render(getMemDC(), _x, _y);

		printNumber(_combo.count, _x + _combo.img->getWidth() + 10, _y);
	}
}

void tetris::printNumber(int num, int x, int y, float scale)
{
	int digit = 1;
	int digitCount = 1;

	while (num / digit >= 10)
	{
		digit *= 10;
		digitCount++;
	}

	for (int i = 0; ; i++, digit /= 10)
	{
		if (digit != 1)
			IMAGEMANAGER->scaleFrameRender("BigNumber", getMemDC(), x + IMAGEMANAGER->findImage("BigNumber")->getFrameWidth() * i, y, (num / digit) % 10, 0, scale);
		else
		{
			IMAGEMANAGER->scaleFrameRender("BigNumber", getMemDC(), x + IMAGEMANAGER->findImage("BigNumber")->getFrameWidth() * i, y, num % 10, 0, scale);
			break;
		}
	}
}

void tetris::nextBlockRender(int x, int y)
{
	int specialCount = 1;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (_nextBlock.block[i][j])
			{
				if (_nextBlock.color == 0 || _nextBlock.color == 6)
				{
					blockColor(x + 32 * j, y - 32 * i, _nextBlock.color);

					if (_nextBlock.special != 0 && j == _nextBlock.specialIndex.x && i == _nextBlock.specialIndex.y)
						blockColor(x + 32 * j, y - 32 * i, _nextBlock.special);
				}
				else
				{
					blockColor(x + 16 + 32 * j, y - 32 * i, _nextBlock.color);

					if (_nextBlock.special != 0 && j == _nextBlock.specialIndex.x && i == _nextBlock.specialIndex.y)
						blockColor(x + 16 + 32 * j, y - 32 * i, _nextBlock.special);
				}
			}
		}
	}
}

void tetris::holdBlockRender(int x, int y)
{
	int specialCount = 1;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (_holdBlock.block[i][j])
			{
				if (_holdBlock.color == 0 || _holdBlock.color == 6)
				{
					blockColor(x + 32 * j, y - 32 * i, _holdBlock.color);

					if (_holdBlock.special != 0 && j == _holdBlock.specialIndex.x && i == _holdBlock.specialIndex.y)
						blockColor(x + 32 * j, y - 32 * i, _holdBlock.special);
				}
				else
				{
					blockColor(x + 16 + 32 * j, y - 32 * i, _holdBlock.color);

					if (_holdBlock.special != 0 && j == _holdBlock.specialIndex.x && i == _holdBlock.specialIndex.y)
						blockColor(x + 16 + 32 * j, y - 32 * i, _holdBlock.special);
				}
			}
		}
	}
}