#pragma once
// system
#include <memory>
#include <AbstractLauncher.h>

class LaunchCommandAbstractAssistant {
public:
    virtual void show() = 0;

    virtual void setTarget(const QString& appImagePath, const QStringList& args) = 0;

    virtual void setLauncher(std::shared_ptr<AbstractLauncher> launcher) = 0;
};

