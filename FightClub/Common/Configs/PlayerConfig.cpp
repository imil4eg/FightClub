#include "Common/Configs/PlayerConfig.h"

Character* PlayerConfig::getCharacter()
{
	if (m_userDataModel == nullptr)
	{
		m_userDataModel = m_gameDataProcesser->load();
	
		if (m_userDataModel == nullptr)
		{
			m_userDataModel = std::make_unique<fightclub::models::UserDataModel>();
			m_userDataModel->character = m_characterFactory->createDefaultPlayer();
		}
	}
	
	return m_userDataModel->character.get();
}