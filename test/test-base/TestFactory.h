#pragma once

// local
#include <AbstractFactory.h>
#include <Command.h>

class TestFactory : public appimagelauncher::commands::AbstractFactory {
public:
    std::shared_ptr<appimagelauncher::commands::Command> getCommandByName(const QString& string) override;
};
