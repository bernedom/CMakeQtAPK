FROM ubuntu:22.04

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

ARG QT_VERSION=5.15.2    
    

RUN apt-get update && apt-get install -y gdb build-essential python3 curl clang-tidy git libqt5qml5 ccache openjdk-8-jdk-headless \
    openjdk-8-jre-headless ninja ant mesa-common-dev libglu1-mesa-dev libfontconfig1-dev libfreetype6-dev libx11-dev \
                           libxext-dev libxfixes-dev libxi-dev libxrender-dev libxcb1-dev libx11-xcb-dev \
                           libxcb-glx0-dev libxkbcommon-x11-dev libssl-dev libxkbcommon-dev libxkbcommon-x11-dev \
                           libxcb-xinerama0-dev libxcb-render-util0-dev  libxcb-icccm4-dev libxcb-util-dev libxcb-shm0-dev \
                           libxcb-image0-dev libxcb-keysyms1-dev \
                           bluez libbluetooth-dev
RUN pip3 install conan cmake-format

# download and install qt
RUN git clone https://code.qt.io/qt/qt5.git
WORKDIR qt5
RUN git checkout v${QT_VERSION}
RUN perl init-repository
WORKDIR ./qt-build
RUN ../configure -xcb -xcb-xlib -qt-zlib -qt-libjpeg -qt-libpng -system-freetype -fontconfig -qt-pcre -qt-harfbuzz -opensource -nomake examples -nomake tests -confirm-license -prefix "/usr/local/Qt/gcc_64"
RUN make -s -j$(nproc)
RUN make install
WORKDIR /
RUN rm -rf qt

# Download & unpack android SDK
RUN echo "${SDK_SHA256} -" > sum.txt && curl -fLs "${SDK_URL}" | tee /tmp/sdk-tools.zip | sha256sum -c sum.txt \
    && mkdir -p /opt/android-sdk && unzip -q /tmp/sdk-tools.zip -d /opt/android-sdk && rm -f /tmp/sdk-tools.zip \
    && yes | sdkmanager --licenses && sdkmanager --update && sdkmanager --verbose "platforms;${SDK_PLATFORM}" "build-tools;${SDK_BUILD_TOOLS}" ${SDK_PACKAGES}

# Download & unpack android NDK
RUN mkdir /tmp/android && cd /tmp/android && echo "${NDK_SHA256} -" > sum.txt && curl -fLs "${NDK_URL}" | tee ndk.zip | sha256sum -c sum.txt \
    && unzip -q ndk.zip && mv android-ndk-* $ANDROID_NDK_ROOT && chmod -R +rX $ANDROID_NDK_ROOT \
    && rm -rf /tmp/android

# Reconfigure locale
RUN locale-gen en_US.UTF-8 && dpkg-reconfigure locales

# Add group & user
RUN groupadd -r builder && useradd --create-home --gid builder --shell /bin/bash builder && echo 'builder ALL=NOPASSWD: ALL' > /etc/sudoers.d/builder

# #install git shell extension
RUN curl -L https://raw.github.com/git/git/master/contrib/completion/git-prompt.sh > ~/.bash_git && echo "source ~/.bash_git" >> ~/.bashrc
RUN sed -Ei 's/(PS1=.*)(\\\[\\033\[00m\\\]\\\$.*)/\1\\[\\033[01;33m\\]$(__git_ps1)\2/p' ~/.bashrc