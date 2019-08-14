// local headers
#include "exceptions.h"
#include "LaunchCommand.h"
#include "GuiCommandsFactory.h"
#include "LaunchCommandAssistantDialog.h"


namespace appimagelauncher {
    namespace commands {

        std::shared_ptr<Command> GuiCommandsFactory::getCommandByName(const QString& commandName) {
            if (commandName == "launch") {
                auto launchCommand = std::make_shared<LaunchCommand>();
                launchCommand->setLauncher(launcher);
                launchCommand->setInspector(inspector);

                auto assistantDialog = std::make_shared<LaunchCommandAssistantDialog>();
                assistantDialog->setLauncher(launcher);
                assistantDialog->setInstaller(installer);
                assistantDialog->setInspector(inspector);
                assistantDialog->setInstaller(installer);

                launchCommand->setAssistant(assistantDialog);
                return launchCommand;
            }


            throw CommandNotFoundError(commandName);
        }

        void GuiCommandsFactory::setLauncher(std::shared_ptr<AbstractLauncher> newLauncher) {
            launcher = newLauncher;
        }

        void GuiCommandsFactory::setInspector(std::shared_ptr<AbstractInspector> newInspector) {
            inspector = newInspector;

        }

        void GuiCommandsFactory::setInstaller(std::shared_ptr<AbstractInstaller> newInstaller) {
            installer = newInstaller;
        }
    }
}
