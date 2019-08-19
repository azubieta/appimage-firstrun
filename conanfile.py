#!/usr/bin/env python
# -*- coding: utf-8 -*-

from conans import ConanFile, CMake, tools
from shutil import copyfile
import os
import struct


class AppImageServices(ConanFile):
    name = "appimage-appsdir"
    version = "0.1"
    settings = "os", "compiler", "build_type", "arch"

    requires = (("zlib/1.2.11@conan/stable"),
                ("libpng/1.6.36@bincrafters/stable"),
                ("qt/5.12.3@appimage-conan-community/stable"),)

    options = {"enable_tests": [True, False]}
    default_options = {
        "qt:shared": True,
        "zlib:shared": True,
        "enable_tests": False
    }

    build_requires = ("patchelf_installer/0.9@appimage-conan-community/stable",
                      "gtest/1.8.1@bincrafters/stable",
                      "cmake_installer/3.14.3@conan/stable",
                      "linuxdeploy/continuous@appimage-conan-community/stable",
                      "linuxdeploy-plugin-qt/continuous@appimage-conan-community/stable",
                      "linuxdeploy-plugin-appimage/continuous@appimage-conan-community/stable")

    generators = "cmake", "cmake_paths"

    def import_pkg_config_files(self, pkg, pkgconfig_path):
        for root, dirs, files in os.walk(self.deps_cpp_info[pkg].rootpath):
            for file in files:
                if file.endswith("pc"):
                    source_path = os.path.join(root, file)
                    target_path = os.path.join(pkgconfig_path, file)
                    print("Importing pkg_config file: %s" % target_path)
                    copyfile(source_path, target_path)
                    tools.replace_prefix_in_pc_file(target_path, self.deps_cpp_info[pkg].rootpath)

    def build(self):
        appDirPath = self.build_folder + "/AppDir"

        for lib in self.deps_cpp_info.deps:
            self.import_pkg_config_files(lib, self.build_folder)

        with tools.environment_append({'PKG_CONFIG_PATH': self.build_folder}):
            cmake = CMake(self)
            cmake.definitions["CMAKE_PROJECT_appimage-appsdir_INCLUDE"] = self.build_folder + "/conan_paths.cmake"
            # Correct conan default installation paths
            cmake.definitions["CMAKE_INSTALL_PREFIX"] = appDirPath
            cmake.definitions["CMAKE_INSTALL_BINDIR"] = "usr/bin"
            cmake.definitions["CMAKE_INSTALL_LIBDIR"] = "usr/lib"
            cmake.definitions["CMAKE_INSTALL_INCLUDEDIR"] = "usr/include"
            cmake.definitions["CMAKE_INSTALL_DATAROOTDIR"] = "usr/share"
            cmake.definitions["CMAKE_INSTALL_SYSCONFDIR"] = "etc"
            cmake.definitions["ENABLE_TESTING"] = self.options["enable_tests"]

            cmake.configure()
            cmake.build()
            cmake.install()

            self.run("linuxdeploy --appdir=%s --plugin qt --output appimage" % appDirPath, run_environment=True)

            print('Removing AppImage magic bites to avoid being intercepted by the launchers')
            appImagePath = self.findCreatedAppImage()
            self.removeAppImageMagicBits(appImagePath)

    def findCreatedAppImage(self):
        appImagePath = ""
        for root, dirs, files in os.walk("."):
            for filename in files:
                if 'appimage-firstrun' in filename and filename.endswith("AppImage"):
                    appImagePath = filename

        return appImagePath

    def removeAppImageMagicBits(self, appImagePath):
        fout = open(appImagePath, 'r+b')
        fout.seek(8)
        fout.write(struct.pack('<BBB', 0, 0, 0))
        fout.close()
