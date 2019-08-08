#pragma once

//libraries
#include <QString>
#include <QStringList>

class AbstractLauncher {
public:
    /**
     * Will launch the given <command> with the <args> replacing the current process
     * @param command
     * @param args
     */
    virtual void launch(const QString& command, const QStringList& args) = 0;

    virtual bool registerApp(const QString& appImagePath) = 0;

    virtual bool unregisterApp(const QString& appImagePath) = 0;

    virtual bool isRegistered(const QString& appImagePath) = 0;

};



