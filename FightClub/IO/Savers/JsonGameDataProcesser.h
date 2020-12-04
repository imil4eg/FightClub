#ifndef JSON_GAME_SAVER_H
#define JSON_GAME_SAVER_H

#include "GameDataProcesser.h"

class JsonGameDataProcesser : public GameDataProcesser
{
public:
	Character* load() override;
	void save(Character& character) const override;
};


#endif // !JSON_GAME_SAVER_H

