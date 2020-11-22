#pragma once

#include "ExceptionBase.h"


namespace Hypodermic
{

    HYPODERMIC_DECLARE_EXCEPTION(ActivationException);

} // namespace Hypodermic


#define HYPODERMIC_THROW_ACTIVATION_EXCEPTION(message) HYPODERMIC_THROW(::Hypodermic::ActivationException, message)
