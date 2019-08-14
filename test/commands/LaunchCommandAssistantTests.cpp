// libraries
#include <QTest>
#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>

// local
#include "FakeLauncher.h"
#include "FakeInstaller.h"
#include "FakeInspector.h"
#include "LaunchCommandAssistantDialog.h"
#include "LaunchCommandAbstractAssistant.h"
#include "AppImageLauncherCommands_autogen/include/ui_LaunchCommandAssistantDialog.h"

class LaunchCommandAssistantDialogTestsWrapper : public LaunchCommandAssistantDialog {
Q_OBJECT
public:
    LaunchCommandAssistantDialogTestsWrapper() : LaunchCommandAssistantDialog() {}

    Ui::LaunchCommandAssistantDialog* getUi() {
        return ui;
    };


    QMessageBox* getOverrideConfirmationMessage() {
        return overrideConfirmationMessage;
    };

    QMessageBox* getErrorMessage() {
        return errorMessage;
    };
};

class LaunchCommandAssistantTests : public QObject {
Q_OBJECT
private slots:

    void testShowDetails() {
        auto launcher = std::make_shared<FakeLauncher>();
        LaunchCommandAssistantDialogTestsWrapper dialog;
        dialog.setLauncher(launcher);
        dialog.setInspector(std::make_shared<FakeInspector>());
        // the dialog must be shown for the visibility tests to work
        dialog.show();

        QVERIFY(!dialog.getUi()->widgetDetails->isVisible());
        QTest::mouseClick(dialog.getUi()->detailsButton, Qt::LeftButton);
        QVERIFY(dialog.getUi()->widgetDetails->isVisible());
    }

    void testRun() {
        auto launcher = std::make_shared<FakeLauncher>();
        LaunchCommandAssistantDialogTestsWrapper dialog;
        dialog.setLauncher(launcher);
        dialog.setInspector(std::make_shared<FakeInspector>());
        dialog.show();
        QTest::mouseClick(dialog.getUi()->runButton, Qt::LeftButton);
        QVERIFY(!dialog.isVisible());
        QVERIFY(launcher->wasLaunchCalled());
    }

    void testIntegrate() {
        auto launcher = std::make_shared<FakeLauncher>();
        auto installer = std::make_shared<FakeInstaller>();

        LaunchCommandAssistantDialogTestsWrapper dialog;
        dialog.setLauncher(launcher);
        dialog.setInstaller(installer);
        dialog.setInspector(std::make_shared<FakeInspector>());
        dialog.show();

        QTest::mouseClick(dialog.getUi()->integrateButton, Qt::LeftButton);

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
        dialog.setInspector(std::make_shared<FakeInspector>());
        dialog.show();

        QTest::mouseClick(dialog.getUi()->integrateButton, Qt::LeftButton);
        QVERIFY(dialog.getOverrideConfirmationMessage());
        dialog.getOverrideConfirmationMessage()->reject();

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
        dialog.setInspector(std::make_shared<FakeInspector>());
        dialog.show();

        QTest::mouseClick(dialog.getUi()->integrateButton, Qt::LeftButton);
        QVERIFY(dialog.getOverrideConfirmationMessage());
        dialog.getOverrideConfirmationMessage()->accept();

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
        dialog.setInspector(std::make_shared<FakeInspector>());
        dialog.show();

        QTest::mouseClick(dialog.getUi()->integrateButton, Qt::LeftButton);
        QVERIFY(dialog.getErrorMessage());
        dialog.getErrorMessage()->accept();
        dialog.show();

        QVERIFY(dialog.isVisible());

        QVERIFY(installer->wasInstallCalled());
        QVERIFY(!launcher->wasLaunchCalled());
        QVERIFY(!installer->wasForcedInstallCalled());
    }

    void testLoadIcon() {
        auto launcher = std::make_shared<FakeLauncher>();
        auto installer = std::make_shared<FakeInstaller>();
        auto inspector = std::make_shared<FakeInspector>();

        LaunchCommandAssistantDialogTestsWrapper dialog;
        dialog.setLauncher(launcher);
        dialog.setInstaller(installer);
        dialog.setInspector(inspector);
        dialog.show();


        QVERIFY(dialog.getUi()->labelIcon->pixmap() != nullptr);
    }

    void testLoadEmptyAppInfo() {
        auto launcher = std::make_shared<FakeLauncher>();
        auto installer = std::make_shared<FakeInstaller>();
        auto inspector = std::make_shared<FakeInspector>();
        inspector->setApplicationInfo(QVariantMap());

        LaunchCommandAssistantDialogTestsWrapper dialog;
        dialog.setLauncher(launcher);
        dialog.setInstaller(installer);
        dialog.setInspector(inspector);
        dialog.show();

        QVERIFY(dialog.getErrorMessage());
        QVERIFY(dialog.getErrorMessage()->isVisible());
        dialog.getErrorMessage()->accept();

        QVERIFY(!dialog.isVisible());
    }

    void testLoadAppInfo() {
        auto launcher = std::make_shared<FakeLauncher>();
        auto installer = std::make_shared<FakeInstaller>();
        auto inspector = std::make_shared<FakeInspector>();
        QByteArray defaultAppInfo = "{\n"
                                    "    \"categories\": [\n"
                                    "        \"Utility\"\n"
                                    "    ],\n"
                                    "    \"flags\": [\n"
                                    "    ],\n"
                                    "    \"id\": \"subsurface\",\n"
                                    "    \"license\": \"GPL-2.0-only\",\n"
                                    "    \"links\": {\n"
                                    "        \"homepage\": \"https://subsurface-divelog.org\",\n"
                                    "        \"translate\": \"https://www.transifex.com/subsurface/subsurface/\"\n"
                                    "    },\n"
                                    "    \"locales\": [\n"
                                    "    ],\n"
                                    "    \"mimeTypes\": [\n"
                                    "    ],\n"
                                    "    \"name\": \"Subsurface\",\n"
                                    "    \"summary\": \"Manage and display dive computer data\",\n"
                                    "    \"version\": \"v4.8.3-243-g9009ea767848\"\n"
                                    "}";

        auto doc = QJsonDocument::fromJson(defaultAppInfo);
        inspector->setApplicationInfo(doc.object().toVariantMap());

        LaunchCommandAssistantDialogTestsWrapper dialog;
        dialog.setLauncher(launcher);
        dialog.setInstaller(installer);
        dialog.setInspector(inspector);
        dialog.show();


        QCOMPARE(dialog.getUi()->labelName->text(), "Subsurface");
        QCOMPARE(dialog.getUi()->labelCategories->text(), "Utility");
        QCOMPARE(dialog.getUi()->labelAbstract->text(), "Manage and display dive computer data");
        QCOMPARE(dialog.getUi()->labelLicense->text(), "GPL-2.0-only");
        QCOMPARE(dialog.getUi()->labelLinks->text(),
                 "<a href=\"https://subsurface-divelog.org\">Homepage</a> "
                 "<a href=\"https://www.transifex.com/subsurface/subsurface/\">Translate</a>");
    }
};


QTEST_MAIN(LaunchCommandAssistantTests)

#include "LaunchCommandAssistantTests.moc"