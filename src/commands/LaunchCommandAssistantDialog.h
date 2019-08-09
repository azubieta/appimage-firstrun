#pragma once
// system
#include <memory>

// libraries
#include <QDialog>

// local
#include "LaunchCommandAbstractAssistant.h"

namespace Ui {
    class LaunchCommandAssistantDialog;
}

class LaunchCommandAssistantDialog : public QDialog, public LaunchCommandAbstractAssistant {
Q_OBJECT

public:
    explicit LaunchCommandAssistantDialog(QWidget* parent = nullptr);

    ~LaunchCommandAssistantDialog() override;

    void show() override;

    void setLauncher(std::shared_ptr<AbstractLauncher> newLauncher) override;

    void setTarget(const QString& newAppImagePath, const QStringList& newArgs) override;

protected slots:

    void on_runButton_released();

    void on_detailsButton_released();

protected:
    QString appImagePath;
    QStringList args;

    Ui::LaunchCommandAssistantDialog* ui;
    std::shared_ptr<AbstractLauncher> launcher;
};
