#pragma once

#include "Command.h"

namespace appimagelauncher {
    namespace commands {
        class AbstractFactory {
        public:
            virtual std::shared_ptr<Command> getCommandByName(const QString&) = 0;

            virtual ~AbstractFactory() = default;
        };
    }
}
