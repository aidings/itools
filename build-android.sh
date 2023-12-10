#!/bin/bash

rm -r build-android
mkdir build-android && cd build-android

cmake -DCMAKE_TOOLCHAIN_FILE=$ANDROID_NDK/build/cmake/android.toolchain.cmake \
      -DANDROID_ABI="armeabi-v7a" \
      -DANDROID_NATIVE_API_LEVEL=android-24 \
      -DANDROID_TOOLCHAIN=clang \
      -DANDROID_STL=c++_shared \
      -DANDROID_CPP_FEATURES="rtti exceptions" \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX=../install-android \
      ..