#pragma once

#include "ExceptionBase.h"


namespace Hypodermic
{

    HYPODERMIC_DECLARE_EXCEPTION(CircularDependencyException);

} // namespace Hypodermic


#define HYPODERMIC_THROW_CIRCULAR_DEPENDENCY_EXCEPTION(message) HYPODERMIC_THROW(::Hypodermic::CircularDependencyException, message)
