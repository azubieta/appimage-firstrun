// local headers
#include "exceptions.h"
#include "LaunchCommand.h"
#include "GuiCommandsFactory.h"


namespace appimagelauncher {
    namespace commands {
        GuiCommandsFactory::GuiCommandsFactory(QApplication* application) : application(application) {

        }

        std::shared_ptr<Command> GuiCommandsFactory::getCommandByName(const QString& commandName) {
            if (commandName == "launch")
                return std::make_shared<LaunchCommand>();

            throw CommandNotFoundError(commandName);
        }
    }
}
