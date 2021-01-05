#pragma once

#include "AttributeType.h"
#include "Characters/Character.h"

namespace fightclub
{
	namespace core
	{
		namespace characterstuff
		{
			class IAttributesManager
			{
			public:
				~IAttributesManager() = default;

				virtual void enterAttributesManager(characters::Character& character) = 0;
				virtual void increaseAttribute(characters::Character& character, AttributeType attributeType, int value) = 0;
				virtual void decreaseAttribute(characters::Character& character, AttributeType attributeType, int value) = 0;
				virtual int calculateLeftAttributePoints(characters::Character& character) const = 0;
			};
		}
	}
}