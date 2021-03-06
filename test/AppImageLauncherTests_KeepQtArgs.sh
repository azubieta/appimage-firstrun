#!/usr/bin/env bash
set -ex

ECHO_PATH=$(which echo)
ARGS="-style=windows another string"
export APPIMAGELAUNCHER_DISABLE=1

if [ "$($1 $ECHO_PATH $APPIMAGELAUNCHER_ARGS)" != "$APPIMAGELAUNCHER_ARGS" ]; then
  echo "Qt commands were removed!"
  exit 1
fi
