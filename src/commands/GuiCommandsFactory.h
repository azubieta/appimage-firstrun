#pragma once

// system headers
#include <memory>

// library headers
#include <QString>
#include <QtWidgets/QApplication>

// local headers
#include "Command.h"
#include "AbstractFactory.h"
#include "AbstractInspector.h"
#include "AbstractInstaller.h"

/**
 * Creates Commands.
 */

namespace appimagelauncher {
    namespace commands {
        class GuiCommandsFactory : public AbstractFactory {
        public:

            std::shared_ptr<Command> getCommandByName(const QString&) override;

            void setLauncher(std::shared_ptr<AbstractLauncher> newLauncher) override;

            void setInstaller(std::shared_ptr<AbstractInstaller> newInstaller) override;

            void setInspector(std::shared_ptr<AbstractInspector> newInspector) override;

        private:
            std::shared_ptr<AbstractLauncher> launcher;
            std::shared_ptr<AbstractInspector> inspector;
            std::shared_ptr<AbstractInstaller> installer;
        };
    }
}
