#pragma once

#include <boost/noncopyable.hpp>

#include "BoostCommon.hpp"
#include "IConfigReader.hpp"
#include "IFighterBuilderFactory.hpp"

namespace FightClub::Server::Fight {

    class FighterBuilderFactory : public IFighterBuilderFactory, private boost::noncopyable
    {
    public:
        FighterBuilderFactory(Common::IConfigReader& configReader, net::io_service& ios) :
            m_configReader(&configReader),
            m_ios(ios)
        {
        }

    private:
        FighterBuilderPtr createImpl(FighterConnectionPtr connection, FighterBuilder::FighterReadyHandler readyHandler) const override
        {
            return std::make_shared<FighterBuilder>(connection, readyHandler, *m_configReader, m_ios);
        }

    private:
        Common::IConfigReader* m_configReader;
        net::io_service& m_ios;
    };

}