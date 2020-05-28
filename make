#!/bin/bash

SAILFISH_SDK_DIR="$HOME/.config/SailfishSDK"
MER_TOOLS=$SAILFISH_SDK_DIR/libsfdk/build-target-tools/Sailfish\ OS\ Build\ Engine
VERSION=3.3.0.16
#######################
# MER BUILD VARIABLES #
#######################
export MER_SSH_SHARED_SRC=$1

export MER_SSH_PORT=2222
export MER_SSH_HOST=127.0.0.1
export MER_SSH_USERNAME="mersdk"
export MER_SSH_PRIVATE_KEY="$MER_SSH_SHARED_SRC/SailfishOS/vmshare/ssh/private_keys/engine/mersdk"
export MER_SSH_SHARED_HOME="$HOME"
export MER_SSH_SHARED_TARGET="$HOME/SailfishOS/mersdk/targets"

ROOT=`pwd`
BUILD=$ROOT/src/lib
PROJECTS=( $(ls $BUILD) )
ARCH=("i486" "armv")
DEBUG=""

#######################
# FUNCTIONS           #
#######################

function compile_i486() {
  PROJECT=$1
  TARGET="i486"
  BUILD_PATH="$ROOT/build/$PROJECT/$TARGET"

  mkdir -p $BUILD_PATH
  export MER_SSH_PROJECT_PATH="$BUILD/$PROJECT"
  export MER_SSH_TARGET_NAME="SailfishOS-$VERSION-i486"
  export MER_SSH_SDK_TOOLS=$MER_TOOLS/$MER_SSH_TARGET_NAME
  pushd $BUILD_PATH
  "$MER_SSH_SDK_TOOLS/qmake" "$MER_SSH_PROJECT_PATH/${PROJECT}.pro" "-r" "-spec" "linux-g++-32" "$DEBUG" "CMD_LINE+=true"
  "$MER_SSH_SDK_TOOLS/make" "clean"
  "$MER_SSH_SDK_TOOLS/make"
  popd 1> /dev/null
}

function compile_armv() {
  PROJECT=$1
  TARGET="armv"
  BUILD_PATH="$ROOT/build/$PROJECT/$TARGET"

  mkdir -p $BUILD_PATH
  export MER_SSH_PROJECT_PATH="$BUILD/$PROJECT"
  export MER_SSH_TARGET_NAME="SailfishOS-$VERSION-armv7hl"
  export MER_SSH_SDK_TOOLS=$MER_TOOLS/$MER_SSH_TARGET_NAME
  echo "$DEBUG"
  pushd $BUILD_PATH
  
  if [ -n $DEBUG ]; then
    local STRIP=""
  else
    local STRIP='QMAKE_CXXFLAGS += "-fvisibility=hidden -fvisibility-inlines-hidden"'
  fi
  "$MER_SSH_SDK_TOOLS/qmake" "$MER_SSH_PROJECT_PATH/${PROJECT}.pro" "-r" "-spec" "linux-g++" "$DEBUG" "$STRIP" "CMD_LINE+=true"
  "$MER_SSH_SDK_TOOLS/make" "clean"
  if [ -n "$STRIP" ]; then
    "$MER_SSH_SDK_TOOLS/make" "strlib"
  else 
    "$MER_SSH_SDK_TOOLS/make"
  fi
  popd 1> /dev/null
}

function usageFn() {
  echo "Compile the Qt Qml plugins for the VM and phone environment"
  echo "usage: make [-D] [-h] [-p projects] shared_user_src_dir"
  echo "-h: displays this program's usage" 
  echo "-D: adds DEBUG identifier to qmake"
  echo "-a: specifies architecture: ${ARCH[*]}"
  echo "-p: compiles the specified project(s)"
  echo "shared_user_src_dir: The parent directory of Sailfish Qt Creator"
  echo "  the following projects are available: ${PROJECTS[*]}"
}

while getopts :hDp:a: opt "$@"; do
  case $opt in
  h)
    usageFn
    exit 0
    ;;
  p)
    PROJECTS=("$OPTARG")
    ;;
  a)
    ARCH=("$OPTARG")
    ;;
  D)
    DEBUG="CONFIG+=debug"
    ;;
  *)    
    echo "Invalid argument given. Exiting." >&2
    usageFn
    exit 1
    ;;
  esac  
done

if [[ -z "$1" || ! -d "$1" ]]; then
  echo "Shared source directory is either missing or not a directory" && exit 1
fi

###############################
# Start the SDK VirtualBox VM #
###############################
echo "Starting SDK"
VBoxHeadless -s "Sailfish OS Build Engine" &
sleep 10

###########
# Compile #
###########
echo "Starting Build"

for proj in ${PROJECTS[@]}; do
  for arch in ${ARCH[@]}; do
    echo "STARTING PROJECT: $proj $arch"
    if [ $proj = 'core' ]; then
      $("compile_$arch" applicationsettings)
    fi
    $("compile_$arch" $proj)
  done
done

