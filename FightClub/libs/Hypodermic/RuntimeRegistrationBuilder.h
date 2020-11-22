#pragma once

#include "ActivationHandlers.h"
#include "DependencyFactories.h"
#include "InstanceFactory.h"
#include "IRuntimeRegistrationBuilder.h"
#include "Registration.h"
#include "TypeAliases.h"


namespace Hypodermic
{

    class RuntimeRegistrationBuilder : public IRuntimeRegistrationBuilder
    {
    public:
        std::shared_ptr< IRegistration > build(const TypeInfo& instanceType, const InstanceFactory& instanceFactory) override
        {
            return std::make_shared< Registration >
            (
                instanceType,
                TypeAliases(),
                instanceFactory,
                DependencyFactories(),
                ActivationHandlers(),
                false /* not a fallback registration */
            );
        }
    };

} // namespace Hypodermic