#!/bin/bash
adb push bl_modifier.ko /sdcard
adb push crash.ko /sdcard
adb push debug_after.ko /sdcard
adb push debug_before.ko /sdcard
adb push abfunction.ko /sdcard



ROOT_COMMAND="echo 0 > /proc/sys/kernel/kptr_restrict"
adb shell "su -c '${ROOT_COMMAND}'"
