#pragma once
// system
#include <memory>

// local
#include "AbstractLauncher.h"
#include "AbstractInstaller.h"
#include "AbstractInspector.h"


class LaunchCommandAbstractAssistant {
public:
    virtual void show() = 0;

    virtual void setTarget(const QString& appImagePath, const QStringList& args) = 0;

    virtual void setLauncher(std::shared_ptr<AbstractLauncher> launcher) = 0;

    virtual void setInstaller(std::shared_ptr<AbstractInstaller> installer) = 0;

    virtual void setInspector(std::shared_ptr<AbstractInspector> inspector) = 0;
};

