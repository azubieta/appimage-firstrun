// libraries
#include <QObject>
#include <QTest>

// local
#include "FakeLauncher.h"
#include "FakeInstaller.h"
#include "LaunchCommandAssistantDialog.h"
#include "LaunchCommandAbstractAssistant.h"
#include "AppImageLauncherCommands_autogen/include/ui_LaunchCommandAssistantDialog.h"

class LaunchCommandAssistantDialogTestsWrapper : public LaunchCommandAssistantDialog {
Q_OBJECT
public:
    LaunchCommandAssistantDialogTestsWrapper()
            : LaunchCommandAssistantDialog(),
              publicUi(ui),
              publicOverrideConfirmationMessage(overrideConfirmationMessage),
              publicErrorMessage(errorMessage) {
    }

    std::shared_ptr<Ui::LaunchCommandAssistantDialog>& publicUi;
    std::shared_ptr<QMessageBox>& publicOverrideConfirmationMessage;
    std::shared_ptr<QMessageBox>& publicErrorMessage;
};

class LaunchCommandAssistantTests : public QObject {
Q_OBJECT
private slots:

    void testShowDetails() {
        auto launcher = std::make_shared<FakeLauncher>();
        LaunchCommandAssistantDialogTestsWrapper dialog;
        dialog.setLauncher(launcher);
        // the dialog must be shown for the visibility tests to work
        dialog.show();

        QVERIFY(!dialog.publicUi->widgetDetails->isVisible());
        QTest::mouseClick(dialog.publicUi->detailsButton, Qt::LeftButton);
        QVERIFY(dialog.publicUi->widgetDetails->isVisible());
    }

    void testRun() {
        auto launcher = std::make_shared<FakeLauncher>();
        LaunchCommandAssistantDialogTestsWrapper dialog;
        dialog.setLauncher(launcher);
        dialog.show();
        QTest::mouseClick(dialog.publicUi->runButton, Qt::LeftButton);
        QVERIFY(!dialog.isVisible());
        QVERIFY(launcher->wasLaunchCalled());
    }

    void testIntegrate() {
        auto launcher = std::make_shared<FakeLauncher>();
        auto installer = std::make_shared<FakeInstaller>();

        LaunchCommandAssistantDialogTestsWrapper dialog;
        dialog.setLauncher(launcher);
        dialog.setInstaller(installer);
        dialog.show();

        QTest::mouseClick(dialog.publicUi->integrateButton, Qt::LeftButton);

        QVERIFY(!dialog.isVisible());
        QVERIFY(launcher->wasLaunchCalled());
        QVERIFY(installer->wasInstallCalled());
    }

    void testIntegrateExistentAndNotOverride() {
        auto launcher = std::make_shared<FakeLauncher>();
        auto installer = std::make_shared<FakeInstaller>();
        installer->setTargetAlreadyExists(true);

        LaunchCommandAssistantDialogTestsWrapper dialog;
        dialog.setLauncher(launcher);
        dialog.setInstaller(installer);
        dialog.show();

        QTest::mouseClick(dialog.publicUi->integrateButton, Qt::LeftButton);
        QVERIFY(dialog.publicOverrideConfirmationMessage);
        dialog.publicOverrideConfirmationMessage->reject();

        QVERIFY(!dialog.isVisible());
        QVERIFY(launcher->wasLaunchCalled());
        QVERIFY(installer->wasInstallCalled());
        QVERIFY(!installer->wasForcedInstallCalled());
    }

    void testIntegrateExistentAndOverride() {
        auto launcher = std::make_shared<FakeLauncher>();
        auto installer = std::make_shared<FakeInstaller>();
        installer->setTargetAlreadyExists(true);

        LaunchCommandAssistantDialogTestsWrapper dialog;
        dialog.setLauncher(launcher);
        dialog.setInstaller(installer);
        dialog.show();

        QTest::mouseClick(dialog.publicUi->integrateButton, Qt::LeftButton);
        QVERIFY(dialog.publicOverrideConfirmationMessage);
        dialog.publicOverrideConfirmationMessage->accept();

        QVERIFY(!dialog.isVisible());
        QVERIFY(launcher->wasLaunchCalled());
        QVERIFY(installer->wasInstallCalled());
        QVERIFY(installer->wasForcedInstallCalled());
    }

    void testIntegrateTargetReadOnly() {
        auto launcher = std::make_shared<FakeLauncher>();
        auto installer = std::make_shared<FakeInstaller>();
        installer->setNoPermissionsOnTarget(true);

        LaunchCommandAssistantDialogTestsWrapper dialog;
        dialog.setLauncher(launcher);
        dialog.setInstaller(installer);
        dialog.show();

        QTest::mouseClick(dialog.publicUi->integrateButton, Qt::LeftButton);
        QVERIFY(dialog.publicErrorMessage);
        dialog.publicErrorMessage->accept();

        QVERIFY(dialog.isVisible());

        QVERIFY(installer->wasInstallCalled());
        QVERIFY(!launcher->wasLaunchCalled());
        QVERIFY(!installer->wasForcedInstallCalled());
    }
};


QTEST_MAIN(LaunchCommandAssistantTests)

#include "LaunchCommandAssistantTests.moc"