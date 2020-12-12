#ifndef PLAYER_CONFIG_H
#define PLAYER_CONFIG_H

#include <memory>
#include <vector>

#include "IPlayerConfig.h"
#include "Characters/ICharacterFactory.h"
#include "CharacterStuff/Armors/Armor.h"
#include "IO/Savers/GameDataProcesser.h"

namespace fightclub
{
	namespace common
	{
		namespace configs
		{
			class PlayerConfig : public IPlayerConfig
			{
			private:
				std::unique_ptr<characters::Player> m_player;

				io::savers::GameDataProcesser* m_gameDataProcesser;
				characters::ICharacterFactory* m_characterFactory;

			public:
				PlayerConfig(io::savers::GameDataProcesser* gameDataProcesser,
					characters::ICharacterFactory* characterFactory) :
					m_gameDataProcesser{ gameDataProcesser },
					m_characterFactory{ characterFactory }
				{
				}

				void initialize() override;
				characters::Player* getCharacter() override;
			};
		}
	}
}

#endif // !PLAYER_CONFIG_H

