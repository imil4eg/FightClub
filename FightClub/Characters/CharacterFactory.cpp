#include "Characters/CharacterFactory.h"
#include "Characters/Player.h"

std::unique_ptr<Character> CharacterFactory::createDefaultPlayer()
{
	auto attributes{ m_attributesFactory->create(nullptr, 1, 0, 0, CharacterType::strong) };
	auto equipment{ std::make_unique<Equipment>() };

	return std::make_unique<Player>(std::move(attributes), std::move(equipment), CharacterType::strong);
}