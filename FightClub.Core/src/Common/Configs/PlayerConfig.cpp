#include "Common/Configs/PlayerConfig.h"

namespace fightclub
{
	namespace core
	{
		namespace common
		{
			namespace configs
			{
				struct PlayerConfig::Impl
				{
					std::unique_ptr<characters::Player> m_player;

					io::savers::GameDataProcesser* m_gameDataProcesser;
					characters::ICharacterFactory* m_characterFactory;

					Impl(io::savers::GameDataProcesser& gameDataProcesser,
						characters::ICharacterFactory& characterFactory) : 
						m_gameDataProcesser{ &gameDataProcesser },
						m_characterFactory{ &characterFactory }
					{
					}

					~Impl() = default;
				};

				PlayerConfig::PlayerConfig(io::savers::GameDataProcesser& gameDataProcesser,
					characters::ICharacterFactory& characterFactory) :
					pImpl(std::make_unique<Impl>(gameDataProcesser, characterFactory))
				{
				}

				PlayerConfig::~PlayerConfig() = default;

				characters::Player* PlayerConfig::getCharacter()
				{
					if (pImpl->m_player == nullptr)
					{
						pImpl->m_player = pImpl->m_characterFactory->createDefaultPlayer();
					}

					return pImpl->m_player.get();
				}

				void PlayerConfig::initialize()
				{
					pImpl->m_player = pImpl->m_gameDataProcesser->load();

					if (pImpl->m_player == nullptr)
					{
						pImpl->m_player = pImpl->m_characterFactory->createDefaultPlayer();
					}
				}
			}
		}
	}
}