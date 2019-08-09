#pragma once

// system headers
#include <memory>

// library headers
#include <QString>
#include <QtWidgets/QApplication>

// local headers
#include "Command.h"
#include "AbstractFactory.h"

/**
 * Creates Commands.
 */

namespace appimagelauncher {
    namespace commands {
        class GuiCommandsFactory : public AbstractFactory {
        public:
            explicit GuiCommandsFactory(QApplication* application);

            std::shared_ptr<Command> getCommandByName(const QString&) override;

            void setLauncher(std::shared_ptr<AbstractLauncher> newLauncher) override;

            void setInspector(std::shared_ptr<AbstractInspector> newInspector) override;

        private:
            QApplication* application;
            std::shared_ptr<AbstractLauncher> launcher;
            std::shared_ptr<AbstractInspector> inspector;
        };
    }
}
