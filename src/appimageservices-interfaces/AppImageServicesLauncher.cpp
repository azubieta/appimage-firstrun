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

    argsVector.push_back(command.toLocal8Bit().data());

    // copy arguments
    for (const QString& arg: args)
        argsVector.push_back(strdup(arg.toLocal8Bit().data()));

    // prevent loop executions
    qputenv("APPIMAGELAUNCHER_DISABLE", "true");

    // args need to be null terminated
    argsVector.push_back(nullptr);
    execv(command.toLocal8Bit().data(), argsVector.data());

    const auto& error = errno;
    qFatal("execv(%s, [...]) failed: %s", command.toLocal8Bit().data(), strerror(error));
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
