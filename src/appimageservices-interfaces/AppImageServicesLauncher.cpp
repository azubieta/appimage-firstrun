// system
#include <unistd.h>
#include <vector>

// libraries
#include <QtGlobal>
#include <QtDBus/QtDBus>
#include <QtDBus/QDBusPendingReply>

// local
#include "AppImageServicesLauncher.h"
#include "LauncherInterface.h"

AppImageServicesLauncher::AppImageServicesLauncher() : launcherInterface(
        new OrgAppimageServices1LauncherInterface("org.appimage.Services1.Launcher",
                                                  "/org/appimage/Services1/Launcher",
                                                  QDBusConnection::sessionBus())) {}

void AppImageServicesLauncher::launch(const QString& command, const QStringList& args) {
    std::vector<char*> argsVector;
    QProcess process;
    process.setArguments(args);
    QProcessEnvironment environment;
    environment.insert("APPIMAGELAUNCHER_DISABLE", "true");
    environment.insert("KDE_DEBUG", "false");
    process.setEnvironment(environment.toStringList());

    argsVector.push_back(command.toLocal8Bit().data());

    if (!process.startDetached(command))
        qApp->exit(1);
    else
        qApp->quit();
}

bool AppImageServicesLauncher::registerApp(const QString& appImagePath) {
    auto reply = launcherInterface->registerApp(appImagePath);
    if (reply.isError()) {
        qWarning() << reply.error();
        return false;
    }

    reply.waitForFinished();
    if (reply.isError()) {
        qWarning() << reply.error();
        return false;
    }

    return reply.value();
}

bool AppImageServicesLauncher::unregisterApp(const QString& appImagePath) {
    auto reply = launcherInterface->unregisterApp(appImagePath);
    if (reply.isError()) {
        qWarning() << reply.error();
        return false;
    }

    reply.waitForFinished();
    if (reply.isError()) {
        qWarning() << reply.error();
        return false;
    }

    return reply.value();
}

bool AppImageServicesLauncher::isRegistered(const QString& appImagePath) {
    auto reply = launcherInterface->isRegistered(appImagePath);
    if (reply.isError()) {
        qWarning() << reply.error();
        return false;
    }

    reply.waitForFinished();
    if (reply.isError()) {
        qWarning() << reply.error();
        return false;
    }

    return reply.value();
}
