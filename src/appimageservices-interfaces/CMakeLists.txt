set_source_files_properties(
    org.appimage.Services.Launcher.xml
    org.appimage.Services.Updater.xml
    org.appimage.Services.Updater.Task.xml
    org.appimage.Services.Inspector.xml
    PROPERTIES NO_NAMESPACE ON
)

qt5_add_dbus_interface(AppImageServicesInterfacesSources org.appimage.Services.Launcher.xml LauncherInterface)
qt5_add_dbus_interface(AppImageServicesInterfacesSources org.appimage.Services.Updater.xml UpdaterInterface)
qt5_add_dbus_interface(AppImageServicesInterfacesSources org.appimage.Services.Updater.Task.xml UpdaterTaskInterface)
qt5_add_dbus_interface(AppImageServicesInterfacesSources org.appimage.Services.Inspector.xml InspectorInterface)

add_library(AppImageServicesInterfaces STATIC ${AppImageServicesInterfacesSources})

target_link_libraries(AppImageServicesInterfaces PUBLIC AppImageServicesBase Qt5::Core)
target_include_directories(AppImageServicesInterfaces PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
