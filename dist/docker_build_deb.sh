#!/usr/bin/env bash

apt-get update -y
apt-get install -y git cmake g++ extra-cmake-modules gettext qtbase5-dev libkf5xmlgui-dev libkf5i18n-dev libkf5kio-dev libkf5textwidgets-dev libkf5notifications-dev libkf5filemetadata-dev libqt5dbus5

cmake -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Release .
make -j`nproc`
cpack -G DEB -R 0.1.0-debian-stable