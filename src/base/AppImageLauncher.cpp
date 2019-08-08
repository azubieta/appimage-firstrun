// libraries
#include <QtCore/QFile>
#include <QtCore/QDebug>
#include <QtCore/QProcess>
#include <QtCore/QCommandLineParser>


// local
#include "AppImageLauncher.h"
#include "AbstractFactory.h"
#include "exceptions.h"
#include "utils.h"

namespace appimagelauncher {
    AppImageLauncher::AppImageLauncher(int argc, char** argv) {
        /* copy original arguments could used later to launch a target app
         * arg 0 refers to the executable path therefore could be ignored */
        for (int i = 1; i < argc; ++i)
            originalArgs.push_back(argv[i]);

        initParser();
    }

    void AppImageLauncher::initParser() {
        parser.addPositionalArgument("<command>", "Command to run (see help for more information");
        parser.addPositionalArgument("[...]", "command-specific additional arguments");
        parser.addHelpOption();
        parser.addVersionOption();
    }


    int AppImageLauncher::exec() {
        commandObj = commandsFactory->getCommandByName(commandName);
        return commandObj->exec(positionalArguments);
    }

    void AppImageLauncher::parseArguments(const QCoreApplication& qCoreApplication) {
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
            positionalArguments = originalArgs;
        } else {
            commandName = first;

            // remove command from the positional arguments list
            positionalArgumentsInput.pop_front();
            positionalArguments = positionalArgumentsInput;
        }

    }

    void AppImageLauncher::showHelp(int exitCode) {
        parser.showHelp(exitCode);
    }

    void AppImageLauncher::setCommandsFactory(const std::shared_ptr<commands::AbstractFactory>& commandsFactory) {
        AppImageLauncher::commandsFactory = commandsFactory;
    }


    InvalidArguments::InvalidArguments(const QString& arg) : runtime_error(arg.toStdString()) {}
}
