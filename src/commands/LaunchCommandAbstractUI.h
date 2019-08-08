#pragma once
// libraries
#include <QObject>

class LaunchCommandAbstractUI : public QObject {
Q_OBJECT
public:
    explicit LaunchCommandAbstractUI(QObject* parent);

    virtual void show() = 0;

    virtual ~LaunchCommandAbstractUI();
};

