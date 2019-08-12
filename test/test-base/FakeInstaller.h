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
    explicit FakeInstaller();

    void install(const QString& appImagePath) override;

    void forcedInstall(const QString& appImagePath) override;

    void uninstall(const QString& appImagePath) override;

    QString getTargetPathFor(const QString& appImagePath) override;

    void setTargetPath(const QString& targetPath);

    bool wasInstallCalled() const;

    bool wasUninstallCalled() const;

    bool wasForcedInstallCalled() const;

    void setTargetAlreadyExists(bool targetAlreadyExists);

    void setNoPermissionsOnTarget(bool noPermissionsOnTarget);

private:
    QString targetPath;
    bool installCalled = false;
    bool uninstallCalled = false;
    bool forcedInstallCalled = false;
    bool targetAlreadyExists = false;
    bool noPermissionsOnTarget = false;
};



