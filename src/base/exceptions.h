#pragma once

// system headers
#include <stdexcept>

// library headers
#include <QtCore/QString>

namespace appimagelauncher {
    class AppImageLauncherError : public std::runtime_error {
    public:
        explicit AppImageLauncherError(const QString& arg) : runtime_error(arg.toStdString()) {}
    };

    class InstallErrorTargetAlreadyExists : public AppImageLauncherError {
    public:
        explicit InstallErrorTargetAlreadyExists(const QString& arg) : AppImageLauncherError(arg) {}
    };

    class InstallErrorNoPermissionsOnTarget : public AppImageLauncherError {
    public:
        explicit InstallErrorNoPermissionsOnTarget(const QString& arg) : AppImageLauncherError(arg) {}
    };
    
    namespace commands {
        class CliError : public std::runtime_error {
        public:
            explicit CliError(const QString& message) : std::runtime_error(message.toStdString()) {}
        };

        class CommandNotFoundError : public std::runtime_error {
        private:
            QString commandName;

        public:
            explicit CommandNotFoundError(const QString& commandName) : std::runtime_error(
                    "No such command available: " + commandName.toStdString()), commandName(commandName) {}

            QString getCommandName() const {
                return commandName;
            }
        };

        class UsageError : public CliError {
        public:
            using CliError::CliError;
        };

        class InvalidArgumentsError : public UsageError {
        public:
            using UsageError::UsageError;
        };
    }
}
