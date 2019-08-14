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

    void setInspector(std::shared_ptr<AbstractInspector> inspector) override;

    void setTarget(const QString& newAppImagePath, const QStringList& newArgs) override;

protected slots:

    void on_runButton_released();

    void on_integrateButton_released();

    void on_detailsButton_released();

    void on_confirmOverrideFinished(int result);

    void on_confirmErrorMessageFinished(int result);

protected:
    QString appImagePath;
    QStringList args;

    Ui::LaunchCommandAssistantDialog* ui;
    QMessageBox* overrideConfirmationMessage;
    QMessageBox* errorMessage;
    std::shared_ptr<AbstractLauncher> launcher;
    std::shared_ptr<AbstractInstaller> installer;
    std::shared_ptr<AbstractInspector> inspector;

    void confirmOverride();

    void showErrorMessage(const QString& title, const QString& message);

    void loadAppIcon();

    bool loadAppInfo();
};
