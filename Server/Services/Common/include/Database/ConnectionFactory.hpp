#pragma once

#include <string>
#include <memory>

#include <QtCore/QtCore>

#include "IConnectionFactory.hpp"

class ConnectionFactory : public IConnectionFactory
{
public:
    ConnectionFactory(const std::string& connectionString);
    ~ConnectionFactory();

    QString create() const override;

private:
    struct Impl;
    std::unique_ptr<Impl> pImpl; 
};