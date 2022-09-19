FROM ubuntu:20.04

ARG NDK_TOOLCHAIN_PREFIX=arm-linux-androideabi
ARG NDK_VERSION=r20b
ARG NDK_URL="https://dl.google.com/android/repository/android-ndk-${NDK_VERSION}-linux-x86_64.zip"
ARG NDK_SHA256="8381c440fe61fcbb01e209211ac01b519cd6adf51ab1c2281d5daad6ca4c8c8c"
ARG SDK_INSTALL_DIR=/opt/android-sdk
ARG SDK_BUILD_TOOLS=28.0.3
ARG SDK_PACKAGES="tools platform-tools"
ARG SDK_PLATFORM=android-28

ENV DEBIAN_FRONTEND=noninteractive \
    ANDROID_HOME=${SDK_INSTALL_DIR} \
    ANDROID_SDK_ROOT=${SDK_INSTALL_DIR} \
    ANDROID_SDK_BUILD_TOOLS=${SDK_BUILD_TOOLS} \
    ANDROID_NDK_ROOT=/opt/android-ndk \
    ANDROID_NDK_TOOLS_PREFIX=${NDK_TOOLCHAIN_PREFIX} \
    ANDROID_NDK_TOOLCHAIN_PREFIX=${NDK_TOOLCHAIN_PREFIX} \
    ANDROID_NDK_TOOLCHAIN_VERSION=4.9 \
    ANDROID_NDK_TOOLCHAIN_ABI=armeabi-v7a \
    ANDROID_NDK_HOST=linux-x86_64 \
    ANDROID_NDK_PLATFORM=${SDK_PLATFORM} 

RUN apt-get update && apt-get install -y gdb build-essential python3 curl clang-tidy git libqt5qml5 ccache openjdk-8-jdk-headless \
    openjdk-8-jre-headless ninja-build ant mesa-common-dev libglu1-mesa-dev libfontconfig1-dev libfreetype6-dev libx11-dev \
                           libxext-dev libxfixes-dev libxi-dev libxrender-dev libxcb1-dev libx11-xcb-dev \
                           libxcb-glx0-dev libxkbcommon-x11-dev libssl-dev libxkbcommon-dev libxkbcommon-x11-dev \
                           libxcb-xinerama0-dev libxcb-render-util0-dev  libxcb-icccm4-dev libxcb-util-dev libxcb-shm0-dev \
                           libxcb-image0-dev libxcb-keysyms1-dev \
                           bluez libbluetooth-dev python3-pip curl sudo bash-completion vim
RUN pip3 install conan cmake-format

COPY --from=bernedom/qt_x86_64:5.15.2 /usr/local/Qt /usr/local/Qt/gcc_64
COPY --from=bernedom/qt_android:5.15.2 /usr/local/Qt /usr/local/Qt/android
COPY --from=bernedom/qt_android:5.15.2 /opt/android-sdk /opt/android-sdk
COPY --from=bernedom/qt_android:5.15.2 /opt/android-ndk /opt/android-ndk

WORKDIR /tmp

RUN curl -OL https://github.com/Kitware/CMake/releases/download/v3.22.2/cmake-3.22.2.tar.gz && tar -xvzf cmake-3.22.2.tar.gz
RUN cd cmake-3.22.2 && ./bootstrap && make -j $(nproc) && make install 

WORKDIR /


# Add group & user
RUN groupadd -r builder && useradd --create-home --gid builder --shell /bin/bash builder && echo 'builder ALL=NOPASSWD: ALL' > /etc/sudoers.d/builder

# #install git shell extension
RUN curl -L https://raw.github.com/git/git/master/contrib/completion/git-prompt.sh > ~/.bash_git && echo "source ~/.bash_git" >> ~/.bashrc
RUN sed -Ei 's/(PS1=.*)(\\\[\\033\[00m\\\]\\\$.*)/\1\\[\\033[01;33m\\]$(__git_ps1)\2/p' ~/.bashrc

USER builder