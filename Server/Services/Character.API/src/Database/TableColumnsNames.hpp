#pragma once

#include <QtCore/QString>

namespace FightClub {
    namespace Server {
        namespace Character {

            class TableColumnsNames
            {
            public:
                static const QString& ID;
                static const QString& UserID;
                static const QString& AttributeID;
                static const QString& HeadID;
                static const QString& CuirassID;
                static const QString& BootsID;
                static const QString& WeaponID;
                static const QString& Name;
                static const QString& Damage;
                static const QString& ArmorType;
                static const QString& Armor;
                static const QString& Cost;
                static const QString& Value;
                static const QString& Duration;
                static const QString& AbilityTypeID;
                static const QString& Health;
                static const QString& Strength;
                static const QString& Agility;
                static const QString& CharacterType;
                static const QString& Level;

                TableColumnsNames() = delete;
                ~TableColumnsNames() = delete;
            };

        }
    }
}