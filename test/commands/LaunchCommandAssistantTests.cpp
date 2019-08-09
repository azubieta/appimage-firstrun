// libraries
#include <QObject>
#include <QTest>

// local
#include "FakeLauncher.h"
#include "LaunchCommandAssistantDialog.h"
#include "LaunchCommandAbstractAssistant.h"
#include "AppImageLauncherCommands_autogen/include/ui_LaunchCommandAssistantDialog.h"

class LaunchCommandAssistantDialogTestsWrapper : public LaunchCommandAssistantDialog {
Q_OBJECT
public:
    LaunchCommandAssistantDialogTestsWrapper() : LaunchCommandAssistantDialog() {
        public_ui = ui;
    }

    Ui::LaunchCommandAssistantDialog* public_ui = nullptr;
};

class LaunchCommandAssistantTests : public QObject {
Q_OBJECT
private slots:

    void testDetailsButtonClicked() {
        auto launcher = std::make_shared<FakeLauncher>();
        LaunchCommandAssistantDialogTestsWrapper dialog;
        dialog.setLauncher(launcher);
        // the dialog must be shown for the visibility tests to work
        dialog.show();

        QVERIFY(!dialog.public_ui->widgetDetails->isVisible());
        QTest::mouseClick(dialog.public_ui->detailsButton, Qt::LeftButton);
        QVERIFY(dialog.public_ui->widgetDetails->isVisible());
    }

    void testRunButtonClicked() {
        auto launcher = std::make_shared<FakeLauncher>();
        LaunchCommandAssistantDialogTestsWrapper dialog;
        dialog.setLauncher(launcher);
        QTest::mouseClick(dialog.public_ui->runButton, Qt::LeftButton);
        QVERIFY(launcher->wasLaunchCalled());
    }

};


QTEST_MAIN(LaunchCommandAssistantTests)

#include "LaunchCommandAssistantTests.moc"