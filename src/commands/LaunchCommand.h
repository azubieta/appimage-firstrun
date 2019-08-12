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

            void setAssistant(std::shared_ptr<LaunchCommandAbstractAssistant> newAssistant);

            void setLauncher(std::shared_ptr<AbstractLauncher> newLauncher);

            void setInspector(std::shared_ptr<AbstractInspector> newInspector);

        private:
            QString binaryPath;
            std::shared_ptr<LaunchCommandAbstractAssistant> assistant = nullptr;
            std::shared_ptr<AbstractLauncher> launcher;
            std::shared_ptr<AbstractInspector> inspector;

            bool isAssistantDisabled();
        };
    }
}