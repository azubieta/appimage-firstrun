#pragma once

// system
#include <memory>

// libraries
#include <QObject>
#include <QtCore/QCommandLineParser>
#include <QCoreApplication>

// local
#include "AbstractFactory.h"

namespace appimagelauncher {
    namespace commands {
        class Command;
    }

    class AppImageLauncher : public QObject {
    Q_OBJECT

    public:
        AppImageLauncher(QObject* parent = nullptr);

        void parseArguments(int argc, char** argv, const QCoreApplication& qCoreApplication);

        void showHelp(int exitCode);

        void setCommandsFactory(const std::shared_ptr<commands::AbstractFactory>& commandsFactory);

        ~AppImageLauncher();

    public slots:

        int exec();

    private:
        QString commandName;
        QStringList commandArguments;

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