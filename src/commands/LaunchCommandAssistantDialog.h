#pragma once
// system
#include <memory>

// libraries
#include <QtWidgets/QDialog>
#include <QtWidgets/QMessageBox>

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

    void setInstaller(std::shared_ptr<AbstractInstaller> installer) override;

    void setTarget(const QString& newAppImagePath, const QStringList& newArgs) override;

protected slots:

    void on_runButton_released();

    void on_integrateButton_released();

    void on_detailsButton_released();

    void on_confirmOverrideFinished(int result);

protected:
    QString appImagePath;
    QStringList args;

    std::shared_ptr<Ui::LaunchCommandAssistantDialog> ui;
    std::shared_ptr<QMessageBox> overrideConfirmationMessage;
    std::shared_ptr<QMessageBox> errorMessage;
    std::shared_ptr<AbstractLauncher> launcher;
    std::shared_ptr<AbstractInstaller> installer;

    void confirmOverride();

    void showErrorMessage(const QString& title, const QString& message);
};
