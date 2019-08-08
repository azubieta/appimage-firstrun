#pragma once
// libraries
#include <QObject>

class LaunchCommandAbstractAssistant : public QObject {
Q_OBJECT
public:
    explicit LaunchCommandAbstractAssistant(QObject* parent);

    virtual void show() = 0;

    virtual ~LaunchCommandAbstractAssistant();
};

