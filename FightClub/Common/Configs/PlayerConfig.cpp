#include "PlayerConfig.h"

Character* PlayerConfig::getCharacter()
{
	if (m_playerCharacter == nullptr)
		m_playerCharacter = m_gameDataProcesser->load();

	return m_playerCharacter;
}