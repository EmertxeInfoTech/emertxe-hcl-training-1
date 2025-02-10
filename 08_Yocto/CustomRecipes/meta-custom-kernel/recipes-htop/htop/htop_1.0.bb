DESCRIPTION = "Interactive process viewer for Unix systems"
HOMEPAGE = "https://github.com/htop-dev/htop"
LICENSE = "GPL-2.0-or-later"
LIC_FILES_CHKSUM = "file://COPYING;md5=751419260aa954499f7abaabaa882bbe"

SRC_URI = "git://github.com/htop-dev/htop.git;branch=main;protocol=https"
SRCREV = "af3b026b818caa623e59c88173db3295f667277a"  # Use the latest commit hash

S = "${WORKDIR}/git"

DEPENDS = "ncurses"

inherit autotools pkgconfig

