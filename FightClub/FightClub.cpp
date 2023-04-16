// FightClub.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <memory>
#include <iostream>

#include "Menu.h"
#include "Battle/Battle.h"
#include "Battle/Fighters/FighterFactory.h"
#include "Characters/CharacterFactory.h"
#include "Characters/Bots/BotFactory.h"
#include "CharacterStuff/InventoryManager.h"
#include "CharacterStuff/AbilitiesDisplayer.h"
#include "CharacterStuff/AttributesFactory.h"
#include "CharacterStuff/Weapons/WeaponStorage.h"
#include "CharacterStuff/Armors/ArmorStorage.h"
#include "CharacterStuff/Abilities/AbilitiesStorage.h"
#include "CharacterStuff/AbilitiesManager.h"
#include "CharacterStuff/AttributesManager.h"
#include "Common/Configs/Config.h"
#include "Common/Configs/PlayerConfig.h"
#include "IO/MessageDisplayer.h"
#include "IO/InputProcesser.h"
#include "IO/Savers/JsonGameDataProcesser.h"
#include "IO/CommandLineParser.h"

int main()
{

	fightclub::core::common::configs::Config config{ "config.txt" };
	fightclub::io::InputProcesser inputProcesser{};
	fightclub::characterstuff::InventoryManager inventoryManager{inputProcesser};
	fightclub::io::MessageDisplayer messageDisplayer{};
	fightclub::characterstuff::AbilitiesDisplayer abilitiesDisplayer{};
	fightclub::core::battle::fighters::FighterFactory fighterFactory{messageDisplayer, inputProcesser, abilitiesDisplayer};
	fightclub::core::characterstuff::AttributesFactory attributesFactory{};
	fightclub::core::characterstuff::weapons::WeaponStorage weaponStorage{ config };
	fightclub::core::characterstuff::armors::ArmorStorage armorStorage{ config };
	fightclub::core::characterstuff::abilities::AbilitiesStorage abilitiesStorage{ config };
	fightclub::core::io::savers::JsonGameDataProcesser jsonGameDataProcesser{ attributesFactory, weaponStorage, armorStorage, abilitiesStorage, config };
	fightclub::core::characters::CharacterFactory characterFactory{ attributesFactory };
	fightclub::core::common::configs::PlayerConfig playerConfig{ jsonGameDataProcesser, characterFactory };
	fightclub::core::characters::bots::BotFactory botFactory{ attributesFactory, weaponStorage, armorStorage, abilitiesStorage };
	fightclub::core::battle::Battle battle{ botFactory, fighterFactory, messageDisplayer };
	fightclub::io::CommandLineParser commandLineParser{};
	fightclub::characterstuff::AttributesManager attributesManager{ inputProcesser, attributesFactory, commandLineParser };
	fightclub::characterstuff::AbilitiesManager abilitiesManager{ inputProcesser, abilitiesDisplayer };
	fightclub::Menu menu{ battle, playerConfig, jsonGameDataProcesser, inputProcesser, inventoryManager, attributesManager, abilitiesManager };
	
	srand(static_cast<unsigned int>(time(0)));

	playerConfig.initialize();

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
