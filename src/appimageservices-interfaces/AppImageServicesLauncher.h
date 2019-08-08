#pragma once
// system

//libraries
#include <QString>
#include <QStringList>

//local
#include "AbstractLauncher.h"


class AppImageServicesLauncher : public AbstractLauncher {
public:
    void launch(const QString& command, const QStringList& args) override;

};



