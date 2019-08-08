#pragma once

// local
#include "Command.h"
#include "LaunchCommandAbstractUI.h"

namespace appimagelauncher {
    namespace commands {
        class LaunchCommand : public Command {
        public:
            int exec(QList<QString> arguments) override;

            void setUi(LaunchCommandAbstractUI* ui);

        private:
            QString binaryPath;
            LaunchCommandAbstractUI* ui = nullptr;

            int doLaunch(const QString& path, const QList<struct QString>& arguments);

            bool isAssistantDisabled();
        };
    }
}