#!/usr/bin/env bash

apt-get update -y
apt-get install -y file git cmake g++ extra-cmake-modules gettext qtbase5-dev libqt5dbus5

cmake -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Release .
make -j`nproc`
cpack -G DEB -R 0.1.0-$PKG_VERSION_POSTFIX