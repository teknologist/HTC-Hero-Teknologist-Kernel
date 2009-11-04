#!/bin/sh
ARCH=arm
CROSS_COMPILE=~/1.6r1/prebuilt/linux-x86/toolchain/arm-eabi-4.4.0/bin/arm-eabi-

cd /root/kernel-hero
make clean
cd /root/kernel-hero/compcache-0.5.4/
make clean
cd   /root/kernel-hero/fuse-2.8.1
make clean

cd /root/1.6r1/system/wlan/ti/sta_dk_4_0_4_32
make KERNEL_DIR=/root/kernel-hero clean

cd /root/kernel-hero

rm -rf  android_package_dir/
rm boot.img
