#pragma once

#include "CharacterStuff/IAttributesFactory.h"
#include "ICharacterFactory.h"

namespace fightclub
{
	namespace core
	{
		namespace characters
		{
			class CharacterFactory : public ICharacterFactory
			{
			private:
				characterstuff::IAttributesFactory* m_attributesFactory;

			public:
				CharacterFactory(characterstuff::IAttributesFactory& attributesFactory) :
					m_attributesFactory{ &attributesFactory }
				{
				}

			public:
				std::unique_ptr<Player> createDefaultPlayer() override;
			};
		}
	}
}