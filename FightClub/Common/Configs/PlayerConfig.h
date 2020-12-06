#ifndef PLAYER_CONFIG_H
#define PLAYER_CONFIG_H

#include <memory>

#include "IPlayerConfig.h"
#include "../../IO/Savers/GameDataProcesser.h"

class PlayerConfig : public IPlayerConfig
{
private:
	Character* m_playerCharacter;
	
	const std::shared_ptr<GameDataProcesser> m_gameDataProcesser;

public:
	PlayerConfig(const std::shared_ptr<GameDataProcesser>& gameDataProcesser) :
		m_gameDataProcesser{gameDataProcesser},
		m_playerCharacter{ nullptr }
	{
	}

	Character* getCharacter() override;
};

#endif // !PLAYER_CONFIG_H

