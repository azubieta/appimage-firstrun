// system
#include <cstdlib>

// libraries
#include <QtCore/QProcess>

// local
#include "utils.h"


namespace appimagelauncher {
    namespace utils {
        bool isRunningHeadless() {
            bool isHeadless = true;

            // not really clean to abuse env vars as "global storage", but hey, it works
            if (getenv("_FORCE_HEADLESS")) {
                return true;
            }

            QProcess proc;
            proc.setProgram("xhost");
            proc.setStandardOutputFile(QProcess::nullDevice());
            proc.setStandardErrorFile(QProcess::nullDevice());

            proc.start();
            proc.waitForFinished();

            switch (proc.exitCode()) {
                case 255: {
                    // program not found, using fallback method
                    isHeadless = (getenv("DISPLAY") == nullptr);
                    break;
                }
                case 0:
                case 1:
                    isHeadless = proc.exitCode() == 1;
                    break;
                default:
                    throw std::runtime_error("Headless detection failed: unexpected exit code from xhost");
            }

            return isHeadless;
        }

        QString removeUriProtocolFromPath(const QString& uri) {
            if (uri.startsWith("file://"))
                return uri.mid(7);
            else
                return uri;
        }
    }
}