// FightClub.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <memory>
#include <iostream>

#include "CharacterStuff/AttributesFactory.h"
#include "Battle/Battle.h"
#include "Characters/Bots/BotFactory.h"
#include "IO/Savers/GameDataProcesser.h"
#include "CharacterStuff/Armors/ArmorStorage.h"
#include "CharacterStuff/IAttributesFactory.h"
#include "CharacterStuff/Armors/IArmorStorage.h"
#include "CharacterStuff/WeaponStorage.h"
#include "Characters/ICharacterFactory.h"
#include "Characters/CharacterFactory.h"
#include "Battle/IBattle.h"
#include "Characters/Bots/IBotFactory.h"
#include "Common/Configs/Config.h"
#include "Common/Configs/IConfig.h"
#include "Common/Configs/IPlayerConfig.h"
#include "Common/Configs/PlayerConfig.h"
#include "IMenu.h"
#include "CharacterStuff/IWeaponStorage.h"
#include "IO/Savers/JsonGameDataProcesser.h"
#include "Menu.h"

int main()
{

	Config config{ "config.txt" };
	AttributesFactory attributesFactory{};
	WeaponStorage weaponStorage{};
	ArmorStorage armorStorage{};
	JsonGameDataProcesser jsonGameDataProcesser{ &attributesFactory, &weaponStorage, &armorStorage, &config };
	CharacterFactory characterFactory{ &attributesFactory };
	PlayerConfig playerConfig{ &jsonGameDataProcesser, &characterFactory };
	BotFactory botFactory{ &attributesFactory, &weaponStorage, &armorStorage };
	Battle battle{ &botFactory };
	Menu menu{ &battle, &playerConfig, &jsonGameDataProcesser };

	srand(static_cast<unsigned int>(time(0)));
	
	menu.show();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
