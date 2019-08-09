// local
#include "TestFactory.h"

std::shared_ptr<appimagelauncher::commands::Command> TestFactory::getCommandByName(const QString& string) {
    if (string == "/bin/echo") {

    }
    return std::shared_ptr<appimagelauncher::commands::Command>();
}

void TestFactory::setLauncher(std::shared_ptr<AbstractLauncher> launcher) {

}

void TestFactory::setInspector(std::shared_ptr<AbstractInspector> inspector) {

}
