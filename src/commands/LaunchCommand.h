#pragma once

// local
#include "Command.h"
#include "AbstractLauncher.h"
#include "AbstractInspector.h"
#include "LaunchCommandAbstractAssistant.h"

namespace appimagelauncher {
    namespace commands {
        class LaunchCommand : public Command {
        public:
            void exec(QList<QString> arguments) override;

            void setUi(std::shared_ptr<LaunchCommandAbstractAssistant> ui);

            void setLauncher(std::shared_ptr<AbstractLauncher> newLauncher);

            void setInspector(std::shared_ptr<AbstractInspector> newInspector);

        private:
            QString binaryPath;
            std::shared_ptr<LaunchCommandAbstractAssistant> ui = nullptr;
            std::shared_ptr<AbstractLauncher> launcher;
            std::shared_ptr<AbstractInspector> inspector;

            bool isAssistantDisabled();
        };
    }
}