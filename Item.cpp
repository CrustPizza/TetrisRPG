#include "stdafx.h"
#include "Item.h"

HRESULT Item::init()
{
	// Weapon
	setData(WEAPON, "Dagger", 5, 1500);
	setData(WEAPON, "ShortDagger", 3, 1000);

	// Helmet
	setData(HELMET, "Helm", 5, 1500);
	setData(HELMET, "LiteHelm", 3, 1000);

	// Necklace
	setData(NECKLACE, "RubyNecklace", 2, 700);
	setData(NECKLACE, "HolyNecklace", 1, 300);

	// Armor
	setData(ARMOR, "Plate", 5, 1500);
	setData(ARMOR, "Cloth", 1, 300);

	// Shield
	setData(SHIELD, "LargeShield", 3, 1000);
	setData(SHIELD, "SmallShield", 1, 300);

	// Belt
	setData(BELT, "StandardBook", 100, 1500);
	setData(BELT, "BasicBook", 50, 800);

	// Shoes
	setData(SHOES, "IronShoes", 5, 1500);
	setData(SHOES, "Shoes", 3, 800);

	// Potion
	setData(POTION, "LargePotion", 100, 1500);
	setData(POTION, "SmallPotion", 50, 500);

	return S_OK;
}

void Item::release()
{
	// 초기화
	_weapon.clear();
	_armor.clear();
	_helmet.clear();
	_necklace.clear();
	_shield.clear();
	_belt.clear();
	_shoes.clear();
}

void Item::update()
{
}

void Item::render()
{
}

tagItemData Item::getData(tagType type, string name)
{
	// 유형별 아이템 받아오기
	switch (type)
	{
	case WEAPON:
		if (_weapon.find(name) != _weapon.end())
			return _weapon.find(name)->second;
		else
			return {};
		break;
	case ARMOR:
		if (_armor.find(name) != _armor.end())
			return _armor.find(name)->second;
		else
			return {};
		break;
	case HELMET:
		if (_helmet.find(name) != _helmet.end())
			return _helmet.find(name)->second;
		else
			return {};
		break;
	case NECKLACE:
		if (_necklace.find(name) != _necklace.end())
			return _necklace.find(name)->second;
		else
			return {};
		break;
	case SHIELD:
		if (_shield.find(name) != _shield.end())
			return _shield.find(name)->second;
		else
			return {};
		break;
	case BELT:
		if (_belt.find(name) != _belt.end())
			return _belt.find(name)->second;
		else
			return {};
		break;
	case SHOES:
		if (_shoes.find(name) != _shoes.end())
			return _shoes.find(name)->second;
		else
			return {};
		break;
	case POTION:
		if (_potion.find(name) != _potion.end())
			return _potion.find(name)->second;
		else
			return {};
		break;
	case TYPE_END:
		return {};
		break;
	}
}

map<string, tagItemData>* Item::getDataMap(tagType type)
{
	// 아이템 저장하기
	switch (type)
	{
	case WEAPON:
		return &_weapon;
		break;
	case ARMOR:
		return &_armor;
		break;
	case HELMET:
		return &_helmet;
		break;
	case NECKLACE:
		return &_necklace;
		break;
	case SHIELD:
		return &_shield;
		break;
	case BELT:
		return &_belt;
		break;
	case SHOES:
		return &_shoes;
		break;
	case POTION:
		return &_potion;
		break;
	}
}

void Item::setData(tagType type, string name, int value, int cost)
{
	// 아이템 저장하기
	switch (type)
	{
	case WEAPON:
		_weapon[name] = { type, name, value, cost };
		break;
	case ARMOR:
		_armor[name] = { type, name, value, cost };
		break;
	case HELMET:
		_helmet[name] = { type, name, value, cost };
		break;
	case NECKLACE:
		_necklace[name] = { type, name, value, cost };
		break;
	case SHIELD:
		_shield[name] = { type, name, value, cost };
		break;
	case BELT:
		_belt[name] = { type, name, value, cost };
		break;
	case SHOES:
		_shoes[name] = { type, name, value, cost };
		break;
	case POTION:
		_potion[name] = { type, name, value, cost };
		break;
	}
}

void Item::randomItemSet(tagType* type, string* name)
{
	tagType _type = (tagType)((int)(((float)rand() / RAND_MAX) * TYPE_END) % TYPE_END);
	string _name;
	int rnd;

	// 아이템 저장하기
	switch (_type)
	{
	case WEAPON:
		rnd = _weapon.size();
		rnd = rand() % rnd;
		for (map<string, tagItemData>::iterator iter = _weapon.begin(); iter != _weapon.end(); iter++)
		{
			if (rnd == 0)
			{ 
				_name = iter->first;
				break;
			}
			else
				rnd--;
		}
		break;
	case ARMOR:
		rnd = _armor.size();
		rnd = rand() % rnd;
		for (map<string, tagItemData>::iterator iter = _armor.begin(); iter != _armor.end(); iter++)
		{
			if (rnd == 0)
			{ 
				_name = iter->first;
				break;
			}
			else
				rnd--;
		}
		break;
	case HELMET:
		rnd = _helmet.size();
		rnd = rand() % rnd;
		for (map<string, tagItemData>::iterator iter = _helmet.begin(); iter != _helmet.end(); iter++)
		{
			if (rnd == 0)
			{ 
				_name = iter->first;
				break;
			}
			else
				rnd--;
		}
		break;
	case NECKLACE:
		rnd = _necklace.size();
		rnd = rand() % rnd;
		for (map<string, tagItemData>::iterator iter = _necklace.begin(); iter != _necklace.end(); iter++)
		{
			if (rnd == 0)
			{ 
				_name = iter->first;
				break;
		}
			else
				rnd--;
		}
		break;
	case SHIELD:
		rnd = _shield.size();
		rnd = rand() % rnd;
		for (map<string, tagItemData>::iterator iter = _shield.begin(); iter != _shield.end(); iter++)
		{
			if (rnd == 0)
			{
				_name = iter->first;
				break;
			}
			else
				rnd--;
		}
		break;
	case BELT:
		rnd = _belt.size();
		rnd = rand() % rnd;
		for (map<string, tagItemData>::iterator iter = _belt.begin(); iter != _belt.end(); iter++)
		{
			if (rnd == 0)
			{
				_name = iter->first;
				break;
			}
			else
				rnd--;
		}
		break;
	case SHOES:
		rnd = _shoes.size();
		rnd = rand() % rnd;
		for (map<string, tagItemData>::iterator iter = _shoes.begin(); iter != _shoes.end(); iter++)
		{
			if (rnd == 0)
			{ 
				_name = iter->first;
				break;
			}
			else
				rnd--;
		}
		break;
	case POTION:
		rnd = _potion.size();
		rnd = rand() % rnd;
		for (map<string, tagItemData>::iterator iter = _potion.begin(); iter != _potion.end(); iter++)
		{
			if (rnd == 0)
			{ 
				_name = iter->first;
				break;
			}
			else
				rnd--;
		}
		break;
	}

	*type = _type;
	*name = _name;
}