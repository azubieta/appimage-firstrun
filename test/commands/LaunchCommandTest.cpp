// libraries
#include <QObject>
#include <QTest>

// local
#include "LaunchCommand.h"
#include "LaunchCommandTestUi.h"

class LaunchCommandTest : public QObject {
Q_OBJECT

private:
    appimagelauncher::commands::LaunchCommand launchCommand;
    LaunchCommandTestUi testUi;

    bool myCondition() {
        return true;
    }

private slots:

    void initTestCase() {
        launchCommand.setUi(&testUi);
    }

    void disableAssistantUsingEnvTest() {
        qputenv("APPIMAGELAUNCHER_DISABLE", "1");
        QStringList args = {"/fake/bin"};
        QCOMPARE(launchCommand.exec(args), 0);
        QVERIFY(!testUi.isShowRequested()); // check that the assistant wasn't shown
        qputenv("APPIMAGELAUNCHER_DISABLE", "0");
    }

    void mySecondTest() {
        QVERIFY(myCondition());
        QVERIFY(1 != 2);
    }

    void cleanupTestCase() {
        qDebug("Called after myFirstTest and mySecondTest.");
    }
};

QTEST_MAIN(LaunchCommandTest)

#include "LaunchCommandTest.moc"