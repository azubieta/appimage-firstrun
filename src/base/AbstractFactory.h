#pragma once

// local
#include "Command.h"
#include "AbstractLauncher.h"
#include "AbstractInspector.h"
#include "AbstractInstaller.h"

namespace appimagelauncher {
    namespace commands {
        class AbstractFactory {
        public:
            virtual std::shared_ptr<Command> getCommandByName(const QString&) = 0;

            virtual void setLauncher(std::shared_ptr<AbstractLauncher> launcher) = 0;

            virtual void setInspector(std::shared_ptr<AbstractInspector> inspector) = 0;

            virtual void setInstaller(std::shared_ptr<AbstractInstaller> installer) = 0;

            virtual ~AbstractFactory() = default;
        };
    }
}
