// local
#include "LaunchCommandAssistantDialog.h"
#include "ui_LaunchCommandAssistantDialog.h"

LaunchCommandAssistantDialog::LaunchCommandAssistantDialog(QWidget* parent) :
        QDialog(parent), ui(new Ui::LaunchCommandAssistantDialog) {
    ui->setupUi(this);

    // TODO: Implement details section
    ui->widgetDetails->hide();
    ui->detailsButton->hide();
}

LaunchCommandAssistantDialog::~LaunchCommandAssistantDialog() {
    delete ui;
}

void LaunchCommandAssistantDialog::show() {
    QDialog::show();
}

void LaunchCommandAssistantDialog::setLauncher(std::shared_ptr<AbstractLauncher> newLauncher) {
    LaunchCommandAssistantDialog::launcher = newLauncher;
}

void LaunchCommandAssistantDialog::on_runButton_released() {
    launcher->launch(appImagePath, args);
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
