require recipes-kernel/linux/linux-yocto.inc
inherit cve-check
# CVE exclusions
include recipes-kernel/linux/cve-exclusion.inc
include recipes-kernel/linux/cve-exclusion_6.6.inc

SUMMARY = "Custom Linux kernel 6.12 for beaglebone"
DESCRIPTION = "Custom Linux kernel 6.12 for beaglebone from yoct repo"
LICENCE = "GPLv2"


KBRANCH = "v6.12/standard/beaglebone"
KMETA = "kernel-meta"
LINUX_VERSION = "6.12.11"
PV = "${LINUX_VERSION}+git"



SRC_URI = "git://git.yoctoproject.org/linux-yocto.git;name=machine;branch=${KBRANCH};protocol=https \
           git://git.yoctoproject.org/yocto-kernel-cache;type=kmeta;name=meta;branch=yocto-6.12;destsuffix=${KMETA};protocol=https"

SRCREV_meta = "cbe89aee4d05e11b15a928dfbc216fbdbdf062d2"
SRCREV_machine = "62b2447ec6cf3f8ce4b768cacd7b787a04f54a14"
#KBUILD_DEFCONFIG_MACHINE = 

LIC_FILES_CHKSUM = "file://COPYING;md5=6bc538ed5bd9a7fc9398086aedcd7e46"

COMPATIBLE_MACHINE = "beaglebone-yocto"
KMACHINE = "beaglebone"


