#ifndef INPUT_PROCESSER_H
#define INPUT_PROCESSER_H

#include "Common/Commands.h"
#include "Battle/HitDirection.h"

namespace fightclub
{
	namespace io
	{
		class InputProcesser
		{
		public:
			static battle::HitDirection askHitDirection();
			static common::Command askCommand();
			static common::Command askMenuCommand();
		};
	}
}

#endif // !INPUT_PROCESSER_H

