#pragma once

#include <LaunchCommandAbstractAssistant.h>

class LaunchCommandFakeAssistant : public LaunchCommandAbstractAssistant {
public:

    void setTarget(const QString& appImagePath, const QStringList& args) override {

    }

    void setLauncher(std::shared_ptr<AbstractLauncher> launcher) override {

    }

    void show() override {
        showRequested = true;
    }

    bool isShowRequested() const {
        return showRequested;
    }

    void reset() {
        showRequested = false;
    }

private:
    bool showRequested = false;
};
