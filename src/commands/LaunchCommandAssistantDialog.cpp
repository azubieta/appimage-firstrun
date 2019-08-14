// libraries
#include <QDebug>

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
    bool appInfoLoaded = loadAppInfo();
    loadAppIcon();

    if (appInfoLoaded)
        QDialog::show();
}

bool LaunchCommandAssistantDialog::loadAppInfo() {
    QVariantMap appInfo = inspector->getApplicationInfo(appImagePath);
    if (appInfo.isEmpty()) {
        showErrorMessage(tr("Unable to open AppImage"),
                         tr("%1, is either broken or not an AppImage").arg(appImagePath));
        return false;
    }

    QString error = appInfo.value("error", "").toString();
    if (!error.isEmpty()) {
        showErrorMessage(tr("Unable to open AppImage"), error);
        return false;
    }

    QString appName = appInfo.value("name").toString();
    ui->labelName->setText(appName);
    setWindowTitle(appName + tr(" Integration Assistant"));

    ui->labelCategories->setText(appInfo.value("categories").toStringList().join(", "));
    ui->labelAbstract->setText(appInfo.value("summary").toString());
    ui->labelLicense->setText(appInfo.value("license").toString());
    auto links = appInfo.value("links").toMap();
    QStringList linksString;
    QString linkStringTemplate = "<a href=\"%2\">%1</a>";
    QMapIterator<QString, QVariant> itr(links);
    for (QMap<QString, QVariant>::iterator itr = links.begin(); itr != links.end(); ++itr) {
        // Make uppercase the first letter of the category name
        QString linkName = itr.key().left(1).toUpper() + itr.key().mid(1);
        linksString << linkStringTemplate.arg(linkName).arg(itr.value().toString());
    }

    ui->labelLinks->setText(linksString.join(" "));
    return true;
}

void LaunchCommandAssistantDialog::loadAppIcon() {
    auto appIcon = inspector->getApplicationIcon(appImagePath);
    auto appIconPixmap = appIcon.pixmap(64, 64);
    if (appIconPixmap.isNull()) {
        ui->labelIcon->hide();
    } else {
        ui->labelIcon->setPixmap(appIconPixmap);
        setWindowIcon(appIcon);
    }
}

void LaunchCommandAssistantDialog::setLauncher(std::shared_ptr<AbstractLauncher> newLauncher) {
    LaunchCommandAssistantDialog::launcher = newLauncher;
}

void LaunchCommandAssistantDialog::on_runButton_released() {
    launcher->launch(appImagePath, args);
    hide();
}

void LaunchCommandAssistantDialog::setInstaller(std::shared_ptr<AbstractInstaller> installer) {
    LaunchCommandAssistantDialog::installer = installer;
}

void LaunchCommandAssistantDialog::setInspector(std::shared_ptr<AbstractInspector> inspector) {
    LaunchCommandAssistantDialog::inspector = inspector;
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
        appImagePath = installer->getTargetPathFor(appImagePath);

        launcher->launch(appImagePath, args);
        hide();
    } catch (const appimagelauncher::InstallErrorTargetAlreadyExists& error) {
        confirmOverride();
    } catch (const appimagelauncher::InstallErrorNoPermissionsOnTarget& error) {
        showErrorMessage(tr("Unable to deploy the AppImage file"), error.what());
    }
}

void LaunchCommandAssistantDialog::confirmOverride() {
    QStringList message;
    message << QObject::tr("Do you wish to overwrite the existing AppImage?")
            << QObject::tr("Choosing \"No\" will run the AppImage once, and leave the system in its current state.");

    overrideConfirmationMessage = new QMessageBox(
            QMessageBox::Warning,
            QObject::tr("AppImage with same filename has already been integrated."),
            message.join('\n'),
            QMessageBox::Yes | QMessageBox::No, this
    );

    connect(overrideConfirmationMessage, &QMessageBox::finished,
            this, &LaunchCommandAssistantDialog::on_confirmOverrideFinished);

    overrideConfirmationMessage->show();
}

void LaunchCommandAssistantDialog::on_confirmOverrideFinished(int result) {
    if (result == QMessageBox::Yes || result == QDialog::Accepted) {
        try {
            installer->forcedInstall(appImagePath);
            appImagePath = installer->getTargetPathFor(appImagePath);
        } catch (const appimagelauncher::InstallErrorNoPermissionsOnTarget& error) {
            showErrorMessage(tr("Unable to deploy the AppImage file"), error.what());
        }
    }

    launcher->launch(appImagePath, args);
    hide();
}

void LaunchCommandAssistantDialog::showErrorMessage(const QString& title, const QString& message) {
    errorMessage = new QMessageBox(QMessageBox::Warning, title, message, QMessageBox::Ok, this);
    connect(errorMessage, &QMessageBox::finished,
            this, &LaunchCommandAssistantDialog::on_confirmErrorMessageFinished);
    errorMessage->show();
}

void LaunchCommandAssistantDialog::on_confirmErrorMessageFinished(int result) {

}

