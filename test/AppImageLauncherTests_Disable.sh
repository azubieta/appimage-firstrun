#!/usr/bin/env bash
set -ex

ECHO_PATH=$(which echo)
ARGS="-style=windows another string"

export APPIMAGELAUNCHER_DISABLE=1
$1 $ECHO_PATH $ARGS

if [ $? -ne 1 ]; then
  echo "APPIMAGELAUNCHER_DISABLE environment var ignored"
  exit 1
fi
