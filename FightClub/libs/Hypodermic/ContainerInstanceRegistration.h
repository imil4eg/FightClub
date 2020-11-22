#pragma once

#include "Container.h"
#include "ContainerInstanceRegistrationActivator.h"
#include "IRegistration.h"
#include "TypeInfo.h"


namespace Hypodermic
{

    class ContainerInstanceRegistration : public IRegistration
    {
    public:
        explicit ContainerInstanceRegistration(const std::shared_ptr< Container >& instance)
            : m_activator(*this, instance)
            , m_instanceType(Utils::getMetaTypeInfo< Container >())
            , m_typeAliases()
        {
        }
    
        const TypeInfo& instanceType() const override
        {
            return m_instanceType;
        }

        const TypeAliases& typeAliases() const override
        {
            return m_typeAliases;
        }

        DependencyFactory getDependencyFactory(const TypeInfo&) const override
        {
            return nullptr;
        }

        IRegistrationActivator& activator() const override
        {
            return m_activator;
        }

        InstanceLifetimes::InstanceLifetime instanceLifetime() const override
        {
            return InstanceLifetimes::Transient;
        }

        bool isFallback() const override
        {
            return false;
        }

    private:
        mutable ContainerInstanceRegistrationActivator m_activator;
        TypeInfo m_instanceType;
        TypeAliases m_typeAliases;
    };

} // namespace Hypodermic