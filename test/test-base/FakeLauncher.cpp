#include "FakeLauncher.h"

void FakeLauncher::launch(const QString& command, const QStringList& args) {
    launchCalled = true;
}

bool FakeLauncher::wasLaunchCalled() const {
    return launchCalled;
}

bool FakeLauncher::registerApp(const QString& appImagePath) {
    registerAppCalled = true;
    return true;
}

bool FakeLauncher::unregisterApp(const QString& appImagePath) {
    unregisterAppCalled = true;
    return true;
}

bool FakeLauncher::isRegistered(const QString& appImagePath) {
    isRegisteredCalled = true;
    return registered;
}

FakeLauncher::FakeLauncher() {
    reset();
}

void FakeLauncher::setRegistered(bool registered) {
    FakeLauncher::registered = registered;
}

void FakeLauncher::reset() {
    registered = false;

    launchCalled = false;
    registerAppCalled = false;
    unregisterAppCalled = false;
    isRegisteredCalled = false;
}
