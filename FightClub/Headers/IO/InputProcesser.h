#ifndef INPUT_PROCESSER_H
#define INPUT_PROCESSER_H

#include "Common/Commands.h"
#include "Battle/HitDirection.h"

class InputProcesser
{
public:
	static HitDirection askHitDirection();
	static Command askCommand();
	static Command askMenuCommand();
};

#endif // !INPUT_PROCESSER_H

