#pragma once

#include <LaunchCommandAbstractUI.h>

class LaunchCommandTestUi : public LaunchCommandAbstractUI {
Q_OBJECT
public:
    explicit LaunchCommandTestUi(QObject* parent = nullptr) : LaunchCommandAbstractUI(parent) {}

    void show() override {
        showRequested = true;
    }

    bool isShowRequested() const {
        return showRequested;
    }

private:
    bool showRequested = false;
};

