//
// Created by alexis on 08/08/19.
//

#pragma once
// system

//libraries
#include <QIcon>
#include <QVariantMap>

//local
#include <AbstractInspector.h>


class FakeInspector : public AbstractInspector {
public:
    FakeInspector();

    QVariantMap getApplicationInfo(const QString& appImagePath) override;

    QIcon getApplicationIcon(const QString& appImagePath) override;

    void setApplicationInfo(const QVariantMap& applicationInfo);

    void setApplicationIcon(const QIcon& applicationIcon);

    void reset();

private:
    QVariantMap applicationInfo;
    QIcon applicationIcon;

    bool infoRequested = false;
    bool iconRequested = false;
};



