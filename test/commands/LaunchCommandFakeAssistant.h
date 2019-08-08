#pragma once

#include <LaunchCommandAbstractAssistant.h>

class LaunchCommandFakeAssistant : public LaunchCommandAbstractAssistant {
Q_OBJECT
public:
    explicit LaunchCommandFakeAssistant(QObject* parent = nullptr) : LaunchCommandAbstractAssistant(parent) {}

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

