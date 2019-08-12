//
// Created by alexis on 09/08/19.
//

#pragma once
// system

//libraries

//local
#include "AbstractInstaller.h"


class FakeInstaller : public AbstractInstaller {
public:
    explicit FakeInstaller(QString targetPath = "", bool targetAlreadyExists = false, bool noPermissionsOnTarget = false);

    void install(const QString& appImagePath) override;

    void forcedInstall(const QString& appImagePath) override;

    void uninstall(const QString& appImagePath) override;

    QString getTargetPathFor(const QString& appImagePath) override;

    bool wasInstallCalled() const;

    bool wasUninstallCalled() const;

    bool wasForcedInstallCalled() const;

private:
    QString targetPath;
    bool installCalled = false;
    bool uninstallCalled = false;
    bool forcedInstallCalled = false;
    bool targetAlreadyExists = false;
    bool noPermissionsOnTarget = false;
};



