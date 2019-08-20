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
    auto process = new QProcess();
    process->setProgram(command);
    process->setArguments(args);

    QProcessEnvironment environment = QProcessEnvironment::systemEnvironment();
    environment.insert("APPIMAGELAUNCHER_DISABLE", "True");
    environment.insert("KDE_DEBUG", "False");
    environment.insert("DESKTOPINTEGRATION", "False");
    process->setEnvironment(environment.toStringList());

    qDebug() << "Launching: " << command << args;
    qDebug() << "Launch environment: " << environment.toStringList();

    qint64 pid;
    if (process->startDetached(&pid))
        qApp->exit();
    else
        qApp->exit(-1);
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
