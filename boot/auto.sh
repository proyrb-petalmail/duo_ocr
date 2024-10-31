#!/bin/sh

/mnt/system/usr/bin/sample_panel --panel=MILKV_8HD

insmod /mnt/system/ko/cvi_fb.ko vxres=800 vyres=1280

insmod /mnt/system/ko/3rd/gt9xx.ko
