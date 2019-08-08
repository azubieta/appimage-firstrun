// libraries
#include <QObject>
#include <QTest>
#include <test-base/TestFactory.h>

// local
#include "AppImageLauncher.h"

class AppImageLauncherTests : public QObject {
Q_OBJECT
public:
    explicit AppImageLauncherTests(QCoreApplication& qCoreApplication) : QObject(&qCoreApplication),
                                                                         qCoreApplication(qCoreApplication) {}

private:
    QCoreApplication& qCoreApplication;
    std::vector<char*> originalArgs;

public:
    void setOriginalArgs(const std::vector<char*>& args) {
        AppImageLauncherTests::originalArgs = args;
    }

    static std::vector<char*> argsToVector(int argc, char** argv) {
        std::vector<char*> args;
        for (int i = 0; i < argc; i++)
            args.push_back(strdup(argv[i]));

        return args;
    }


private slots:

    void initTestCase() {
    }

    void KeepQtSpecialArgs() {
        appimagelauncher::AppImageLauncher launcher(originalArgs.size(), originalArgs.data());
        auto testFactory = std::make_shared<TestFactory>();
        launcher.setCommandsFactory(testFactory);

        QString command = QCoreApplication::arguments().first();

        launcher.parseArguments(qCoreApplication);
        QVERIFY(true); // check that a condition is satisfied
        QCOMPARE(1, 1); // compare two values
    }

    void mySecondTest() {
//        QVERIFY(myCondition());
//        QVERIFY(1 != 2);
    }

    void cleanupTestCase() {
        qDebug("Called after myFirstTest and mySecondTest.");
    }
};

int main(int argc, char* argv[]) {
    std::vector<char*> args = AppImageLauncherTests::argsToVector(argc, argv);

    QCoreApplication app(argc, argv);
    AppImageLauncherTests launcherTests(app);
    launcherTests.setOriginalArgs(args);

    app.setAttribute(Qt::AA_Use96Dpi, true);
    QTEST_SET_MAIN_SOURCE_PATH
    return QTest::qExec(&launcherTests, argc, argv);
}


#include "AppImageLauncherTests.moc"