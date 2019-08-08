#pragma once

// system headers
#include <memory>

// library headers
#include <QList>
#include <QString>

namespace appimagelauncher {
    namespace commands {
        /**
         * Base class for CLI command implementations.
         */
        class Command {
        public:
            // Run the command.
            virtual int exec(QList<QString> arguments) = 0;
        };
    }
}


