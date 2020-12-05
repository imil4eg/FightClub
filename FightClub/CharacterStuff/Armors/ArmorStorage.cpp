#include <exception>

#include "ArmorStorage.h"
#include "../../Common/RandomGenerator.h"

const Armor* ArmorStorage::getOrDefault(const boost::uuids::uuid& id)
{
	if (m_armors.find(id) == m_armors.end())
	{
		return nullptr;
	}

	return m_armors.at(id);
}

const Armor* ArmorStorage::getRandom(Armor::Type armorType)
{
	int lowerBound;
	int upperBound;
	switch (armorType)
	{
	case Armor::Type::head:
		lowerBound = m_headStartIndex;
		upperBound = m_headEndIndex;
		break;
	case Armor::Type::body:
		lowerBound = m_cuirasseStartIndex;
		upperBound = m_cuirasseEndIndex;
		break;
	case Armor::Type::legs:
		lowerBound = m_legsStartIndex;
		upperBound = m_legsEndIndex;
		break;
	default:
		throw std::exception("Armor type not implemented.");
	}

	auto randomArmorId{ RandomGenerator::getBetween(lowerBound, upperBound) };

	if (randomArmorId == m_armorIds.size())
	{
		return nullptr;
	}

	return m_armors[m_armorIds[randomArmorId]];
}

void ArmorStorage::initializeArmors()
{
	auto* poorManHat{ new PoorManHat{} };
	m_armors.insert(std::make_pair(poorManHat->getId(), poorManHat));
	m_armorIds.push_back(poorManHat->getId());

	auto* averageHead{ new AverageFighterHat{} };
	m_armors.insert(std::make_pair(averageHead->getId(), averageHead));
	m_armorIds.push_back(averageHead->getId());

	auto* richHat{ new RichGuyHat{} };
	m_armors.insert(std::make_pair(richHat->getId(), richHat));
	m_armorIds.push_back(richHat->getId());

	auto* poorManCuirasse{ new PoorManCuirasse{} };
	m_armors.insert(std::make_pair(poorManCuirasse->getId(), poorManCuirasse));
	m_armorIds.push_back(poorManHat->getId());

	auto* averageCuirasse{ new AverageFighterCuirasse{} };
	m_armors.insert(std::make_pair(averageCuirasse->getId(), averageCuirasse));
	m_armorIds.push_back(averageCuirasse->getId());

	auto* richCuirasse{ new RichGuyCuirasse{} };
	m_armors.insert(std::make_pair(richCuirasse->getId(), richCuirasse));
	m_armorIds.push_back(richCuirasse->getId());

	auto* poorManLegs{ new PoorManLegs{} };
	m_armors.insert(std::make_pair(poorManLegs->getId(), poorManLegs));
	m_armorIds.push_back(poorManLegs->getId());

	auto averageLegs{ new AverageFighterLegs{} };
	m_armors.insert(std::make_pair(averageLegs->getId(), averageLegs));
	m_armorIds.push_back(averageLegs->getId());

	auto* richLegs{ new RichGuyLegs{} };
	m_armors.insert(std::make_pair(richLegs->getId(), richLegs));
	m_armorIds.push_back(richLegs->getId());
}