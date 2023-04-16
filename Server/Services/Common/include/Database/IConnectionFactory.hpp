#pragma once

#include <memory>
#include <QtCore/QString>
#include <QtSql/QSqlDatabase>

class IConnectionFactory
{
public:
    virtual ~IConnectionFactory() = default;
    virtual QString create() const = 0;
};