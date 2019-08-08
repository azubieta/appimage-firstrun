#pragma once

// system
#include <memory>

// libraries
#include <QCoreApplication>
#include "AbstractFactory.h"

namespace appimagelauncher {
    namespace commands {
        class Command;
    }

    class AppImageLauncher {
    public:
        AppImageLauncher(int argc, char** argv);

        void parseArguments(const QCoreApplication& qCoreApplication);

        int exec();

        void showHelp(int exitCode);

        void setCommandsFactory(const std::shared_ptr<commands::AbstractFactory>& commandsFactory);

    private:
        QString commandName;
        QStringList originalArgs;
        QStringList positionalArguments;

        QCommandLineParser parser;

        std::shared_ptr<commands::Command> commandObj;
        std::shared_ptr<commands::AbstractFactory> commandsFactory;

        void initParser();
    };

    class InvalidArguments : public std::runtime_error {
    public:
        explicit InvalidArguments(const QString& arg);
    };
}