// libraries
#include <QtCore/QFile>
#include <QtCore/QDebug>

// local
#include "AppImageLauncher.h"
#include "AbstractFactory.h"
#include "exceptions.h"
#include "utils.h"

namespace appimagelauncher {

    AppImageLauncher::AppImageLauncher(QObject* parent) : QObject(parent) {
        initParser();
    }


    void AppImageLauncher::initParser() {
        parser.addPositionalArgument("<command>", "Command to run (see help for more information");
        parser.addPositionalArgument("[...]", "command-specific additional arguments");
        parser.addHelpOption();
        parser.addVersionOption();
    }


    int AppImageLauncher::exec() {
        try {
            commandObj = commandsFactory->getCommandByName(commandName);
            commandObj->exec(commandArguments);
        } catch (const commands::CommandNotFoundError& e) {
            qCritical("%s", e.what());
            showHelp(2);
        } catch (const commands::InvalidArgumentsError& e) {
            qCritical("Invalid arguments: %s", e.what());
            showHelp(2);
        } catch (const commands::UsageError& e) {
            qCritical("Usage error:  %s", e.what());
            showHelp(2);
        }
    }

    void AppImageLauncher::parseArguments(int argc, char** argv, const QCoreApplication& qCoreApplication) {
        parser.process(qCoreApplication);
        QStringList positionalArgumentsInput = parser.positionalArguments();

        if (positionalArgumentsInput.isEmpty())
            throw InvalidArguments(QCoreApplication::tr("No command provided."));

        QString first = positionalArgumentsInput.first();
        first = utils::removeUriProtocolFromPath(first);

        if (QFile::exists(first)) {
            commandName = "launch";

            /* the original arguments are required to run the target app, Qt removes the ones relevant to it which
             * leads to issues while launching other Qt applications */
            for (int i = 1; i < argc; ++i)
                commandArguments << argv[i];

        } else {
            commandName = first;

            /* the original arguments are required to run the target app, Qt removes the ones relevant to it which
             * leads to issues while launching other Qt applications */
            for (int i = 1; i < argc; ++i)
                commandArguments << argv[i];
        }
    }

    void AppImageLauncher::showHelp(int exitCode) {
        parser.showHelp(exitCode);
    }

    void AppImageLauncher::setCommandsFactory(const std::shared_ptr<commands::AbstractFactory>& commandsFactory) {
        AppImageLauncher::commandsFactory = commandsFactory;
    }

    AppImageLauncher::~AppImageLauncher() {

    }

    InvalidArguments::InvalidArguments(const QString& arg) : runtime_error(arg.toStdString()) {}
}
