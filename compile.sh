#!/bin/bash

set -e

if [[ $(which qmake) ]]; then
  QMAKE_BIN="qmake"
elif [[ $(which qmake-qt4) ]]; then
  QMAKE_BIN="qmake-qt4"
else
  echo "No qmake or qmake-qt4 on the system. Qt4 is required for compilation. Aborting."
  exit
fi

(cd src; ${QMAKE_BIN})
(cd src; make)

