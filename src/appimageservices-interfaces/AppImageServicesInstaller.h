#pragma once
// system

//libraries

//local
#include "AbstractInstaller.h"
#include "AppImageServicesLauncher.h"


class AppImageServicesInstaller : public AbstractInstaller {
public:
    void install(const QString& appImagePath) override;

    void forcedInstall(const QString& appImagePath) override;

    void uninstall(const QString& appImagePath) override;

    QString getTargetPathFor(const QString& appImagePath) override;

    void tryMoveFile(const QString& appImagePath, const QString& targetPath) const;

private:
    AppImageServicesLauncher launcher;

    const QString getAppsDir() const;
};



