#include "PlayerConfig.h"

Character* PlayerConfig::getCharacter()
{
	if (m_playerCharacter == nullptr)
	{
		m_playerCharacter = m_gameDataProcesser->load();

		if (m_playerCharacter == nullptr)
		{
			m_playerCharacter = m_characterFactory->createDefaultPlayer();
		}
	}

	return m_playerCharacter;
}