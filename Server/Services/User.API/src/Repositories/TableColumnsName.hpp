#pragma once

#include <qt5/QtCore/QString>

namespace FightClub {
    namespace Server {
        namespace User {

            class TableColumnsName
            {
            public:
                static const QString ID;
                static const QString UserName;
                static const QString Password;

                TableColumnsName() = delete;
                ~TableColumnsName() = delete;
            };

        }
    }
}