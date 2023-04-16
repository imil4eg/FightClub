#include "ConnectionFactory.hpp"

#include <QtCore/QUuid>

struct ConnectionFactory::Impl
{
    Impl(const std::string& aConnectionString) : 
        connectionString{aConnectionString}
    {
    }

    std::string connectionString;
};

ConnectionFactory::ConnectionFactory(const std::string& connectionString) :
        pImpl{std::make_unique<Impl>(connectionString)}
{    
}

ConnectionFactory::~ConnectionFactory()
{
}

QString ConnectionFactory::create() const
{
    QString connectionName{QUuid::createUuid().toString()};

    QSqlDatabase connection{QSqlDatabase::addDatabase("QODBC", connectionName)};
    connection.setDatabaseName(pImpl->connectionString.c_str());
    
    return connectionName;
}