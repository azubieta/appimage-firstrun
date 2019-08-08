// system
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
        int LaunchCommand::exec(QList<QString> arguments) {
            QString binaryUri = arguments.first();
            binaryPath = utils::removeUriProtocolFromPath(binaryUri);
            arguments.pop_front();

            if (isAssistantDisabled())
                return doLaunch(binaryPath, arguments);
            else {
                if (ui != nullptr)
                    throw std::runtime_error("Trying to show LaunchCommandAssistant while it is not set");

                ui->show();
                return 0;
            }
        }

        bool LaunchCommand::isAssistantDisabled() {
            // TODO: No UI set
            if (ui == nullptr)
                return true;

            // Assistant disabled by default
            if (!qgetenv("APPIMAGELAUNCHER_DISABLE").isEmpty())
                return true;

            // AppImages in AppImages are not supposed to be integrated
            if (binaryPath.startsWith("/tmp/.mount_"))
                return true;

            // TODO: Desktop entry X-AppImage-Integrate=false

            // TODO: Desktop entry Terminal=true

            // TODO: if the user opted out of the "ask move" thing, we can just run the AppImage

            return false;
        }

        int LaunchCommand::doLaunch(const QString& path, const QList<struct QString>& arguments) {
            std::vector<char*> args;

            args.push_back(path.toLocal8Bit().data());

            // copy arguments
            for (const QString& arg: arguments)
                args.push_back(arg.toLocal8Bit().data());

            // args need to be null terminated
            args.push_back(nullptr);
            execv(path.toLocal8Bit().data(), args.data());

            const auto& error = errno;
            qFatal("execv(%s, [...]) failed: %s", path.toLocal8Bit().data(), strerror(error));
        }

        void LaunchCommand::setUi(LaunchCommandAbstractUI* ui) {
            LaunchCommand::ui = ui;
        }
    }
}