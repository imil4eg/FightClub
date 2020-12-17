#pragma once

#include "Characters/ICharacterFactory.h"
#include "IO/Savers/GameDataProcesser.h"
#include "IPlayerConfig.h"

namespace fightclub
{
	namespace core
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
}