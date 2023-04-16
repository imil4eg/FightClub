#include <iostream>

#include "CharacterStuff/CharacterCustomizer.h"

namespace fightclub
{
	namespace characterstuff
	{
		void CharacterCustomizer::changeAttributes(
			core::characterstuff::Attributes& attributes)
		{
			int freeAttributePoints = (attributes.getLevel() * m_attributePerLevel) - (attributes.getAgility() + attributes.getStrength());

			std::cout << "Attribute points left: " << freeAttributePoints;

			std::cout << "Current attributes:\n" << attributes << '\n';

			if (freeAttributePoints == 0)
			{
				return;
			}

			while (true)
			{
				std::cout << "Enter attribute name and points counts to add.";
			}
		}
	}
}