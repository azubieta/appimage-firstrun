#pragma once
// system

//libraries
#include <QtCore/QString>


class AbstractInstaller {
public:
    virtual void install(const QString& appImagePath) = 0;

    virtual void forcedInstall(const QString& appImagePath) = 0;

    virtual void uninstall(const QString& appImagePath) = 0;

    virtual QString getTargetPathFor(const QString& appImagePath) = 0;
};



