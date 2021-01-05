#pragma once

#include "IAttributesManager.h"
#include "IAttributesFactory.h"

namespace fightclub
{
	namespace core
	{
		namespace characterstuff
		{
			class BaseAttributesManager : public IAttributesManager
			{
			private:
				struct Impl;
				std::unique_ptr<Impl> pImpl;

			protected:
				void saveChanges(characters::Character& character);

			public:
				BaseAttributesManager(IAttributesFactory& attributesFactory);
				virtual ~BaseAttributesManager();

				void increaseAttribute(characters::Character& character, AttributeType attributeType, int value) override;
				void decreaseAttribute(characters::Character& character, AttributeType attributeType, int value) override;
				int calculateLeftAttributePoints(characters::Character& character) const override;
			};
		}
	}
}