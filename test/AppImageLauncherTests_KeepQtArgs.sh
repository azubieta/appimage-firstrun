#!/usr/bin/env bash
set -ex
export APPIMAGELAUNCHER_DISABLE="1"
[ "$($1 /bin/echo -style=windows)" == "-style=windows" ] && exit 0
exit 1
