#include "stdafx.h"
#include "gameLoading.h"

HRESULT gameLoading::init()
{
	// 로딩
	_loading = new loading;
	_loading->init();

	// 리스트 등록
	this->soundList();
	this->imageList();

	return S_OK;
}

void gameLoading::release()
{
	_loading->release();
	SAFE_DELETE(_loading);
}

void gameLoading::update()
{
	// 로딩
	_loading->update();

	// 로딩에 있는 BGM 실행
	if (!SOUNDMANAGER->isPlaySound("MainBgm"))
		SOUNDMANAGER->play("MainBgm");

	// 로딩이 완료되고 화면을 누를시 게임 시작
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (_loading->getDone())
		{
			SCENEMANAGER->loadScene("Main");
		}
	}
}

void gameLoading::render()
{
	// 로딩
	_loading->render();
}

void gameLoading::imageList()
{
	// 블럭 이미지
	_loading->loadImage("BlueBlock", "Img/Block/blueBlock.bmp", 32, 32);
	_loading->loadImage("GreyBlock", "Img/Block/greyBlock.bmp", 32, 32);
	_loading->loadImage("GreenBlock", "Img/Block/greenBlock.bmp", 32, 32);
	_loading->loadImage("RedBlock", "Img/Block/redBlock.bmp", 32, 32);
	_loading->loadImage("YellowBlock", "Img/Block/yellowBlock.bmp", 32, 32);
	_loading->loadImage("EmeraldBlock", "Img/Block/emeraldBlock.bmp", 32, 32);
	_loading->loadImage("BrownBlock", "Img/Block/brownBlock.bmp", 32, 32);
	_loading->loadImage("PinkBlock", "Img/Block/pinkBlock.bmp", 32, 32);
	_loading->loadImage("PurpleBlock", "Img/Block/purpleBlock.bmp", 32, 32);
	_loading->loadImage("AtkBuff", "Img/Block/atkBuff.bmp", 32, 32, true, RGB(255, 0, 255));
	_loading->loadImage("AtkDebuff", "Img/Block/atkDebuff.bmp", 32, 32, true, RGB(255, 0, 255));
	_loading->loadImage("Recovery", "Img/Block/recovery.bmp", 32, 32, true, RGB(255, 0, 255));
	_loading->loadImage("Poison", "Img/Block/poison.bmp", 32, 32, true, RGB(255, 0, 255));

	// 스킬
	_loading->loadImage("SkillCoolTime", "Img/Skill/skillCoolTime.bmp", 50, 50);
	_loading->loadImage("SlowSkill", "Img/Skill/Slow.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->loadImage("LongBlockSkill", "Img/Skill/Long_block.bmp", 50, 50, true, RGB(255, 0, 255));

	// 메인 UI
	_loading->loadImage("MenuBackGround", "Img/Bg/menuBg.bmp", 540, 1800);
	_loading->loadImage("TetrisBoard", "Img/UI/tetrisBoard.bmp", (WINSIZEX - BOARD_WIDTH) / 2, WINSIZEY - 650, 328, 648, true, RGB(255, 0, 255));
	_loading->loadImage("FieldGlass", "Img/UI/fieldGlass.bmp", (WINSIZEX - BOARD_WIDTH + 4) / 2, 12, BOARD_WIDTH - 4, 296, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Character", "Img/UI/character.bmp", WINSIZEX / 2 + 180, WINSIZEY - 500, 316, 81, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Battle", "Img/UI/battle.bmp", WINSIZEX / 2 + 180, WINSIZEY - 400, 316, 81, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Shop", "Img/UI/shop.bmp", WINSIZEX / 2 + 180, WINSIZEY - 300, 316, 81, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Option", "Img/UI/option.bmp", WINSIZEX / 2 + 180, WINSIZEY - 200, 316, 81, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Exit", "Img/UI/exit.bmp", WINSIZEX / 2 + 180, WINSIZEY - 100, 316, 81, 4, 1, true, RGB(255, 0, 255));
	_loading->loadImage("ScreenOut", "Img/UI/screenOut.bmp", 0, WINSIZEY, 560, 2058, true, RGB(255, 0, 255));

	// 옵션 UI
	_loading->loadImage("PopUp", "Img/UI/popupBoard.bmp", 372, 312, true, RGB(255, 0, 255));
	_loading->loadFrameImage("BgSound", "Img/UI/bgSound.bmp", 158, 81, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("EffectSound", "Img/UI/effectSound.bmp", 158, 81, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Keypad", "Img/UI/keypad.bmp", 158, 81, 2, 1, true, RGB(255, 0, 255));

	// 종료 UI
	_loading->loadImage("AskBoard", "Img/UI/askBoard.bmp", 436, 255, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Ok", "Img/UI/ok.bmp", 316, 81, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Close", "Img/UI/close.bmp", 316, 81, 4, 1, true, RGB(255, 0, 255));

	// 키 UI
	_loading->loadImage("KeyBoard", "Img/UI/keyBoard.bmp", 372, 720, true, RGB(255, 0, 255));
	_loading->loadImage("DirKeyFront", "Img/UI/dirKeyFront.bmp", 150, 40, true, RGB(255, 0, 255));
	_loading->loadImage("DirKeyBack", "Img/UI/dirKeyBack.bmp", 100, 40, true, RGB(255, 0, 255));

	// 숫자
	_loading->loadFrameImage("Number", "Img/UI/number.bmp", 120, 18, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("MidNumber", "Img/UI/midNumber.bmp", 250, 38, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("BigNumber", "Img/UI/Bignumber.bmp", 480, 73, 10, 1, true, RGB(255, 0, 255));

	// 플레이어
	_loading->loadImage("Room1", "Img/Player/room1.bmp", (WINSIZEX - BOARD_WIDTH) / 2, 10, 500, 300, false);
	_loading->loadFrameImage("Player", "Img/Player/Fumiko.bmp", (WINSIZEX - 72) / 2, 180, 1224, 768, 17, 8, true, RGB(255, 0, 255));
	_loading->loadFrameImage("PlayerDamaged", "Img/Player/FumikoDamaged.bmp", (WINSIZEX - 72) / 2, 180, 1224, 768, 17, 8, true, RGB(255, 0, 255));

	// 인벤토리
	_loading->loadImage("EquipHelmet", "Img/Inventory/helmet.bmp", INVENTORY_IMAGE_SIZE, INVENTORY_IMAGE_SIZE);
	_loading->loadImage("EquipWeapon", "Img/Inventory/weapon.bmp", INVENTORY_IMAGE_SIZE, INVENTORY_IMAGE_SIZE);
	_loading->loadImage("EquipArmor", "Img/Inventory/armor.bmp", INVENTORY_IMAGE_SIZE, INVENTORY_IMAGE_SIZE);
	_loading->loadImage("EquipShield", "Img/Inventory/shield.bmp", INVENTORY_IMAGE_SIZE, INVENTORY_IMAGE_SIZE);
	_loading->loadImage("EquipBelt", "Img/Inventory/belt.bmp", INVENTORY_IMAGE_SIZE, INVENTORY_IMAGE_SIZE);
	_loading->loadImage("EquipShoes", "Img/Inventory/shoes.bmp", INVENTORY_IMAGE_SIZE, INVENTORY_IMAGE_SIZE);
	_loading->loadImage("EquipNecklace", "Img/Inventory/necklace.bmp", INVENTORY_IMAGE_SIZE, INVENTORY_IMAGE_SIZE);
	_loading->loadImage("Slot", "Img/Inventory/slot.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->loadImage("Selected", "Img/Inventory/selected.bmp", 60, 64, true, RGB(255, 0, 255));
	_loading->loadImage("Status", "Img/Inventory/status.bmp", 136, 220, true, RGB(255, 0, 255));
	_loading->loadImage("HP", "Img/Inventory/hp.bmp", 130, 32, true, RGB(255, 0, 255));
	_loading->loadImage("Atk", "Img/Inventory/atk.bmp", 130, 32, true, RGB(255, 0, 255));
	_loading->loadImage("Def", "Img/Inventory/def.bmp", 130, 32, true, RGB(255, 0, 255));

	// 골드
	_loading->loadImage("Gold", "Img/UI/gold.bmp", 34, 34, true, RGB(255, 0, 255));
	_loading->loadImage("Buy", "Img/UI/buyCost.bmp", 57, 20, true, RGB(255, 0, 255));
	_loading->loadImage("Sell", "Img/UI/sellCost.bmp", 61, 20, true, RGB(255, 0, 255));

	// 아이템
	_loading->loadImage("Cloth", "Img/Item/cloth.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->loadImage("Plate", "Img/Item/plate.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->loadImage("BasicBook", "Img/Item/basicBook.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->loadImage("StandardBook", "Img/Item/standardBook.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->loadImage("ShortDagger", "Img/Item/shortDagger.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->loadImage("Dagger", "Img/Item/dagger.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->loadImage("LiteHelm", "Img/Item/liteHelm.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->loadImage("Helm", "Img/Item/helm.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->loadImage("SmallShield", "Img/Item/smallShield.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->loadImage("LargeShield", "Img/Item/LargeShield.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->loadImage("HolyNecklace", "Img/Item/holyNecklace.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->loadImage("RubyNecklace", "Img/Item/RubyNeck.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->loadImage("Shoes", "Img/Item/shoes.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->loadImage("IronShoes", "Img/Item/ironShoes.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->loadImage("SmallPotion", "Img/Item/smallPotion.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->loadImage("LargePotion", "Img/Item/largePotion.bmp", 50, 50, true, RGB(255, 0, 255));

	// 전투
	_loading->loadImage("BattleBg", "Img/Battle/bg.bmp", 540, 960);
	_loading->loadImage("Stage", "Img/Battle/stage.bmp", 113, 26, true, RGB(255, 0, 255));
	_loading->loadImage("StageBoard", "Img/Battle/stageBoard.bmp", 200, 57, true, RGB(255, 0, 255));
	_loading->loadImage("Combo", "Img/Battle/Combo.bmp", 312, 77, true, RGB(255, 0, 255));
	_loading->loadImage("NextBlock", "Img/Battle/nextBlock.bmp", WINSIZEX - 180, WINSIZEY / 2 - 150, 160, 200, true, RGB(255, 0, 255));
	_loading->loadImage("HoldBlock", "Img/Battle/holdBlock.bmp", WINSIZEX - 180, WINSIZEY / 2 + 70, 160, 200, true, RGB(255, 0, 255));
	_loading->loadImage("Evasion", "Img/Battle/evasion.bmp", 75, 18, true, RGB(255, 0, 255));
	_loading->loadImage("ActiveSlot", "Img/Battle/activeSlot.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->loadImage("RewardBoard", "Img/Battle/rewardBoard.bmp", 372, 600, true, RGB(255, 0, 255));
	_loading->loadImage("GoldReward", "Img/Battle/goldReward.bmp", 87, 39, true, RGB(255, 0, 255));
	_loading->loadImage("ItemReward", "Img/Battle/itemReward.bmp", 93, 35, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Home", "Img/Battle/home.bmp", 316, 81, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Replay", "Img/Battle/replay.bmp", 316, 81, 4, 1, true, RGB(255, 0, 255));
	_loading->loadImage("BattleRoom", "Img/Battle/battleRoom.bmp", (WINSIZEX - BOARD_WIDTH) / 2, 10, 500, 300, false);

	// 에너미
	_loading->loadFrameImage("BlueStone", "Img/Enemy/BlueStone.bmp", 261, 131, 2, 1, false);
	_loading->loadFrameImage("DarkBrownStone", "Img/Enemy/DarkBrownStone.bmp", 261, 131, 2, 1, false);
	_loading->loadFrameImage("GreenStone", "Img/Enemy/GreenStone.bmp", 261, 131, 2, 1, false);
	_loading->loadFrameImage("OrangeStone", "Img/Enemy/OrangeStone.bmp", 261, 131, 2, 1, false);
	_loading->loadFrameImage("FullColorStone", "Img/Enemy/fullColor.bmp", 261, 131, 2, 1, false);
	_loading->loadImage("StoneDamaged", "Img/Enemy/StoneDamaged.bmp", 131, 131, false);
}

void gameLoading::soundList()
{
	// 배경
	_loading->loadSound("MainBgm", "GameSound/Bgm/11_Fill Me Up.mp3", true, true);
	_loading->loadSound("BattleBgm", "GameSound/Bgm/Charangos.mp3", true, true);
	
	// 승패
	_loading->loadSound("Victory", "GameSound/Bgm/victory.wav", true, false);
	_loading->loadSound("Lose", "GameSound/Bgm/lose.wav", true, false);
	
	// 마우스
	_loading->loadSound("MouseOver", "GameSound/Effect/MouseOver.wav", false, false);
	_loading->loadSound("Click", "GameSound/Effect/Click.wav", false, false);
	
	// 테트리스
	_loading->loadSound("BlockDrop", "GameSound/Effect/BlockDrop.wav", false, false);
	_loading->loadSound("BlockErase", "GameSound/Effect/BlockErase.mp3", false, false);
	_loading->loadSound("BlockMove", "GameSound/Effect/BlockMove.wav", false, false);
}
