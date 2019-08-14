//
// Created by alexis on 13/08/19.
//
//libraries
#include <QtDBus/QDBusConnection>
#include <QtCore/QJsonDocument>

// local
#include "AppImageServicesInspector.h"
#include "InspectorInterface.h"

AppImageServicesInspector::AppImageServicesInspector() : inspectorInterface(
        new OrgAppimageServices1InspectorInterface("org.appimage.Services1.Inspector",
                                                   "/org/appimage/Services1/Inspector",
                                                   QDBusConnection::sessionBus())) {}

QVariantMap AppImageServicesInspector::getApplicationInfo(const QString& appImagePath) {
    auto reply = inspectorInterface->getApplicationInfo(appImagePath);
    if (reply.isError()) {
        qWarning() << reply.error();
        return QVariantMap();
    }

    reply.waitForFinished();
    if (reply.isError()) {
        qWarning() << reply.error();
        return QVariantMap();
    }

    QByteArray result = reply.value().toLocal8Bit();
    auto jsonDoc = QJsonDocument::fromJson(result);
    return jsonDoc.object().toVariantMap();
}

QIcon AppImageServicesInspector::getApplicationIcon(const QString& appImagePath) {
    QTemporaryFile temporaryIconFile;
    if (temporaryIconFile.open() && inspectorInterface->isValid()) {
        auto reply = inspectorInterface->extractApplicationIcon(appImagePath, temporaryIconFile.fileName());
        if (reply.isError()) {
            qWarning() << reply.error();
            return QIcon();
        }

        if (reply.value())
            return QIcon(temporaryIconFile.fileName());
    }

    return QIcon();
}
