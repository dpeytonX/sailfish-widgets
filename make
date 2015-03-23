#!/bin/bash

###############################
# Start the SDK VirtualBox VM #
###############################
echo "Starting SDK"
VBoxHeadless -s "MerSDK" &
sleep 10

#########
# QMake #
#########
export MER_SSH_PORT=2222
export MER_SSH_USERNAME="mersdk"
export MER_SSH_PRIVATE_KEY="$HOME/SailfishOS/vmshare/ssh/private_keys/engine/mersdk"
export MER_SSH_SHARED_HOME="$HOME"
export MER_SSH_SHARED_SRC="$HOME"
export MER_SSH_SHARED_TARGET="$HOME/SailfishOS/mersdk/targets"

ROOT=`pwd`
PROJECTS=("database" "applicationsettings" "filemanagement")

function compile_i486() {
  PROJECT=$1
  TARGET="i486"
  BUILD_PATH="$ROOT/build/$PROJECT/$TARGET"

  export MER_SSH_PROJECT_PATH="$ROOT/$PROJECT"
  export MER_SSH_SDK_TOOLS="$HOME/.config/SailfishBeta2/mer-sdk-tools/MerSDK/SailfishOS-i486"
  export MER_SSH_TARGET_NAME="SailfishOS-i486"
  cd $BUILD_PATH
  "$MER_SSH_SDK_TOOLS/make" clean
  "$MER_SSH_SDK_TOOLS/qmake" "$MER_SSH_PROJECT_PATH/${PROJECT}.pro" "-r" "-spec" "linux-g++-32"
  "$MER_SSH_SDK_TOOLS/make"
}

function compile_armv() {
  PROJECT=$1
  TARGET="armv"
  BUILD_PATH="$ROOT/build/$PROJECT/$TARGET"

  export MER_SSH_PROJECT_PATH="$ROOT/$PROJECT"
  export MER_SSH_SDK_TOOLS="$HOME/.config/SailfishBeta2/mer-sdk-tools/MerSDK/SailfishOS-armv7hl"
  export MER_SSH_TARGET_NAME="SailfishOS-armv7hl"
  cd $BUILD_PATH
  "$MER_SSH_SDK_TOOLS/make" clean
  "$MER_SSH_SDK_TOOLS/qmake" "$MER_SSH_PROJECT_PATH/${PROJECT}.pro" "-r" "-spec" "linux-g++"
  "$MER_SSH_SDK_TOOLS/make"
}

echo "Starting Build"
for proj in ${PROJECTS[@]}; do
  echo "STARTING PROJECT: $proj i486"
  compile_i486 $proj
  echo "STARTING PROJECT: $proj armv"
  compile_armv $proj
done

