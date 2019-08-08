// system
#include <unistd.h>
#include <vector>

// local
#include "AppImageServicesLauncher.h"

void AppImageServicesLauncher::launch(const QString& command, const QStringList& args) {
    std::vector<char*> argsVector;

    argsVector.push_back(command.toLocal8Bit().data());

    // copy arguments
    for (const QString& arg: args)
        argsVector.push_back(arg.toLocal8Bit().data());

    // args need to be null terminated
    argsVector.push_back(nullptr);
    execv(command.toLocal8Bit().data(), argsVector.data());

    const auto& error = errno;
    qFatal("execv(%s, [...]) failed: %s", command.toLocal8Bit().data(), strerror(error));
}
