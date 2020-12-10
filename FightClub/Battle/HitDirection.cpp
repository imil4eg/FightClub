#include "Battle/HitDirection.h"

std::ostream& operator<<(std::ostream& out, HitDirection hd)
{
	switch (hd)
	{
	case HitDirection::head:
		out << "head";
		break;
	case HitDirection::body:
		out << "body";
		break;
	case HitDirection::legs:
		out << "legs";
		break;
	default:
		out << "incorrect direction";
	}

	return out;
}