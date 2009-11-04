#!/bin/sh

cd /root/1.6r1/system/wlan/ti/sta_dk_4_0_4_32
make KERNEL_DIR=/root/kernel-hero ARCH=arm CROSS_COMPILE=~/1.6r1/prebuilt/linux-x86/toolchain/arm-eabi-4.4.0/bin/arm-eabi- clean
make KERNEL_DIR=/root/kernel-hero ARCH=arm CROSS_COMPILE=~/1.6r1/prebuilt/linux-x86/toolchain/arm-eabi-4.4.0/bin/arm-eabi-

