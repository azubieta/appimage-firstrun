//libraries
#include <QtCore/QDir>
#include <QtCore/QFileInfo>
#include <QtDBus/QDBusConnection>

// local
#include "exceptions.h"
#include "AppImageServicesInstaller.h"

void AppImageServicesInstaller::install(const QString& appImagePath) {
    QString targetPath = getTargetPathFor(appImagePath);
    tryMoveFile(appImagePath, targetPath);
    launcher.registerApp(targetPath);
}

void AppImageServicesInstaller::tryMoveFile(const QString& appImagePath, const QString& targetPath) const {
    if (!QFile::exists(getAppsDir())) {
        if (!QDir::home().mkdir("Applications"))
            throw appimagelauncher::InstallErrorNoPermissionsOnTarget(
                    QObject::tr("Not enough permissions to create %1").arg(getAppsDir()));
    }

    if (targetPath != appImagePath) {
        if (QFile::exists(targetPath))
            throw appimagelauncher::InstallErrorTargetAlreadyExists(appImagePath);

        bool res = QFile::rename(appImagePath, targetPath);
        if (!res)
            throw appimagelauncher::InstallErrorNoPermissionsOnTarget(
                    QObject::tr("Not enough permissions to write %1").arg(targetPath));
    }
}

void AppImageServicesInstaller::forcedInstall(const QString& appImagePath) {
    QString targetPath = getTargetPathFor(appImagePath);
    if (QFile::exists(targetPath)) {
        bool res = QFile::remove(targetPath);
        if (!res)
            throw appimagelauncher::InstallErrorNoPermissionsOnTarget(
                    QObject::tr("Not enough permissions to write %1").arg(appImagePath));
    }

    tryMoveFile(appImagePath, targetPath);
    launcher.registerApp(targetPath);
}

void AppImageServicesInstaller::uninstall(const QString& appImagePath) {

}

QString AppImageServicesInstaller::getTargetPathFor(const QString& pathToAppImage) {
    const QFileInfo appImageInfo(pathToAppImage);
    QString baseName = appImageInfo.completeBaseName();

    auto fileName = baseName;

    // must not use completeSuffix() in combination with completeBasename(), otherwise the final filename is composed
    // incorrectly
    if (!appImageInfo.suffix().isEmpty()) {
        fileName += "." + appImageInfo.suffix();
    }

    return getAppsDir() + fileName;
}

const QString AppImageServicesInstaller::getAppsDir() const { return QDir::homePath() + "/Applications/"; }
