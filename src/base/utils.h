#pragma once


namespace appimagelauncher {
    namespace utils {
        bool isRunningHeadless();

        QString removeUriProtocolFromPath(const QString& uri);
    }
}