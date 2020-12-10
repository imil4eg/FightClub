#ifndef SAVE_FILE_MODEL_H
#define SAVE_FILE_MODEL_H

#include <vector>

#include "../Characters/Character.h"
#include "../CharacterStuff/Armors/Armor.h"

class SaveFileModel
{
private:
	const Character* m_character;
	const std::vector<Armor*> m_armor;

public:
	SaveFileModel(Character* character, std::vector<Armor*> armor) : 
		m_character{ character },
		m_armor{ armor }
	{
	}
};

#endif // !SAVE_FILE_MODEL_H

