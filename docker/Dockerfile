FROM ubuntu:24.04

ARG TARGETARCH
ARG TOOLS_PATH=/opt/gcc-arm-none-eabi
ARG ARM_VERSION=14.3.rel1

RUN apt-get update && \
    apt-get install ninja-build --no-install-recommends -y && \
    apt-get install just --no-install-recommends -y && \
    apt-get install curl -y && \
    apt-get install xz-utils -y && \
    apt-get install cmake --no-install-recommends -y && \
    apt-get clean

RUN mkdir ${TOOLS_PATH} && \
    if [ "$TARGETARCH" = "amd64" ]; then \
        echo "x86_64" && ARM_GCC_URL="https://developer.arm.com/-/media/Files/downloads/gnu/${ARM_VERSION}/binrel/arm-gnu-toolchain-${ARM_VERSION}-x86_64-arm-none-eabi.tar.xz"; \
    elif [ "$TARGETARCH" = "arm64" ]; then \
        echo "aarch64" && ARM_GCC_URL="https://developer.arm.com/-/media/Files/downloads/gnu/${ARM_VERSION}/binrel/arm-gnu-toolchain-${ARM_VERSION}-aarch64-arm-none-eabi.tar.xz"; \
    else \
        echo "Unsupported architecture: $TARGETARCH" && exit 1; \
    fi && \
	curl -Lo gcc-arm-none-eabi.tar.xz $ARM_GCC_URL && \
	tar xf gcc-arm-none-eabi.tar.xz --strip-components=1 -C ${TOOLS_PATH} && \
	rm gcc-arm-none-eabi.tar.xz && \
	rm -rf ${TOOLS_PATH}/share/doc

ENV PATH="$PATH:${TOOLS_PATH}/bin"