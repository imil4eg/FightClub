#ifndef PLAYER_CONFIG_H
#define PLAYER_CONFIG_H

#include <memory>
#include <vector>

#include "IPlayerConfig.h"
#include "Characters/ICharacterFactory.h"
#include "CharacterStuff/Armors/Armor.h"
#include "IO/Savers/GameDataProcesser.h"

class PlayerConfig : public IPlayerConfig
{
private:
	std::unique_ptr<Player> m_player;
	
	GameDataProcesser* m_gameDataProcesser;
	ICharacterFactory* m_characterFactory;

public:
	PlayerConfig(GameDataProcesser* gameDataProcesser, 
				ICharacterFactory* characterFactory) :
		m_gameDataProcesser{gameDataProcesser},
		m_characterFactory{characterFactory}
	{
	}

	void initialize() override;
	Player* getCharacter() override;
};

#endif // !PLAYER_CONFIG_H

