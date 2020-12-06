#ifndef PLAYER_CONFIG_H
#define PLAYER_CONFIG_H

#include <memory>

#include "IPlayerConfig.h"
#include "../../Characters/ICharacterFactory.h"
#include "../../IO/Savers/GameDataProcesser.h"

class PlayerConfig : public IPlayerConfig
{
private:
	Character* m_playerCharacter;
	
	const std::shared_ptr<GameDataProcesser> m_gameDataProcesser;
	const std::shared_ptr<ICharacterFactory> m_characterFactory;

public:
	PlayerConfig(const std::shared_ptr<GameDataProcesser>& gameDataProcesser, 
		const std::shared_ptr<ICharacterFactory>& characterFactory) :
		m_gameDataProcesser{gameDataProcesser},
		m_characterFactory{characterFactory},
		m_playerCharacter{ nullptr }
	{
	}

	Character* getCharacter() override;
};

#endif // !PLAYER_CONFIG_H

