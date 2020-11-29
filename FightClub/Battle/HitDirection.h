#ifndef HIT_DIRECTION_H
#define HIT_DIRECTION_H

#include <iostream>

enum class HitDirection
{
	head,
	body,
	legs,
	max_hit_direction
};

std::ostream& operator<<(std::ostream& out, HitDirection hd);


#endif // !HIT_DIRECTION_H
