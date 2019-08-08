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

        private:
            QApplication* application;
        };
    }
}
