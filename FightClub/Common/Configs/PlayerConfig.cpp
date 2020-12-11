#include "Common/Configs/PlayerConfig.h"

Player* PlayerConfig::getCharacter()
{
	if (m_player == nullptr)
	{
		m_player = m_characterFactory->createDefaultPlayer();
	}

	return m_player.get();
}

void PlayerConfig::initialize()
{
	m_player = m_gameDataProcesser->load();
}