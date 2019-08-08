//
// Created by alexis on 08/08/19.
//

#pragma once
// system

//libraries
#include <QtGui/QIcon>
#include <QtCore/QString>
#include <QtCore/QJsonObject>

class AbstractInspector {
public:
    virtual QVariantMap getApplicationInfo(const QString& appImagePath) = 0;

    virtual QIcon getApplicationIcon(const QString& appImagePath) = 0;

};



