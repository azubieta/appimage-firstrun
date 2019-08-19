// libraries
#include <QDebug>
#include <QMetaObject>
#include <QApplication>
#include <QCommandLineParser>
#include <QtGui/QFontDatabase>

// local
#include "base/AppImageLauncher.h"
#include "commands/GuiCommandsFactory.h"
#include "AppImageServicesLauncher.h"
#include "AppImageServicesInstaller.h"
#include "AppImageServicesInspector.h"
#include "exceptions.h"

using namespace appimagelauncher;

int main(int argc, char** argv) {
    // Copy arguments before they are modified by the QApplication
    int originalArgc = argc;
    char* originalArgv[argc];
    for (int i = 0; i < argc; ++i)
        originalArgv[i] = strdup(argv[i]);

    QApplication app(argc, argv);
    AppImageLauncher appImageLauncher(&app);

    auto commandsFactory = std::make_shared<commands::GuiCommandsFactory>();
    commandsFactory->setLauncher(std::make_shared<AppImageServicesLauncher>());
    commandsFactory->setInspector(std::make_shared<AppImageServicesInspector>());
    commandsFactory->setInstaller(std::make_shared<AppImageServicesInstaller>());

    appImageLauncher.setCommandsFactory(commandsFactory);

    try {
        appImageLauncher.parseArguments(originalArgc, originalArgv, app);
    } catch (const InvalidArguments& error) {
        qCritical("%s", error.what());
        appImageLauncher.showHelp(2);
    }

    QFontDatabase::addApplicationFont(":/DejaVuSans.ttf");
    QFont appFont("DejaVuSans", 10);
    app.setFont(appFont);


    // Execute method on app start
    QMetaObject::invokeMethod(&appImageLauncher, "exec", Qt::QueuedConnection);
    return QCoreApplication::exec();

}

