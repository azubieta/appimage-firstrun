// local
#include <exceptions.h>
#include "LaunchCommandAssistantDialog.h"
#include "ui_LaunchCommandAssistantDialog.h"

LaunchCommandAssistantDialog::LaunchCommandAssistantDialog(QWidget* parent) :
        QDialog(parent), ui(new Ui::LaunchCommandAssistantDialog) {
    ui->setupUi(this);

    // TODO: Implement details section
    ui->widgetDetails->hide();
    ui->detailsButton->hide();
}

LaunchCommandAssistantDialog::~LaunchCommandAssistantDialog() = default;

void LaunchCommandAssistantDialog::show() {
    QDialog::show();
}

void LaunchCommandAssistantDialog::setLauncher(std::shared_ptr<AbstractLauncher> newLauncher) {
    LaunchCommandAssistantDialog::launcher = newLauncher;
}

void LaunchCommandAssistantDialog::on_runButton_released() {
    launcher->launch(appImagePath, args);
}

void LaunchCommandAssistantDialog::setInstaller(std::shared_ptr<AbstractInstaller> installer) {
    LaunchCommandAssistantDialog::installer = installer;
}

void LaunchCommandAssistantDialog::setTarget(const QString& newAppImagePath, const QStringList& newArgs) {
    appImagePath = newAppImagePath;
    args = newArgs;
}

void LaunchCommandAssistantDialog::on_detailsButton_released() {
    if (ui->widgetDetails->isVisible())
        ui->widgetDetails->hide();
    else
        ui->widgetDetails->show();
}

void LaunchCommandAssistantDialog::on_integrateButton_released() {
    try {
        installer->install(appImagePath);
        launcher->launch(appImagePath, args);
    } catch (const appimagelauncher::InstallErrorTargetAlreadyExists& error) {
        confirmOverride();
    }
}

void LaunchCommandAssistantDialog::confirmOverride() {
    QStringList message;
    message << QObject::tr("Do you wish to overwrite the existing AppImage?")
            << QObject::tr("Choosing \"No\" will run the AppImage once, and leave the system in its current state.");

    overrideConfirmationMessage.reset(new QMessageBox(
            QMessageBox::Warning,
            QObject::tr("AppImage with same filename has already been integrated."),
            message.join('\n'),
            QMessageBox::Yes | QMessageBox::No
    ));

    connect(overrideConfirmationMessage.get(), &QMessageBox::finished,
            this, &LaunchCommandAssistantDialog::on_confirmOverrideFinished);

    overrideConfirmationMessage->show();
}

void LaunchCommandAssistantDialog::on_confirmOverrideFinished(int result) {
    if (result == QMessageBox::Yes || result == QDialog::Accepted)
        installer->forcedInstall(appImagePath);

    launcher->launch(appImagePath, args);
}

