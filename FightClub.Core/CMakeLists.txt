cmake_minimum_required(VERSION 3.10)

project(FightClub.Core)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost 1.75.0)

include_directories(${Boost_INCLUDE_DIRS} src src/headers include libs)

link_directories(${Boost_LIBRARY_DIRS})

add_library(FightClub.Core STATIC src/Battle/Battle.cpp src/Characters/Bots/Bot.cpp src/Characters/Character.cpp src/CharacterStuff/Equipment.cpp src/CharacterStuff/Armors/Armor.cpp src/Characters/CharacterType.cpp src/Characters/Character.cpp src/Battle/Fighters/Fighter.cpp src/CharacterStuff/Abilities/AbilitiesContainer.cpp src/CharacterStuff/Abilities/Ability.cpp src/CharacterStuff/Abilities/DynamicAbilitiesContainer.cpp src/CharacterStuff/Abilities/AbilitiesStorage.cpp src/CharacterStuff/Abilities/AbilityType.cpp src/CharacterStuff/AttributesFactory.cpp src/CharacterStuff/BodyPart.cpp src/CharacterStuff/AttributeType.cpp src/CharacterStuff/Equipment.cpp src/CharacterStuff/Attributes.cpp src/CharacterStuff/BaseAttributesManager.cpp src/CharacterStuff/Inventory.cpp src/CharacterStuff/Weapons/Weapon.cpp src/CharacterStuff/Weapons/WeaponStorage.cpp src/CharacterStuff/Armors/ArmorStorage.cpp src/CharacterStuff/Armors/ArmorType.cpp src/Battle/DamageCalculator.cpp src/Battle/Fighters/BotFighter.cpp src/Battle/Fighters/FighterFactory.cpp src/Battle/Fighters/PlayerFighter.cpp src/Characters/CharacterFactory.cpp src/Characters/Player.cpp src/Characters/Bots/BotFactory.cpp src/Common/RandomGenerator.cpp src/Common/Configs/Config.cpp src/Common/Configs/ConfigKeys.cpp src/Common/Configs/PlayerConfig.cpp src/IO/JsonAttributes.cpp src/IO/Savers/JsonGameDataProcesser.cpp)

target_link_libraries(FightClub.Core ${Boost_LIBRARIES})
