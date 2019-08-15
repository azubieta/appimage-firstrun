// libraries
#include <QObject>
#include <QTest>

// local
#include "LaunchCommand.h"
#include "LaunchCommandFakeAssistant.h"
#include "FakeLauncher.h"
#include "FakeInspector.h"

class LaunchCommandTest : public QObject {
Q_OBJECT

private:
    appimagelauncher::commands::LaunchCommand launchCommand;
    std::shared_ptr<LaunchCommandFakeAssistant> assistant;
    std::shared_ptr<FakeLauncher> launcher;
    std::shared_ptr<FakeInspector> inspector;

private slots:

    void initTestCase() {
        assistant = std::make_shared<LaunchCommandFakeAssistant>();
        launcher = std::make_shared<FakeLauncher>();
        inspector = std::make_shared<FakeInspector>();

        launchCommand.setAssistant(assistant);
        launchCommand.setLauncher(launcher);
        launchCommand.setInspector(inspector);
    }

    void testShowAssistant() {
        launchCommand.exec({"/fake/bin"});

        QVERIFY(assistant->isShowRequested()); // check that the assistant wasn't shown
        QVERIFY(!launcher->wasLaunchCalled()); // check that the assistant wasn't shown
    }

    void disableAssistantUsingEnvTest() {
        qputenv("APPIMAGELAUNCHER_DISABLE", "1");

        launchCommand.exec({"/fake/bin"});

        QVERIFY(!assistant->isShowRequested()); // check that the assistant wasn't shown
        QVERIFY(!launcher->wasLaunchCalled()); // check that the assistant wasn't shown
        qputenv("APPIMAGELAUNCHER_DISABLE", "0");
    }

    void disableAssistantOnAppImageInsideOtherAppImages() {
        QStringList args = {"/tmp/.mount_23123/usr/another.AppImage"};
        launchCommand.exec(args);

        QVERIFY(!assistant->isShowRequested()); // check that the assistant wasn't shown
        QVERIFY(!launcher->wasLaunchCalled()); // check that the assistant wasn't shown
    }

    void disableAssistantOnTerminalApp() {
        QVariantMap fakeAppInfo = {{"flags", {"TERMINAL_APP"}}};
        inspector->setApplicationInfo(fakeAppInfo);

        launchCommand.exec({"/fake/bin"});

        QVERIFY(!assistant->isShowRequested()); // check that the assistant wasn't shown
        QVERIFY(!launcher->wasLaunchCalled()); // check that the assistant wasn't shown
    }

    void disableAssistantOnIntegrationExplicitlyDisabled() {
        QVariantMap fakeAppInfo = {{"flags", {"NO_INTEGRATE"}}};
        inspector->setApplicationInfo(fakeAppInfo);

        launchCommand.exec({"/fake/bin"});

        QVERIFY(!assistant->isShowRequested()); // check that the assistant wasn't shown
        QVERIFY(!launcher->wasLaunchCalled()); // check that the assistant wasn't shown
    }

    void disableAssistantOnRegisteredApps() {
        launcher->setRegistered(true);
        launchCommand.exec({"/fake/bin"});

        QVERIFY(!assistant->isShowRequested()); // check that the assistant wasn't shown
        QVERIFY(!launcher->wasLaunchCalled()); // check that the assistant wasn't shown
    }

    void cleanup() {
        assistant->reset();
        launcher->reset();
        inspector->reset();
    }
};

QTEST_MAIN(LaunchCommandTest)

#include "LaunchCommandTest.moc"