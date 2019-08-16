#!/usr/bin/env bash

pacman -Sy --noconfirm base-devel cmake git qt5-base
useradd build

mkdir build
chmod a+rwx build
cp -v dist/arch/* build
cd build && su build -c "makepkg"
mv appimage-firstrun*.pkg.tar.xz ..
