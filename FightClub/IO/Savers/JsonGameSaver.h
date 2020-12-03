#ifndef JSON_GAME_SAVER_H
#define JSON_GAME_SAVER_H

#include "GameSaver.h"

class JsonGameSaver : public GameSaver
{
public:
	Character* load() override;
	void save(Character& character) const override;
};


#endif // !JSON_GAME_SAVER_H

