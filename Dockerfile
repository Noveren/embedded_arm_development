FROM alpine:3.22.1

ARG TOOLS_PATH=/opt/gcc-arm-none-eabi
# x86_64 darwin-arm64
ARG ARM_ARCH=x86_64
ARG ARM_VERSION=14.3.rel1
ARG ARM_GCC_URL="https://developer.arm.com/-/media/Files/downloads/gnu/${ARM_VERSION}/binrel/arm-gnu-toolchain-${ARM_VERSION}-${ARM_ARCH}-arm-none-eabi.tar.xz"

RUN apk update && apk add --no-cache --virtual build-dependences \
	build-base \
	libc6-compat \
	curl \
	cmake \
	ninja \
	just

RUN mkdir ${TOOLS_PATH} && \
	curl -Lo gcc-arm-none-eabi.tar.xz ${ARM_GCC_URL} && \
	tar xf gcc-arm-none-eabi.tar.xz --strip-components=1 -C ${TOOLS_PATH} && \
	rm gcc-arm-none-eabi.tar.xz && \
	rm -rf ${TOOLS_PATH}/share/doc

ENV PATH="$PATH:${TOOLS_PATH}/bin"