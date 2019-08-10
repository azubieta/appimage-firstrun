// local
#include "exceptions.h"
#include "FakeInstaller.h"

FakeInstaller::FakeInstaller(QString targetPath, bool targetAlreadyExists)
        : targetAlreadyExists(targetAlreadyExists), targetPath(targetPath) {}

void FakeInstaller::install(const QString& appImagePath) {
    installCalled = true;
    if (targetAlreadyExists)
        throw appimagelauncher::InstallErrorTargetAlreadyExists(appImagePath);
}

bool FakeInstaller::wasInstallCalled() const {
    return installCalled;
}

void FakeInstaller::forcedInstall(const QString& appImagePath) {
    forcedInstallCalled = true;
}

void FakeInstaller::uninstall(const QString& appImagePath) {
    uninstallCalled = true;
}

QString FakeInstaller::getTargetPathFor(const QString& appImagePath) {
    return targetPath;
}

bool FakeInstaller::wasUninstallCalled() const {
    return uninstallCalled;
}

bool FakeInstaller::wasForcedInstallCalled() const {
    return forcedInstallCalled;
}
