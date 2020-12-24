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
					struct Impl;
					std::unique_ptr<Impl> pImpl;

				public:
					PlayerConfig(io::savers::GameDataProcesser& gameDataProcesser,
						characters::ICharacterFactory& characterFactory);
					~PlayerConfig();

					void initialize() override;
					characters::Player* getCharacter() override;
				};
			}
		}
	}
}