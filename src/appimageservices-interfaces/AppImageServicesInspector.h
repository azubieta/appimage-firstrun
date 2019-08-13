//
// Created by alexis on 13/08/19.
//

#pragma once
// system
#include <memory>

//libraries

//local

#include "AbstractInspector.h"

class OrgAppimageServices1InspectorInterface;

class AppImageServicesInspector : public AbstractInspector {
public:
    AppImageServicesInspector();

    QVariantMap getApplicationInfo(const QString& appImagePath) override;

    QIcon getApplicationIcon(const QString& appImagePath) override;

private:
    std::shared_ptr<OrgAppimageServices1InspectorInterface> inspectorInterface;
};



