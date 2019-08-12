// libraries
#include <QtCore/QObject>

// local
#include "exceptions.h"
#include "FakeInstaller.h"

FakeInstaller::FakeInstaller() {}

void FakeInstaller::install(const QString& appImagePath) {
    installCalled = true;

    if (targetAlreadyExists)
        throw appimagelauncher::InstallErrorTargetAlreadyExists(appImagePath);

    if (noPermissionsOnTarget)
        throw appimagelauncher::InstallErrorNoPermissionsOnTarget(
                QObject::tr("Not enough permissions to write %1").arg(appImagePath));
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

void FakeInstaller::setTargetAlreadyExists(bool targetAlreadyExists) {
    FakeInstaller::targetAlreadyExists = targetAlreadyExists;
}

void FakeInstaller::setNoPermissionsOnTarget(bool noPermissionsOnTarget) {
    FakeInstaller::noPermissionsOnTarget = noPermissionsOnTarget;
}

void FakeInstaller::setTargetPath(const QString& targetPath) {
    FakeInstaller::targetPath = targetPath;
}
