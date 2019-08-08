// libraries
#include <QDebug>
#include <QApplication>
#include <QCommandLineParser>

// local
#include "base/AppImageLauncher.h"
#include "commands/GuiCommandsFactory.h"
#include "exceptions.h"

using namespace appimagelauncher;

int main(int argc, char** argv) {
    AppImageLauncher appImageLauncher(argc, argv);
    QApplication app(argc, argv);
    auto commandsFactory = std::make_shared<commands::GuiCommandsFactory>(&app);
    appImageLauncher.setCommandsFactory(commandsFactory);

    try {
        appImageLauncher.parseArguments(app);
    } catch (const InvalidArguments& error) {
        qCritical("%s", error.what());
        appImageLauncher.showHelp(2);
    }

    try {
        return appImageLauncher.exec();
    } catch (const commands::CommandNotFoundError& e) {
        qCritical("%s", e.what());
        appImageLauncher.showHelp(2);
    } catch (const commands::InvalidArgumentsError& e) {
        qCritical("Invalid arguments: %s", e.what());
        appImageLauncher.showHelp(2);
    } catch (const commands::UsageError& e) {
        qCritical("Usage error:  %s", e.what());
        appImageLauncher.showHelp(2);
    }
}

