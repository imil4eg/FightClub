#pragma once

#include "FighterBuilder.hpp"

namespace FightClub::Server::Fight {

    using FighterBuilderPtr = std::shared_ptr<FighterBuilder>;

    class IFighterBuilderFactory
    {
    public:
        virtual ~IFighterBuilderFactory() = default;

        FighterBuilderPtr create(FighterConnectionPtr connection, FighterBuilder::FighterReadyHandler readyHandler) const
        {
            return createImpl(connection, readyHandler);
        }

    private:
        virtual FighterBuilderPtr createImpl(FighterConnectionPtr connection, FighterBuilder::FighterReadyHandler readyHandler) const = 0;
    };

}