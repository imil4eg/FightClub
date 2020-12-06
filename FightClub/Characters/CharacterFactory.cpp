#include "CharacterFactory.h"
#include "Player.h"

Character* CharacterFactory::createDefaultPlayer()
{
	auto attributes{ m_attributesFactory->create(nullptr, 1, 0, 0, CharacterType::strong) };
	auto equipment = new Equipment{};

	return new Player{&attributes, equipment, CharacterType::strong};
}