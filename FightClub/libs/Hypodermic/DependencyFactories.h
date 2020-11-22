#pragma once

#include <unordered_map>

#include "DependencyFactory.h"
#include "TypeInfo.h"


namespace Hypodermic
{

    typedef std::unordered_map< TypeInfo, DependencyFactory > DependencyFactories;

} // namespace Hypodermic