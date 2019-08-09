#!/usr/bin/env bash
[ "$(APPIMAGELAUNCHER_DISABLE="1" $1 /bin/echo -style=windows)" != "-style=windows" ] && exit 1

