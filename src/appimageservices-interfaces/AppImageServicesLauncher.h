#pragma once
// system
#include <memory>

//libraries
#include <QString>
#include <QStringList>

//local
#include "AbstractLauncher.h"

class OrgAppimageServices1LauncherInterface;

class AppImageServicesLauncher : public AbstractLauncher {
public:
    AppImageServicesLauncher();

    void launch(const QString& command, const QStringList& args) override;

    bool registerApp(const QString& appImagePath) override;

    bool unregisterApp(const QString& appImagePath) override;

    bool isRegistered(const QString& appImagePath) override;

private:
    std::shared_ptr<OrgAppimageServices1LauncherInterface> launcherInterface;
};



