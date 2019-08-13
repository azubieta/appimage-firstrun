// libraries
#include <QDebug>
#include <QMetaObject>
#include <QApplication>
#include <QCommandLineParser>

// local
#include "base/AppImageLauncher.h"
#include "commands/GuiCommandsFactory.h"
#include "AppImageServicesLauncher.h"
#include "AppImageServicesInspector.h"
#include "exceptions.h"

using namespace appimagelauncher;

int main(int argc, char** argv) {
    AppImageLauncher appImageLauncher(argc, argv);
    QApplication app(argc, argv);
    auto commandsFactory = std::make_shared<commands::GuiCommandsFactory>(&app);
    commandsFactory->setLauncher(std::make_shared<AppImageServicesLauncher>());
    commandsFactory->setInspector(std::make_shared<AppImageServicesInspector>());
    // TODO: initialize commands factory

    appImageLauncher.setCommandsFactory(commandsFactory);

    try {
        appImageLauncher.parseArguments(app);
    } catch (const InvalidArguments& error) {
        qCritical("%s", error.what());
        appImageLauncher.showHelp(2);
    }

    // Execute method on app start
    QMetaObject::invokeMethod(&appImageLauncher, &AppImageLauncher::exec, Qt::QueuedConnection);
    return QCoreApplication::exec();

}

