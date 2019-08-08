#pragma once
// system

//libraries
#include <QString>
#include <QStringList>

//local
#include <AbstractLauncher.h>

class FakeLauncher : public AbstractLauncher {
public:
    FakeLauncher();

    void launch(const QString& command, const QStringList& args) override;

    bool registerApp(const QString& appImagePath) override;

    bool unregisterApp(const QString& appImagePath) override;

    bool isRegistered(const QString& appImagePath) override;

    bool wasLaunchCalled() const;

    void reset();

    void setRegistered(bool registered);

private:
    bool registered;

    bool launchCalled;
    bool registerAppCalled;
    bool unregisterAppCalled;
    bool isRegisteredCalled;
};



