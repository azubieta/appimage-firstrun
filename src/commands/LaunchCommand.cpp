// system
#include <utility>
#include <vector>
#include <unistd.h>

// libraries
#include <QtCore/QDebug>
#include <QtCore/QCoreApplication>

// local
#include "LaunchCommand.h"
#include "utils.h"

namespace appimagelauncher {
    namespace commands {
        void LaunchCommand::exec(QList<QString> arguments) {
            QString binaryUri = arguments.first();
            binaryPath = utils::removeUriProtocolFromPath(binaryUri);
            arguments.pop_front();

            QVariantMap appInfo = inspector->getApplicationInfo(binaryPath);

            if (isAssistantDisabled(appInfo))
                launcher->launch(binaryPath, arguments);
            else {
                assistant->setTarget(binaryPath, arguments);
                assistant->show();
            }
        }

        bool LaunchCommand::isAssistantDisabled(const QVariantMap& appInfo) {
            // Assistant disabled by default
            if (!qgetenv("APPIMAGELAUNCHER_DISABLE").isEmpty())
                return true;

            // AppImages in AppImages are not supposed to be integrated
            if (binaryPath.startsWith("/tmp/.mount_"))
                return true;

            // Desktop entry X-AppImage-Integrate=false
            QVariantList appSettings = appInfo.value("flags").toList();
            if (appSettings.contains("NO_INTEGRATE"))
                return true;

            // Desktop entry Terminal=true
            if (appSettings.contains("TERMINAL_APP"))
                return true;

            // TODO: if the user opted out of the "ask move" thing, we can just run the AppImage

            return false;
        }

        void LaunchCommand::setAssistant(std::shared_ptr<LaunchCommandAbstractAssistant> newAssistant) {
            LaunchCommand::assistant = std::move(newAssistant);
        }

        void LaunchCommand::setLauncher(std::shared_ptr<AbstractLauncher> newLauncher) {
            launcher = std::move(newLauncher);
        }

        void LaunchCommand::setInspector(std::shared_ptr<AbstractInspector> newInspector) {
            inspector = std::move(newInspector);
        }
    }
}