#pragma once

#include <memory>

#include "InstanceFactory.h"
#include "IRegistration.h"
#include "TypeInfo.h"


namespace Hypodermic
{

    class IRuntimeRegistrationBuilder
    {
    public:
        virtual ~IRuntimeRegistrationBuilder() = default;

        virtual std::shared_ptr< IRegistration > build(const TypeInfo& instanceType, const InstanceFactory& instanceFactory) = 0;
    };

} // namespace Hypodermic