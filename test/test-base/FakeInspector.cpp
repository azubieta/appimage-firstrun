// libraries
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>

// local
#include "FakeInspector.h"

QVariantMap FakeInspector::getApplicationInfo(const QString& appImagePath) {
    infoRequested = true;
    return applicationInfo;
}

QIcon FakeInspector::getApplicationIcon(const QString& appImagePath) {
    iconRequested = true;
    return applicationIcon;
}

void FakeInspector::setApplicationInfo(const QVariantMap& applicationInfo) {
    FakeInspector::applicationInfo = applicationInfo;
}

void FakeInspector::setApplicationIcon(const QIcon& applicationIcon) {
    FakeInspector::applicationIcon = applicationIcon;
}

void FakeInspector::reset() {
    infoRequested = false;
    iconRequested = false;

    applicationInfo.clear();
    applicationIcon = QIcon();
}

FakeInspector::FakeInspector() {
    applicationInfo = {{"namne", "App"}};
}
